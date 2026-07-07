# Positional Encoding: Absolute PE vs RoPE
- **Category**: LLM Systems
- **Difficulty**: Hard
- **Target Role**: LLM Inference Engineer / ML Systems Engineer
- **Source**: ROPE.md + ABSOLUTE_PE.md + rope_output.txt (Su et al. 2021, Vaswani et al. 2017, Radford 2019)

---

## Concept Overview

The Transformer's attention mechanism is a dot product `Q · K` that is completely **blind to token order** — shuffle the tokens and every score stays the same. Position information must be injected from outside. There are two fundamentally different families:

**Absolute PE** (the "stamp-a-barcode" family) adds a position-specific vector to the token's embedding once at the input, before any Transformer block. Each token carries its seat number permanently baked in. GPT-2 uses a **learned** version (an `nn.Embedding` table `wpe`); the original Transformer uses a **sinusoidal** version (fixed sin/cos formula).

**RoPE** (Rotary Position Embedding, the "spin-a-compass-needle" family) works differently: instead of adding a barcode, it *rotates* the Query and Key vectors by an angle proportional to their position, inside **every** attention layer. The key insight: when two rotated vectors are dot-producted, the absolute angles cancel and only the *relative angle difference* (i.e., the distance between tokens) survives. Relative position emerges for free from a rotation — no explicit relative-position table needed.

This guide covers both families side by side. RoPE is used by Llama, Qwen, Mistral, Gemma. Absolute PE (learned) is used by GPT-2/nanoGPT.

### The Problem It Solves

Without position encoding, `"The cat sat"` and `"sat cat The"` produce identical attention scores and identical model outputs. From the output file: with RoPE, Q·K score for gap=1 is always **+0.514498** regardless of absolute seat (positions (2,1), (5,4), (10,9) all give the same score). With absolute PE, the same gap=1 gives **+7.0556, +4.9014, +7.2618** — completely different for different seats. RoPE encodes relative distance; absolute PE encodes absolute position.

### How It Works

```text
                  ┌──────────────────────────────────────┐
                  │   Problem: Q·K ignores token order   │
                  └──────────────────┬───────────────────┘
                                     │
            ┌────────────────────────┴────────────────────────┐
            ▼                                               ▼
 ┌────────────────────────┐                    ┌────────────────────────┐
 │  ADDITIVE family       │                    │  ROTARY family         │
 │  (absolute)            │                    │  (RoPE)                │
 └───────────┬────────────┘                    └───────────┬────────────┘
             │                                             │
     ┌───────┴───────┐                             ┌───────┴────────┐
     ▼               ▼                             ▼                ▼
┌────────────┐ ┌──────────────┐             ┌──────────────┐ ┌────────────┐
│Stamp each  │ │Examples:     │             │Give each     │ │Examples:   │
│token with  │ │learned wpe   │             │token a       │ │Llama, Qwen,│
│its SEAT    │ │(nanoGPT),    │             │COMPASS       │ │Mistral,    │
│NUMBER as a │ │sinusoidal    │             │NEEDLE; its   │ │Gemma       │
│fixed       │ │(original     │             │SEAT tells it │ │            │
│barcode,    │ │Transformer)  │             │how far to    │ │            │
│ADD ONCE at │ │              │             │ROTATE.       │ │            │
│the input   │ │              │             │INSIDE every  │ │            │
│            │ │              │             │attention     │ │            │
│            │ │              │             │layer.        │ │            │
└────────────┘ └──────────────┘             └──────────────┘ └────────────┘
```

---

## Family 1: Absolute Positional Encoding

### Where It Lives

Applied **once** at the input embedding, to the **full model dimension `E`**:

