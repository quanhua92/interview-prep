# JAX, XLA & TPU Pallas

- **Category**: LLM Systems
- **Difficulty**: Expert
- **Target Role**: LLM Inference Architect / ML Platform Engineer
- **Source**: JAX (Frostig et al., SysML 2018) / TPU Systolic Array (Jouppi et al., ISCA 2017) / FlashAttention (Dao et al., 2022) / TPU Pallas
- **Flashcards**: [LLM Systems deck](../flash_cards/llm/llm_systems.md)

---

## Concept Overview

Eager execution frameworks (like PyTorch) compute operations sequentially as Python encounters them. For a chain of operations, each intermediate tensor is written to slow High-Bandwidth Memory (HBM) and immediately read back by the next step, introducing significant memory bandwidth overhead.

**JAX** and **XLA** solve this by tracing and compiling execution blocks. When a function is JIT-compiled (`@jax.jit`), JAX performs a single dry-run trace using abstract placeholders (**Tracers**) to record the operation dependencies into a functional Intermediate Representation called a **jaxpr**. The **XLA** compiler then analyzes this jaxpr to **fuse** producer-consumer operations. Intermediates flow directly within register file structures or fast on-chip memory (VMEM), minimizing HBM round-trips. The compiled binary runs on a **TPU**, which features a **systolic Matrix Multiply Unit (MXU)** where weights sit still and activations flow through a 2D processing element grid, eliminating intermediate memory writebacks.

```text
Eager PyTorch (4 HBM writes):
[x@W1] ──> HBM ──> [+b1] ──> HBM ──> [silu] ──> HBM ──> [@W2] ──> HBM

XLA Fused JAX (1 HBM write):
[ (x@W1) ──> Reg ──> (+b1) ──> Reg ──> (silu) ──> Reg ──> (@W2) ] ──> HBM
```

### The Problem It Solves

Because LLM generation is memory-bandwidth bound, writing and reading intermediate tensors degrades execution speed.
For the MLP activation block `silu(x @ W1 + b1) @ W2`:
- **Eager Execution**: Four separate kernels are launched, materializing **4 intermediate writes to HBM** (`dot1`, `add`, `silu`, `dot4`).
- **Traced & Fused JAX**: XLA fuses the element-wise operations (`add`, `silu`) into the epilogues of the matrix multiplications. Only the final product is written to HBM, collapsing HBM writes from **4 to 1** (a **4× memory traffic reduction**).

For a chain of $E$ element-wise operations following a matrix multiplication, the memory traffic scales as:

| Element-wise Ops Fused ($E$) | Eager HBM Writes | Fused HBM Writes | Bandwidth Win |
|---|---|---|---|
| **0** | 1 | 1 | 1× |
| **1** | 2 | 1 | 2× |
| **2** | 3 | 1 | 3× |
| **3** | 4 | 1 | 4× (Our MLP Block) |
| **5** | 6 | 1 | 6× |
| **9** | 10 | 1 | 10× |

### How It Works

1. **JIT Tracing**: When a `@jax.jit` decorated function is called, the Python engine compiles the graph once. It passes abstract `Tracer` objects (capturing shape and dtype, but no data) through the function, capturing the primitives into a **jaxpr** IR.
2. **XLA Fusion**: XLA lowering identifies straight-line dependencies. It groups element-wise operations together and stitches them onto the matrix multiplication (anchor) kernels.
3. **Weight-Stationary Systolic Array**: The TPU's MXU contains a 2D grid of multiply-accumulate Processing Elements (PEs) (typically 256×256). Weights are loaded into the PEs and remain **stationary**. Activations stream through diagonally. Accumulations are passed directly to neighboring PEs in the grid. The result emerges at the boundaries after $3N - 1$ cycles (for $N \times N$ grid, taking 767 cycles for $N=256$), with zero intermediate memory overhead.
4. **Pallas Grid & BlockSpec**: While XLA handles standard fusion, it fails to fuse complex operations like Softmax. **Pallas** is a TPU kernel language that provides explicit tiling control:
   - **Grid**: The parallel indexing space of the tiles.
   - **BlockSpec**: Defines the shape and index mapping of HBM tiles into local Vector Memory (VMEM). Pallas pipelines HBM $\leftrightarrow$ VMEM copies to overlap memory transfer with MXU compute, ensuring the intermediate softmax outputs never touch HBM.
