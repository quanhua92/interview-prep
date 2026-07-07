# W4A16 Group Quantization

- **Category**: LLM Systems
- **Difficulty**: Hard
- **Target Role**: LLM Inference Engineer / ML Systems Engineer
- **Source**: LLM.int8() (Dettmers et al. 2022) + AWQ (Lin et al. 2024) + MLX affine quantization
- **Flashcards**: [LLM Systems deck](../flash_cards/llm/llm_systems.md)

---

## Concept Overview

Think of quantization like a digital camera's color depth. A raw image stores millions of precise colors (float16/FP32), which takes huge storage. If you reduce the photo to a 16-color palette (4-bit), the file size shrinks dramatically. You might notice a slight "color banding" in the gradients, but the main features of the photo are still perfectly recognizable. In **W4A16 Group Quantization**, we do exactly this: we round the model's static **weights** to a 16-color palette (4 bits, or $16$ discrete values) per group of weights, while keeping the dynamic **activations** (the actual data passing through the model) at full $16$-bit resolution. Since LLM decoding is limited by how fast we can load weights from memory, compressing the weights to $4$-bit makes the model load $\approx 4\times$ faster, while keeping activations in high-precision protects the model's reasoning quality.

```text
┌──────────────────────────────────────────────────────────────────────────┐
│                       WEIGHT COMPRESSION (OFFLINE)                       │
│                                                                          │
│  ┌───────────────────────────────┐                                       │
│  │     Static Weight Matrix      │                                       │
│  │       [N, E] (FP16)           │                                       │
│  └───────────────┬───────────────┘                                       │
│                 │                                                        │
│                 ▼                                                        │
│  ┌───────────────────────────────┐                                       │
│  │     Split into groups         │                                       │
│  │      (group_size=128)         │                                       │
│  └───────────────┬───────────────┘                                       │
│                 │                                                        │
│                 ▼                                                        │
│  ┌───────────────────────────────┐                                       │
│  │   Find Scale & Bias/group     │                                       │
│  └───────────────┬───────────────┘                                       │
│                 │                                                        │
│                 ▼                                                        │
│  ┌───────────────────────────────┐                                       │
│  │   Round weights to 0..15      │                                       │
│  └───────────────┬───────────────┘                                       │
│                 │                                                        │
│                 ▼                                                        │
│  ┌───────────────────────────────┐                                       │
│  │    Pack 8 weights -> uint32   │                                       │
│  │    (Saved to model weight)    │                                       │
│  └───────────────┬───────────────┘                                       │
└──────────────────┼───────────────────────────────────────────────────────┘
                   │
                   │ (Deploy model: Load weights 4x faster from HBM)
                   ▼
┌──────────────────────────────────────────────────────────────────────────┐
│                   FUSED DEQUANTIZE & MATMUL (RUNTIME)                    │
│                                                                          │
│  ┌───────────────────────────────┐   ┌───────────────────────────────┐   │
│  │     Activation Vector x       │   │     Packed weights uint32[]   │   │
│  │       (FP16, 2 Bytes)         │   │      + Scales/Biases (HBM)    │   │
│  └───────────────┬───────────────┘   └───────────────┬───────────────┘   │
│                 │                                   │                    │
│                 └─────────────────┬─────────────────┘                    │
│                                   │                                      │
│                                   ▼                                      │
│  ┌────────────────────────────────┬──────────────────────────────────┐   │
│  │                          Fused MAC Loop                           │   │
│  │                        (inside GPU SRAM)                          │   │
│  │    - Unpack uint32 -> 8 nibbles                                   │   │
│  │    - Dequantize: w_float = scale * w_int + bias                   │   │
│  │    - Compute dot product: acc += x * w_float                      │   │
│  └────────────────────────────────┬──────────────────────────────────┘   │
│                                   │                                      │
│                                   ▼                                      │
│  ┌───────────────────────────────────────────────────────────────────┐   │
│  │                       Output Vector (FP16)                        │   │
│  └───────────────────────────────────────────────────────────────────┘   │
└──────────────────────────────────────────────────────────────────────────┘
```