```text
┌──────────┐     ┌──────────────────┐
│ token id │───> │ token embedding  │
└──────────┘     │ wte[m] : [E]     │──┐
                 └──────────────────┘  │
                                       v
                                ┌──────────────┐     ┌────────────────────┐
                                │ stamp + add  │───> │ x : [B, L, E]      │
                                │              │     │ feeds transformer  │
                                └──────────────┘     │ blocks             │
                                       ▲             └────────────────────┘
                                       │
┌──────────┐     ┌──────────────────┐  │
│ seat num │───> │ position barcode │──┘
│    m     │     │ pe[m] : [E]      │
└──────────┘     └──────────────────┘
```

This is the defining property: absolute PE operates on `[B, L, E]`, added **once** before any block. Contrast with RoPE, which operates on `[B, L, H, D]` inside every block.

### The Shared Frequency Ladder

Both families use the same inverse-exponential frequency structure:

```
θ_i = base^(−2i/dim)    (same formula, different dim: E for absolute, D for RoPE)
```

From `rope_output.txt` **Section A** (`D=8, base=10000`):

| j | θ_j | meaning |
|---|---|---|
| 0 | **1.000000** | FAST rotation — tracks local position |
| 1 | **0.100000** | FAST |
| 2 | **0.010000** | SLOW — tracks long-range position |
| 3 | **0.001000** | SLOW |

The same four frequencies appear in the sinusoidal PE table (from `absolute_pe.py` Section A) — because the formula is identical. The **operation** differs: RoPE uses them as rotation angles; absolute PE uses them as values to add.

### Sinusoidal PE Table (Section B from absolute_pe output)

`PE(pos, 2i) = sin(pos / base^(2i/E))`, `PE(pos, 2i+1) = cos(pos / base^(2i/E))`

| m | d0 (sin) | d1 (cos) | d2 (sin) | d3 (cos) | d6 (sin) | d7 (cos) |
|---|---|---|---|---|---|---|
| 0 | 0.0000 | 1.0000 | 0.0000 | 1.0000 | 0.0000 | 1.0000 |
| 1 | 0.8415 | 0.5403 | 0.0998 | 0.9950 | 0.0010 | 1.0000 |
| 2 | 0.9093 | −0.4161 | 0.1987 | 0.9801 | 0.0020 | 1.0000 |
| 3 | 0.1411 | −0.9900 | 0.2955 | 0.9553 | 0.0030 | 1.0000 |

The high-frequency pair (d0/d1) swings wildly; the low-frequency pair (d6/d7) barely moves. Seat 0 gets the neutral barcode `[0,1,0,1,0,1,0,1]` (sin(0)=0, cos(0)=1 everywhere).

### Learned PE (nanoGPT `wpe`)

No formula — just a table `nn.Embedding(block_size, n_embd)` trained by SGD:

```python
self.wpe = nn.Embedding(block_size, n_embd)   # [max_len, E], trained
x = self.wte[idx] + self.wpe[pos]             # token emb + learned pos emb
```

Initial values are small random noise (~`*0.02`). The model learns what each seat's barcode should look like during training.

### Why Absolute PE Cannot Encode Relative Position

From `absolute_pe.py` **Section E** — same fixed Q and K, different absolute seats:

| m_q | m_k | gap = m_q−m_k | Q·K score |
|---|---|---|---|
| 2 | 1 | **1** | **+7.055621** |
| 5 | 4 | **1** | **+4.901406** |
| 10 | 9 | **1** | **+7.261821** |
| 2 | 0 | **2** | **+5.189337** |
| 5 | 3 | **2** | **+4.768941** |
| 10 | 8 | **2** | **+6.810799** |

Same gap, completely different scores. Adding the barcode bakes `m_q` into Q and `m_k` into K separately. The dot product then has cross terms `pe[m_q]·pe[m_k]`, `q·pe[m_k]`, `pe[m_q]·k` — no trig identity cancels them to a function of `m_q − m_k` alone.

---

## Family 2: RoPE (Rotary Position Embedding)

### The Compass Analogy

Each token holds `D/2` compass needles (called "clock dials"). The token's seat number `m` tells each needle how far to rotate. When two rotated tokens are later compared (dot product `Q·K`), what survives is only the **difference** in rotation angles — i.e., only `m_q − m_k` survives. Absolute positions cancel; relative distance appears for free.