5. **Splash Attention**: The TPU-native version of FlashAttention written in Pallas. It keeps running online-softmax accumulators ($m, l, o$) in VMEM and rescales them on the fly using the correction factor $\exp(m_{old} - m_{new})$, returning exact attention outputs with a single write-back to HBM.

---

## Worked Example

This example demonstrates the compilation tracing, systolic array execution, and Pallas Splash Attention recurrence using exact simulated numbers.

### 1. Jaxpr Tracing
Tracing the function $f(x) = \text{silu}(x \cdot W1 + b1) \cdot W2$ generates the following jaxpr equations:
- `dot1 = dot_general(x, W1)` (shape: `(1, 8)`)
- `a2 = add(dot1, b1)` (shape: `(1, 8)`)
- `s3 = silu(a2)` (shape: `(1, 8)`)
- `dot4 = dot_general(s3, W2)` (shape: `(1, 4)`)

Under eager execution, this results in **4 HBM writes**. Under fused execution, `dot1`, `a2`, and `s3` are computed in local register files. Only `dot4` is materialized to HBM, reducing writes to **1**.

### 2. TPU Weight-Stationary Systolic Step-by-Step
We perform $C = W \cdot X$ on a $3\times3$ grid:
- **Stationary Weights ($W$)**:
  $$W = \begin{pmatrix} -0.1 & 0.8 & 0.9 \\ -1.1 & 1.7 & -0.9 \\ -0.4 & 1.2 & 0.1 \end{pmatrix}$$
- **Streaming Activations ($X$)**:
  $$X = \begin{pmatrix} -1.7 & 0.3 & 0.1 \\ 0.1 & 0.2 & 1.4 \\ 1.3 & 2.4 & 0.2 \end{pmatrix}$$

Execution accumulates partial sums in-place over 3 steps:
- **Step $k=0$**: $C += W[:,0] \otimes X[0,:]$
  $$C_0 = \begin{pmatrix} 0.17 & -0.03 & -0.01 \\ 1.87 & -0.33 & -0.11 \\ 0.68 & -0.12 & -0.04 \end{pmatrix}$$
- **Step $k=1$**: $C += W[:,1] \otimes X[1,:]$
  $$C_1 = \begin{pmatrix} 0.25 & 0.13 & 1.11 \\ 2.04 & 0.01 & 2.27 \\ 0.80 & 0.12 & 1.64 \end{pmatrix}$$
- **Step $k=2$**: $C += W[:,2] \otimes X[2,:]$
  $$C_2 = \begin{pmatrix} 1.42 & 2.29 & 1.29 \\ 0.87 & -2.15 & 2.09 \\ 0.93 & 0.36 & 1.66 \end{pmatrix}$$
- **Reference `torch.matmul(W, X)`**:
  $$C_{ref} = \begin{pmatrix} 1.42 & 2.29 & 1.29 \\ 0.87 & -2.15 & 2.09 \\ 0.93 & 0.36 & 1.66 \end{pmatrix}$$
The systolic output matches the reference exactly ($\text{error} = 2.38 \times 10^{-7}$). Weights stayed resident in the grid throughout the accumulation, saving memory round-trips.

### 3. Splash Attention Pallas Execution
We run Splash Attention on seeded inputs ($N=8, d=8$, query tile size $B_r = 4$, key tile size $B_c = 4$).
The tiled online-softmax recurrence runs in Pallas:
- **Running Update Equations**:
  $$m_{\text{new}} = \max(m_{\text{old}}, \text{rowmax}(s))$$
  $$p = \exp(s - m_{\text{new}})$$
  $$l_{\text{new}} = \exp(m_{\text{old}} - m_{\text{new}}) \cdot l_{\text{old}} + \text{rowsum}(p)$$
  $$o_{\text{new}} = \exp(m_{\text{old}} - m_{\text{new}}) \cdot o_{\text{old}} + p \cdot v_{\text{tile}}$$
  $$\text{out} = \frac{o}{l}$$

We inspect the final output row $q=0$:
- **Tiled Splash Output**:
  `[-0.0673, -0.1466, -0.2175, +0.0201, +0.1810, -0.1534, +0.2226, -0.0995]`