### The Problem It Solves

- **Memory Bandwidth Bottleneck**: In the autoregressive decode phase, the GPU cores compute the output for one token at a time. The computation is extremely simple, but the GPU must load the *entire* model weight matrix from slow High-Bandwidth Memory (HBM) to fast on-chip SRAM for every single token generated. 
- **The Speed Limit**: Because HBM reads are slow, the GPU cores spend most of their time waiting for weights to arrive. This makes LLM serving **memory-bandwidth bound**.
- **Outlier Activation Sensitivity**: Standard methods that quantize both weights and activations to 8-bit (W8A8) or 4-bit (W4A4) suffer from severe accuracy drops. This is because activations contain high-magnitude "outlier" channels (as shown in the LLM.int8() paper) that carry critical representation capacity. Rounding them to a coarse grid destroys the model's accuracy.

### How It Works

W4A16 addresses this by compressing only the weights (saving bandwidth) and keeping the activations in FP16 (preserving precision). To minimize accuracy loss, it applies **Group Quantization**:

1. **Partitioning**: The weight matrix is split into contiguous groups along the input dimension (typically `group_size = 128`).
2. **Finding the Scale & Bias**: For each group, we compute a floating-point `scale` and `bias` to map the weight range $[w_{\min}, w_{\max}]$ to the $4$-bit integer range $[0, 15]$.
3. **Quantizing**: 
   $$w_{\text{int}} = \text{clip}\left( \text{round}\left( \frac{w - \text{bias}}{\text{scale}} \right), 0, 15 \right)$$
4. **Packing**: Eight $4$-bit integers (each occupying a $4$-bit *nibble*) are squeezed into a single $32$-bit unsigned integer (`uint32`).
5. **Runtime Dequantization**: During inference, the weights are loaded from HBM in their packed `uint32` format. Inside the multiply-accumulate (MAC) loop, the GPU cores unpack the nibbles using bitwise shifts and masks, dequantize them back to FP16:
   $$w_{\text{float}} = \text{scale} \times w_{\text{int}} + \text{bias}$$
   and immediately multiply by the activation. The full-precision weight matrix is never materialized in HBM.

---

## Worked Example

Consider a single group of $8$ weights (group size $= 8$, $4$-bit resolution) being quantized using the MLX affine convention.

### Step 1: Deriving the Group Parameters
Let the input weight group be:
$$w = [-1.80, \ 0.55, \ -0.35, \ 1.20, \ -0.85, \ 0.25, \ -1.15, \ 1.05]$$

- **Extremes**: $w_{\min} = -1.80$, $w_{\max} = 1.20$.
- **Heavier Extreme**: $|w_{\min}| > |w_{\max}| \to 1.80 > 1.20$. The negative end is heavier, so we set the anchor `edge = w_min = -1.80`.
- **Target Quantization Level**: For 4 bits, the negative extreme maps to index $-9$ (since the levels range from $-8$ to $+7$, scaled appropriately). 
- **Scale**: $\text{scale} = \text{edge} / q_0 = -1.80 / -9 = \mathbf{0.200000}$
- **Bias**: $\text{bias} = \text{edge} = \mathbf{-1.800000}$ (in float units)

### Step 2: Mapping Weights to $4$-bit Integers
For each weight, we compute $w_{\text{int}} = \text{clip}(\text{round}((w - \text{bias})/\text{scale}), 0, 15)$:

| Element ($k$) | Original $w[k]$ | $\frac{w - \text{bias}}{\text{scale}}$ | Round | Stored $w_{\text{int}}$ | Dequantized Value | Rounding Error |
|---|---|---|---|---|---|---|
| **$0$** | $-1.80$ | $+0.00$ | $0$ | **$0$** | $-1.80$ | $+0.00$ (Zero error anchor) |
| **$1$** | $+0.55$ | $+11.75$ | $12$ | **$12$** | $+0.60$ | $-0.05$ |
| **$2$** | $-0.35$ | $+7.25$ | $7$ | **$7$** | $-0.40$ | $+0.05$ |
| **$3$** | $+1.20$ | $+15.00$ | $15$ | **$15$** | $+1.20$ | $+0.00$ (Other extreme anchor) |
| **$4$** | $-0.85$ | $+4.75$ | $5$ | **$5$** | $-0.80$ | $-0.05$ |
| **$5$** | $+0.25$ | $+10.25$ | $10$ | **$10$** | $+0.20$ | $+0.05$ |
| **$6$** | $-1.15$ | $+3.25$ | $3$ | **$3$** | $-1.20$ | $+0.05$ |
| **$7$** | $+1.05$ | $+14.25$ | $14$ | **$14$** | $+1.00$ | $+0.05$ |

The maximum rounding error is $0.05$ (exactly $\le \text{scale} / 2 = 0.1$).

### Step 3: Packing into `uint32`
The $8$ integers $w_{\text{int}} = [0, 12, 7, 15, 5, 10, 3, 14]$ are packed LSB-first:
- $w_{\text{int}}[0] = 0 \to \text{bits } [0:4]$
- $w_{\text{int}}[1] = 12 \ (0\text{xC}) \to \text{bits } [4:8]$
- ...
- $w_{\text{int}}[7] = 14 \ (0\text{xE}) \to \text{bits } [28:32]$

$$\text{Packed Decimal} = \mathbf{3819304896} \quad \text{Hex} = \mathbf{0xE3A5F7C0}$$
*Note: Reading the hex representation right-to-left recovers the original integers: $0xE3A5F7C0 \to 0, \text{C } (12), 7, \text{F } (15), 5, \text{A } (10), 3, \text{E } (14)$.*

### Step 4: Quantized Matrix Multiplication
Let an activation vector be $x = [0.5, -0.3, 0.8, -0.1, 0.4, -0.6, 0.2, 0.7]$. We perform $x @ W^T$ against a $4 \times 8$ weight matrix (where row 0 is our quantized weight above):

| Output Index | Full-Precision Matmul ($x @ W^T$) | Quantized Matmul (Dequant in MAC) | Absolute Error |
|---|---|---|---|
| **Row 0** | $-1.4500$ | $-1.5000$ | $0.0500$ |
| **Row 1** | $+2.0800$ | $+2.0800$ | $0.0000$ |
| **Row 2** | $-1.9500$ | $-2.0267$ | $0.0767$ |
| **Row 3** | $+2.0600$ | $+1.9987$ | $0.0612$ |

- **Mean Relative Error**: $2.59\%$ (extremely minor deviation, which is why accuracy is preserved at scale).

---

## Memory Footprint Analysis (Qwen2.5-0.5B scale)
For one linear layer weight matrix of shape $[896, 896]$:

| Format | Weight Memory Footprint | Compression vs FP16 |
|---|---|---|
| **FP16 / BF16 Baseline** | $896 \times 896 \times 2 \text{ bytes} = \mathbf{1.606\text{ MB}}$ | $1.0\times$ |
| **W4A16 (group_size = 8)** | $401,408\text{ B (weights)} + 401,408\text{ B (scale/bias)} = \mathbf{0.803\text{ MB}}$ | $2.0\times$ |
| **W4A16 (group_size = 128)** | $401,408\text{ B (weights)} + 25,088\text{ B (scale/bias)} = \mathbf{0.426\text{ MB}}$ | **$3.76\times$** |

*Note: Group size $= 128$ is the real-world standard. Group size $= 8$ wastes too much memory on scale/bias overhead (1 scale and 1 bias for every 8 weights).*

---

## The Sign-Convention Pitfall (The #1 Quantization Bug)
There are two major dequantization standards in the LLM ecosystem:
1. **MLX Affine**: $w = \text{scale} \times w_{\text{int}} + \text{bias}$ (where `bias` is stored in **float** units).
2. **Textbook Zero-Point (GPTQ/AWQ)**: $w = \text{scale} \times (w_{\text{int}} - \text{zero\_point})$ (where `zero_point` is stored in **integer** units).