### The Frequency Table (Section A)

From `rope_output.txt` **Section A** (`D=8, base=10000`):

| j | inner = j/(D/2) | θ_j = base^(−inner) | meaning |
|---|---|---|---|
| 0 | 0.0000 | **1.000000** | FAST — tracks local position |
| 1 | 0.2500 | **0.100000** | FAST |
| 2 | 0.5000 | **0.010000** | SLOW — tracks long-range position |
| 3 | 0.7500 | **0.001000** | SLOW — barely moves over 1000 seats |

Pair j=0 is a twitchy stopwatch; pair j=3 is a slow hour-hand. Together they record both fine-grained and coarse position simultaneously — a Fourier-like decomposition.

### Precomputed Lookup Tables (Section B+C)

Angle table `angle[m,j] = m · θ_j` (radians):

| m\j | j=0 | j=1 | j=2 | j=3 |
|---|---|---|---|---|
| m=0 | 0.0000 | 0.0000 | 0.0000 | 0.0000 |
| m=1 | 1.0000 | 0.1000 | 0.0100 | 0.0010 |
| m=2 | 2.0000 | 0.2000 | 0.0200 | 0.0020 |
| m=3 | 3.0000 | 0.3000 | 0.0300 | 0.0030 |

COS table (what gets looked up at seat m=2):

| m\j | j=0 | j=1 | j=2 | j=3 |
|---|---|---|---|---|
| m=2 | **−0.4161** | 0.9801 | 0.9998 | 1.0000 |

SIN table at m=2:

| m\j | j=0 | j=1 | j=2 | j=3 |
|---|---|---|---|---|
| m=2 | **0.9093** | 0.1987 | 0.0200 | 0.0020 |

Seat 0's row is all `cos=1, sin=0` → identity rotation (no spin). Seat 3's j=0 clock has cos=−0.99 (swung almost 180°); j=3 clock is still at cos≈1.000 (barely moved).

### Rotating One Token (Section D)

Input token `x` at position `m=2`, head dim `D=8`:
- `x1` (first half) = `[1.0, 0.5, −0.3, 0.8]`
- `x2` (second half) = `[0.2, −0.1, 0.4, 0.6]`

Per-pair rotation (complex multiply `(x1+i·x2)·(cos+i·sin)`):

| pair j | x1 | x2 | cos | sin | real = x1·cos−x2·sin | imag = x2·cos+x1·sin |
|---|---|---|---|---|---|---|
| 0 | +1.0 | +0.20 | −0.4161 | +0.9093 | **−0.5980** | **+0.8261** |
| 1 | +0.5 | −0.10 | +0.9801 | +0.1987 | **+0.5099** | **+0.0013** |
| 2 | −0.3 | +0.40 | +0.9998 | +0.0200 | **−0.3079** | **+0.3939** |
| 3 | +0.8 | +0.60 | +1.0000 | +0.0020 | **+0.7988** | **+0.6016** |

Reassemble (concat real then imag):
```
RoPE(x, m=2) = [-0.598, 0.5099, -0.3079, 0.7988, 0.8261, 0.0013, 0.3939, 0.6016]
original x   = [ 1.0,   0.5,   -0.3,    0.8,   0.2,  -0.1,   0.4,   0.6  ]
```

> **Norm preserved**: `max|‖out‖−‖in‖| = 2.98e−08` — rotation never stretches a vector.

### Full Batch Output (Section E)

From `rope_output.txt` — head h=0, before/after:

| m | d0 | d1 | d4 | d7 |
|---|---|---|---|---|
| 0 | +0.001 | +0.002 | +0.005 | +0.008 |
| 1 | **−0.034** | +0.091 | **+0.142** | +0.108 |
| 2 | **−0.270** | +0.157 | **+0.097** | +0.208 |
| 3 | **−0.341** | +0.198 | **−0.259** | +0.309 |