- **Naive Softmax Attention Output**:
  `[-0.0673, -0.1466, -0.2175, +0.0201, +0.1810, -0.1534, +0.2226, -0.0995]`
- **Difference**: $2.98 \times 10^{-8}$ (pure floating-point noise).
The output matches the naive attention calculation exactly. This row is also identical to FlashAttention's output on GPUs, proving the math is hardware-agnostic.

---

## Complexity & Trade-offs

| Metric | Complexity / Value | Notes |
|---|---|---|
| **Compilation Latency** | High (first call) | Tracing and optimizing the graph introduces compilation lag. Subsequent calls run at native speed. |
| **Systolic Latency** | $3N - 1$ cycles | Grid fill and drain latency for $N \times N$ tiles. |
| **Pallas HBM Writes** | $\mathcal{O}(\text{tiles})$ | Softmax scores are kept in VMEM; only the final aggregated attention tile is written to HBM. |
| **VMEM Capacity** | Tens of MiB | Strict physical limits. If the tiled BlockSpec shape is too large, it throws a VMEM OOM. |

---

## Common Interview Questions & How to Answer

### Q1: Explain why Python control flow (like `if` statements or `for` loops) can behave unexpectedly inside a JAX JIT-compiled function.
- **Answer**: JAX compiles functions by **tracing** them once using abstract placeholder variables (`Tracers`) that have shapes and dtypes but no physical data.
  If a JAX function contains a standard Python conditional statement:
  ```python
  if x > 0:
      return y
  else:
      return z
  ```
  The condition `x > 0` depends on concrete data. During tracing, JAX passes a `Tracer` for `x`. Because the concrete value is unknown during compile time, JAX cannot resolve which branch to take. It will throw a `ConcretizationTypeError`.
  Similarly, a standard Python `for` loop:
  ```python
  for i in range(len(x)):
  ```
  will be unrolled statically during compilation if the loop bound is static. However, if the loop condition depends on a dynamic value, tracing fails.
  To resolve this, we must use JAX-specific control flow primitives (like `jax.lax.cond` or `jax.lax.fori_loop`), which compile the conditional branches into the jaxpr as control flow operators rather than evaluating them during Python tracing.

### Q2: How does Pallas's BlockSpec address the VMEM size limit on TPUs, and how does it prevent memory bandwidth stalls?
- **Answer**: The Vector Memory (VMEM) on a TPU is a fast, on-chip scratchpad (typically tens of megabytes), which is too small to hold large model activation or weight tensors.
  Pallas resolves this by using **BlockSpec** to tile the tensors. BlockSpec defines:
  1. A `block_shape` (e.g., $128 \times 128$), which specifies the size of the tile loaded into VMEM.
  2. An `index_map`, which maps the multi-dimensional grid coordinates to HBM memory offsets.
  To prevent memory bandwidth stalls, Pallas utilizes the TPU's hardware DMA engine to **pipeline** memory transfers. While the Vector Processing Unit (VPU) and MXU are performing computations on the current tile in VMEM, the DMA engine asynchronously pulls the next HBM tile into a separate VMEM buffer (double-buffering). This hides memory latency behind arithmetic execution, preventing the TPU cores from stalling.

---

## Pro-Tip: How to Impress the Interviewer

- **XLA Fusion Bottleneck awareness**: Impress the interviewer by showing that fusion is not a magic bullet. Explain that XLA is highly effective at fusing **element-wise and reduction operations** (such as activations, layernorms, and residuals) into the matrix multiplication kernels. However, XLA cannot easily fuse two consecutive heavy matrix multiplications (like MLP `gate` and `down` projections) because they are compute-bound anchors that require full VRAM allocation. For these, we must rely on scheduling optimizations like Grouped GEMM or custom Triton/Pallas kernels.
- **CUDA Graphs vs. XLA Compilation**: Contrast JAX with PyTorch's performance acceleration. Explain that **CUDA Graphs** target **CPU launch overhead** (collapsing many Python-to-GPU API calls into a single instruction playback), whereas **XLA** targets **memory bandwidth** (re-organizing and fusing operations to avoid HBM round-trips). They are complementary optimizations: a production serving engine utilizes XLA to compile optimal fused kernels and a Graph scheduler to launch them with minimal overhead.