They are equivalent *only* if:
$$\text{zero\_point} = -\frac{\text{bias}}{\text{scale}}$$
If a developer plugs an MLX float `bias` ($-1.8$) into a textbook-style implementation (e.g. `(w_int + bias) * scale`), it scrambles the weights:

| Variant | Equation | Result for $w_{\text{int}} = 12$ | Verdict |
|---|---|---|---|
| **MLX Convention** | $0.2 \times 12 + (-1.8)$ | $\mathbf{+0.6000}$ | **Correct** |
| **Textbook Convention** | $0.2 \times (12 - 9.0)$ | $\mathbf{+0.6000}$ | **Correct** |
| **Incorrect Prose Cross** | $(12 + (-1.8)) \times 0.2$ | $\mathbf{+2.0400}$ | **Garbage (Error = 1.44)** |

---

## Complexity & Trade-offs

| Metric | Value | Notes |
|---|---|---|
| **HBM Read Bandwidth** | $\approx 3.76\times$ reduction | Speeds up decode phase since we load far fewer bytes from main memory. |
| **GPU Compute (FLOPs)** | Slightly higher | We perform additional bitwise shifts, masks, and FMA operations to dequantize. |
| **SRAM Memory Usage** | Bounded | Activations and unpacked registers live in SRAM; no full weight dequantization in SRAM. |
| **Model Size** | $\approx 70-75\%$ reduction | Allows larger models (e.g., Llama 3 70B) to run on a single consumer GPU. |
| **Outlier Handling** | Excellent | Leaving activations in FP16 ensures outlier channels are not clipped. |

---

## Common Interview Questions & How to Answer

### Q1: Why do we choose W4A16 (weights in 4-bit, activations in 16-bit) rather than quantizing activations to 4-bit as well (W4A4)?
- **Answer**: Activation vectors contain dynamic "outlier channels" — specific dimensions that have exceptionally large values (up to $100\times$ higher than other channels) across almost all tokens. If we quantize activations to 4-bit, these outlier values force the quantization step size to be very large, which destroys the resolution of the non-outlier values, leading to a catastrophic drop in model accuracy. Weights do not exhibit this extreme, token-dependent outlier behavior. Since LLM decoding is memory-bandwidth bound (limited by weight loading, not activation loading), keeping activations in 16-bit preserves representation capacity while quantizing weights to 4-bit achieves the desired memory throughput.

### Q2: How does dequantization on-the-fly work inside the matrix multiplication kernel, and why is this faster than dequantizing the weights beforehand?
- **Answer**: If we dequantized the 4-bit weights back to FP16 in memory *before* running the matrix multiplication, we would have to write the FP16 weights back to HBM and read them again. This would defeat the entire purpose of quantization, as we would still be bottlenecked by FP16 HBM traffic. Instead, we perform "fused dequantization" inside the Multiply-Accumulate (MAC) loop. The thread blocks load the packed `uint32` weights from HBM directly into the GPU registers/SRAM. Inside the execution pipeline, the cores unpack the 4-bit integers using bitwise shifts and masks, apply the scale and bias, and immediately multiply by the activations. The full-precision weights are never written to main memory, keeping the memory bandwidth requirement to a minimum.

---

## Pro-Tip: How to Impress the Interviewer

- **Avoiding Dequantization Latency (Bit-Unpacking Bottlenecks)**: Explain that while W4A16 saves memory bandwidth, the extra instructions required to unpack the `uint32` values (shifts, bitwise ANDs, casting to floats) can introduce computation overhead, making the kernel instruction-bound. On modern NVIDIA GPUs, we can optimize this by using specialized SIMD byte-permutation instructions (like `prmt` or warp-level shuffle assembly) to unpack multiple nibbles simultaneously. Additionally, storing the scale and bias in half-precision (FP16) allows us to perform the dequantization using fast Half-Precision Tensor Core instructions, overlapping the unpacking latency with the main matrix operations.