Row m=0 is unchanged (identity rotation). Rows get progressively more churned as `m` grows. The slow clocks (j=2,3, affecting d6/d7) barely deviate from input even at m=3.

### The Relative Position Proof (Section H)

The math: rotating Q by `m_q · θ` and K by `m_k · θ`, then taking the dot product:

```
clock contribution = (q1·k1 + q2·k2)·cos((m_q − m_k)·θ)
                   + (q1·k2 − q2·k1)·sin((m_q − m_k)·θ)
```

Only `(m_q − m_k)` survives. From `rope_output.txt` **Section H**:

| m_q | m_k | relative = m_q−m_k | Q·K score |
|---|---|---|---|
| 2 | 1 | **1** | **+0.514498** |
| 5 | 4 | **1** | **+0.514498** |
| 10 | 9 | **1** | **+0.514499** |
| 2 | 0 | **2** | **+0.285792** |
| 5 | 3 | **2** | **+0.285792** |
| 10 | 8 | **2** | **+0.285792** |

Same gap → identical score, regardless of absolute seat. This is the property absolute PE structurally cannot provide.

### Where RoPE Operates: The Tensor Shape Dance

```text
  ┌────────────────────┐
  │ x : [B, L, E]      │
  └─────────┬──────────┘
            │
            v
  ┌────────────────────┐
  │ wq / wk / wv       │
  │ linear projection  │
  └─────────┬──────────┘
            │
            v
  ┌────────────────────┐
  │ q, k, v :          │
  │ [B, L, H, D]       │
  └─────────┬──────────┘
            │
            v
  ┌────────────────────┐
  │ QK-Norm per-head   │
  │ RMSNorm            │
  │ [B, L, H, D]       │
  └─────────┬──────────┘
            │
            v
  ┌════════════════════┐   <<< RoPE applied HERE
  ║ ** RoPE here **    ║
  ║ apply on           ║
  ║ [B, L, H, D]       ║
  └─────────┬──────────┘
            │
            v
  ┌────────────────────┐
  │ transpose          │
  │ -> [B, H, L, D]    │
  └─────────┬──────────┘
            │
            v
  ┌────────────────────┐
  │ attention Q.K^T    │
  │ + causal mask      │
  └─────────┬──────────┘
            │
            v
  ┌────────────────────┐
  │ out : [B, H, L, D] │
  └─────────┬──────────┘
            │
            v
  ┌────────────────────┐
  │ transpose back     │
  │ -> [B, L, H, D]    │
  └─────────┬──────────┘
            │
            v
  ┌────────────────────┐
  │ wo projection      │
  └────────────────────┘
```

**Critical**: RoPE must be applied **while still in `[B, L, H, D]`**, BEFORE the transpose to `[B, H, L, D]`. The position axis is `L`, and cos/sin tables index by `L`. After transposing, the L axis is in the wrong slot for a clean per-position lookup.

### Split vs Traditional Layout (Section F)

Two ways to pair coordinates into clock dials:

| Layout | Pairs | Key |
|---|---|---|
| **Split** (Llama/Qwen, `traditional=False`) | (dim0, dim4), (dim1, dim5), ... | `x1=x[..., :D/2]`, `x2=x[..., D/2:]` |
| **Traditional** (GPT-NeoX, `traditional=True`) | (dim0, dim1), (dim2, dim3), ... | reshape `x[..., D/2, 2]` |

From `rope_output.txt` **Section F** — same input `x=[1..8]`, rotated at m=2:
```
Split:        [-4.9626, 0.7681, 2.8594, 3.984, -1.1714, 6.2777, 7.0586, 8.008]
Traditional:  [-2.2347, 0.077, 2.1455, 4.5163, 4.879, 6.0988, 6.984, 8.014]
```

**Different outputs. No error. Silent corruption if you use the wrong one.** Always read the checkpoint config. Qwen3/Llama = `traditional=False`.

### The Offset Parameter: KV Cache Prefill vs Decode (Section G)

During decode, each new token has a **true seat number** equal to the current sequence length, not position 0:

```
CORRECT offset=slice(3,4) → row m=3: [-0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.003]
WRONG   offset=slice(0,1) → row m=0: [ 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0  ]
```

`[check] decode(offset=3) == prefill_all[3]? True`

With the wrong offset (`slice(0,1)`), the new token's needle doesn't spin at all — it looks like it's at position 0, destroying all relative-position information. Output turns to nonsense after prefill. Fix: `offset = slice(current_len, current_len + 1)`.

---

## Complexity & Trade-offs

| Property | Absolute PE (sinusoidal/learned) | RoPE |
|---|---|---|
| Mental model | Stamp a seat-number barcode | Spin a compass needle |
| Operation | `x + pe[m]` (additive) | rotate `(x1+i·x2)·e^(imθ)` |
| Where applied | Input, **once**, `[B, L, E]` | Every layer, Q&K only, `[B, L, H, D]` |
| Frequency ladder | Same `[1, 0.1, 0.01, 0.001]` | Same `[1, 0.1, 0.01, 0.001]` |
| Norm preservation | **NO** (addition changes length) | **YES** (`max drift ≈ 3e−8`) |
| Encodes | Absolute seat number | **Relative** gap |
| Q·K depends on | `m_q` AND `m_k` separately | Only `m_q − m_k` |
| Length generalization | Weak (learned: hard cap at max_len) | Strong (YaRN/NTK scaling) |
| Used by | GPT-2, nanoGPT | Llama, Qwen, Mistral, Gemma |
| Base (theta) | N/A | 10000 (Llama-classic); **1,000,000** (Qwen3) |

---

## Common Interview Questions & How to Answer

### Q1: Why does RoPE encode relative position but absolute PE does not?

- **Answer**: It's a consequence of the math. With absolute PE, adding a position vector `pe[m]` to the token embedding bakes `m` permanently into the vector. When you dot-product two such vectors, you get cross-terms like `pe[m_q]·pe[m_k]`, `q·pe[m_k]`, `pe[m_q]·k` — these are functions of both `m_q` and `m_k` **separately**, not just their difference. No trig identity collapses them. With RoPE, rotating Q by `m_q·θ` and K by `m_k·θ` and then multiplying uses the identity that `cos(A)cos(B) + sin(A)sin(B) = cos(A−B)`, so the dot product becomes a function of `(m_q − m_k)·θ` only — absolute positions cancel exactly.

### Q2: What is the RoPE frequency table and why does it use a range of speeds?

- **Answer**: The frequency table has `D/2` entries where `θ_j = base^(−j/(D/2))`. With `D=8, base=10000`, that gives `[1.0, 0.1, 0.01, 0.001]` — a geometric sequence spanning 3 orders of magnitude. The fast pairs (j=0: θ=1.0) rotate by 1 radian per seat, so they can distinguish nearby tokens (they're fully differentiated by position 3). The slow pairs (j=3: θ=0.001) barely move across 1000 seats, so they encode coarse/global position. Together, it's a Fourier-like decomposition of position — fine-grained and coarse at the same time, with a single compact table.

### Q3: What is the split vs traditional layout in RoPE, and what breaks if you mix them?

- **Answer**: Both layouts apply the same rotation math but pair different coordinate dimensions. **Split** (Llama/Qwen, `traditional=False`): clock j pairs dim `j` with dim `j + D/2` — i.e., `x1 = x[..., :D/2]`, `x2 = x[..., D/2:]`. **Traditional** (GPT-NeoX, `traditional=True`): clock j pairs dim `2j` with dim `2j+1` — adjacent coordinates. From the output: the same vector at m=2 gives `[-4.963, 0.768, 2.859, ...]` under split but `[-2.235, 0.077, 2.146, ...]` under traditional. If you mix them, you get wrong outputs with no error message — the shapes match, the computation runs, but every attention score is wrong. Always read `config.json` for the `rope_scaling` and traditional flag.

### Q4: Why is the `offset` parameter critical during KV cache decode, and what is the failure mode?

- **Answer**: During decode, only one new token is processed per step, but it must be rotated at its **true** position `m = current_len`, not position 0. The `offset` parameter tells RoPE which row of the precomputed cos/sin table to look up: `offset = slice(current_len, current_len + 1)`. If you forget the offset and use `slice(0, 1)`, you look up row 0 (the identity rotation — cos=1, sin=0), meaning the new token's needle never spins. Its Q is unrotated, while the cached K vectors were correctly rotated at positions 0,1,2,... — the relative geometry is destroyed and the model emits nonsense. No crash, no error. From the output: correct gives `[..., 0.003]` in the last dimension; wrong gives `[..., 0.0]`.

### Q5: What is the difference between `base=10000` (Llama) and `base=1000000` (Qwen3)?

- **Answer**: A larger base means **slower** overall rotation — at position `m`, the angle for pair j is `m · base^(−j/(D/2))`. With `base=10000`, position 1000 has angle 1000 for the fastest pair — already past multiple full rotations, starting to alias. With `base=1000000`, position 1000 has angle 1000·(10^6)^0 = 1000 for j=0 but the slower pairs are 10× slower, effectively stretching the model's "distance scale" by 100×. This is a form of context length extrapolation — a larger base shifts the aliasing problem to much longer sequences. Qwen3's choice of `base=1_000_000` is why it handles 128k+ context better than Llama-classic with `base=10_000`.

### Q6: What is the tensor shape order for applying RoPE, and why does it matter?

- **Answer**: RoPE must be applied while the tensor is in `[B, L, H, D]` layout, **before** the transpose to `[B, H, L, D]`. Reason: position is the `L` axis, and the cos/sin lookup tables are indexed by `L`. In `[B, L, H, D]`, the L axis is at position 1 and is directly accessible for per-position rotation; broadcasting over H works cleanly. After transposing to `[B, H, L, D]`, L is at position 2 — the code still works but the convention in all reference implementations (Qwen, Llama) is to rotate first. If you apply RoPE after the transpose using the wrong axis, you'll rotate over heads instead of positions — silent garbage with no shape error.

---

## Pro-Tip: How to Impress the Interviewer

- **The relative-position proof in one breath**: "RoPE's dot product collapses to `cos((m_q−m_k)·θ)` terms via the trig identity `cos(A−B) = cosA·cosB + sinA·sinB`. The absolute positions `m_q` and `m_k` cancel — only their difference survives. Absolute PE has no such cancellation because addition bakes both positions in separately."
- **Know the Qwen3 specifics**: `rope_theta = 1_000_000` (not 10,000), `traditional = False` (split layout), per-head RMSNorm (QK-Norm) applied **before** RoPE. Getting these three details right in a code review is what separates inference engineers from ML practitioners.
- **Norm preservation is a useful invariant**: "RoPE preserves L2 norm exactly (max drift 2.98e−8 from the output file). This means `‖Q_rotated‖ = ‖Q_raw‖`, so the attention score magnitude `Q·K/√D` is controlled purely by the query/key content, not position. Absolute PE doesn't have this property — adding a barcode changes vector length."
- **Gold values to cite**: `RoPE(x=[1..8], m=2) = [-0.598, 0.510, -0.308, 0.799, 0.826, 0.001, 0.394, 0.602]` (split layout). Gap-1 score = `+0.514498` regardless of absolute seat.
- **YaRN/NTK connection**: For context extension beyond training length, mention that RoPE's base can be interpolated (NTK-aware scaling, YaRN) to extend context 2–32× with minimal fine-tuning. Absolute PE (especially learned `wpe`) hard-crashes at `max_len` with an index error — no such extension is possible without retraining the position table.
