# KV Cache — Dense vs Paged

- **Category**: LLM Systems
- **Difficulty**: Hard
- **Target Role**: LLM Inference Engineer / ML Systems Engineer
- **Source**: PagedAttention (Kwon et al., SOSP 2023) + vLLM

---

## Concept Overview

Think of autoregressive decoding like a student writing an essay one word at a time, who must re-read the *entire* essay from scratch before writing each new word — that's the **no-cache** nightmare. A **KV cache** is the student's notebook: jot down the key ideas as you read once, then only look up your notes for each new word. The notebook is fast. The problem is that a *dense* notebook reserves the entire maximum-length shelf the moment a request arrives — if the essay ends at page 10, pages 11–8192 sit blank forever (up to 93.75% wasted). **PagedAttention** solves this by borrowing the OS virtual memory trick: shared "pages" of a fixed size, handed out on demand, with each request holding only an index card (block table) pointing to where its notes physically live.

### The Problem It Solves

- **No cache**: every decode step recomputes K,V for the *entire* prefix. Generating 5 tokens costs `1+2+3+4+5 = 15` K,V projections — `O(L²)` total. Token-0's K,V is recomputed **5×** without a cache vs **1×** with one.
- **Dense cache**: reduces decode to `O(1)` per step, but pre-allocates `[B, H_kv, max_seq_len, D]` up front. With `max_seq_len=8192` and a 512-token response, **93.75%** of the slab is dead memory (`1 − 512/8192 = 0.9375`). Across 100 concurrent requests: reserved = **400 GiB**, used = **25 GiB**, wasted = **375 GiB**.
- **Paged cache**: wastes only the last partial page. vLLM measured **< 4% system-wide waste** vs **60–80%** for prior dense/over-reserving systems.

### How It Works

```text
                ┌────────────────────────────────────────┐
                │ Decode: token t needs K,V of 0..t-1    │
                └───────────────────┬────────────────────┘
                                    │
            ┌───────────────────────┼───────────────────────┐
            v                       v                       v
  ┌─────────────────────┐ ┌─────────────────────┐ ┌─────────────────────┐
  │ 1. NO cache         │ │ 2. DENSE cache      │ │ 3. PAGED cache      │
  │                     │ │                     │ │ (PagedAttention)    │
  │ recompute all       │ │ pre-alloc slab      │ │                     │
  │ K,V every step      │ │ up-front            │ │ OS virtual memory   │
  │                     │ │                     │ │ model               │
  │ O(L^2) total        │ │ O(1)/step but       │ │ logical->physical   │
  │                     │ │ wastes 1-used/max   │ │ page table          │
  │                     │ │                     │ │                     │
  │                     │ │                     │ │ waste less than     │
  │                     │ │                     │ │ page_size tokens    │
  └─────────────────────┘ └─────────────────────┘ └─────────────────────┘
         |                       |                       ^
         |     "too slow"        |    "93%+ wasted"      |
         +---------------------->+---------------------->+
```

**Dense cache decode loop (step by step):**

1. New token arrives → project only *it* → `Q[1,d]`, `K[1,d]`, `V[1,d]`
2. Rotate Q and K at `offset = slice(current_len, current_len+1)` via RoPE (critical — wrong offset → gibberish)
3. Append `K[1]`, `V[1]` to the slab at `axis=2` (SeqLen axis)
4. Attention: `Q[1,d] @ K[S,d]^T` — O(S) per step, NOT O(S²)

**Paged cache (PagedAttention):**

```text
┌────────────────────────────────────────────────────────────────────┐
│ Physical page pool (shared)                                         │
│                                                                     │
│    ┌─────────┐    ┌─────────┐    ┌─────────┐    ┌─────────┐       │
│    │ page 0  │    │ page 1  │    │ page 2  │    │ page 3  │       │
│    └────▲────┘    └────▲────┘    └────▲────┘    └────▲────┘       │
└─────────┼──────────────┼──────────────┼──────────────┼─────────────┘
          │              │              │              │
       LA0│           LB0│           LA1│           LB1│
          │              │              │              │
┌─────────┴────────────────────────┐ ┌──┴───────────────────────────┐
│ Request A block table            │ │ Request B block table        │
│                                  │ │                              │
│   logical 0 -> phys 0   (LA0)   │ │   logical 0 -> phys 1  (LB0)│
│   logical 1 -> phys 2   (LA1)   │ │   logical 1 -> phys 3  (LB1)│
└──────────────────────────────────┘ └──────────────────────────────┘
```

Key mechanics:
- A **page** (block) holds `page_size` token slots (vLLM default: 16)
- Each request holds a **block table**: logical page index → physical page id
- A **free list** is the OS-style frame allocator; freed pages are immediately reusable
- Physical pages are **non-contiguous** — the attention kernel gathers K,V via the block table

---

## Worked Example

### No Cache vs Dense Cache (5 tokens)

From `kv_cache.py` Section A — generating 5 tokens:

| step t | seq len processed | K,V tokens computed | token-0 K,V recomputed? |
|--------|------------------|---------------------|-------------------------|
| 1 | 1 | 1 | yes (1) |
| 2 | 2 | 2 | yes (2) |
| 3 | 3 | 3 | yes (3) |
| 4 | 4 | 4 | yes (4) |
| 5 | 5 | 5 | yes (5) |

```
no-cache total projections : 1+2+3+4+5 = 15  (= L(L+1)/2 = O(L²))
with-cache total           : 5               (1 per step = O(L))
speedup (projections)      : 3.0x
```

### Dense Cache — Shape Evolution

From `kv_cache.py` Section B (`B=1, H_kv=2, D=8, max_seq_len=8`):

```
Pre-allocated slab shape: (1, 2, 8, 8) = [B=1, H_kv=2, max_seq_len=8, D=8]
Reserved bytes (K+V): 1024

PREFILL 3 tokens:  cache.k[:,:,:offset,:].shape = (1, 2, 3, 8)  (offset=3)
DECODE  1 token:   cache.k[:,:,:offset,:].shape = (1, 2, 4, 8)  (offset=4)
                   Q shape = [1, H_q, 1, D]  <- ONLY the new token
                   attention: Q[1,d] @ K[4,d]^T = O(S=4), not O(S^2)

Note: offset=4 but max_seq_len=8 -> 50% of the slab is unused right now.
```

### Fragmentation Math

From `kv_cache.py` Section C (fp16 = 2 bytes):

**Per-request slab (LLaMA-7B: 32 layers, 32 KV heads, d=128):**
```
2(KV) x 32 x 32 x 8192 x 128 x 2 B = 4,294,967,296 bytes = 4.000 GiB
```

| scenario | reserved | used | wasted |
|----------|----------|------|--------|
| 1 request, max=8192, actual=512 | — | 512 tokens | **93.75%** |
| 100 concurrent (used=512 each) | 400.0 GiB | 25.0 GiB | **375 GiB (93.8%)** |
| PagedAttention (vLLM default block=16) | on-demand | ~exact | **< 4%** |

Paged waste bound — only the last page is partial:

| page_size | worst-case internal waste |
|-----------|--------------------------|
| 4 | 25.00% |
| 16 | 6.25% <- vLLM default |
| 128 | 0.78% |

### Paged Block Table (page_size=4)

From `kv_cache.py` Section D — interleaving 2 requests:

| request | logical pages | physical pages | contiguous? |
|---------|--------------|----------------|-------------|
| A | ['L0', 'L1'] | ['P0', 'P2'] | NO (scattered) |
| B | ['L0', 'L1'] | ['P1', 'P3'] | NO (scattered) |

```
A.page_ids  = [0, 2]    A.page_lens = [4, 4]
B.page_ids  = [1, 3]    B.page_lens = [4, 1]
```

### Correctness Proof — All Three Paths Match

From `kv_cache.py` Section E (prefill 3 tokens, then decode token 3):

| path | K[0,0,0,:4] (token 0) | K[0,0,3,:4] (token 3) |
|------|----------------------|----------------------|
| all-at-once | [0.101, 0.102, 0.103, 0.104] | [-0.4541, 0.2641, 0.3906, 0.4028] |
| dense | [0.101, 0.102, 0.103, 0.104] | [-0.4541, 0.2641, 0.3906, 0.4028] |
| paged | [0.101, 0.102, 0.103, 0.104] | [-0.4541, 0.2641, 0.3906, 0.4028] |

```
[check] dense full-K  == all-at-once K? True
[check] paged full-K  == all-at-once K? True
[check] WRONG-offset decode differs?    True  <- proves offset is mandatory
[check] ALL THREE PATHS MATCH: OK
```

### Rewind(n) — The Ceil Trap (Speculative Decoding)

From `kv_cache.py` Section F (page_size=4):

Start: `page_ids=[0,1], page_lens=[4,1], offset=5, free_list=[2,3,4,5,6,7]`

After `rewind(1)`:
- `page_ids = [0]`  ← physical page 1 RETURNED to free list
- `page_lens = [4]` ← page 0 back to full
- `offset = 4`
- `free_list = [1,2,3,4,5,6,7]`

Off-by-one trap:

| offset | rewind(n) | new_offset | ceil(new/4) kept | floor would keep | correct? |
|--------|-----------|------------|-----------------|------------------|----------|
| 4 | 1 | 3 | 1 | **0 — too few!** | yes (ceil) |
| 8 | 1 | 7 | 2 | **1 — silent data loss!** | yes (ceil) |
| 5 | 5 | 0 | 0 | 0 | yes (ceil) |

```
rewind algorithm (always use ceil):
  new_offset   = offset - n
  target_pages = ceil(new_offset / page_size)  # <-- NEVER floor
  pop pages > target_pages -> free_list
  page_lens[-1] = new_offset - page_size*(target_pages - 1)
```

---

## Complexity & Trade-offs

| Metric | No Cache | Dense Cache | Paged Cache |
|--------|----------|-------------|-------------|
| K,V compute per step | O(L) — recompute all | O(1) — append 1 | O(1) — append 1 |
| Total over L steps | **O(L²)** | O(L) | O(L) |
| Memory reserved | none | `[B,H_kv,max_len,d]` up-front | on-demand pages |
| Worst-case waste | — | up to **93.75%** | < page_size tokens (< 4%) |
| Rewind complexity | free (no-op) | `offset -= n` | ceil-based page pop |
| LLaMA-7B per seq (8192 tok) | — | **4.0 GiB** | ~exact usage |
| Production use | toy code | rarely used | **vLLM, TGI, SGLang** |

---

## Common Interview Questions & How to Answer

### Q1: Why does the KV cache exist? What does it actually cache?

- **Answer**: Without a cache, every new token triggers a full forward pass over the growing prefix — token 0's K,V is recomputed at every step, making decode O(L²) total (for 5 tokens: `1+2+3+4+5=15` projections vs 5 with a cache, 3× speedup). The cache stores the *already-computed, already-RoPE-rotated* Keys and Values for every past token. At each decode step, we project only the **one new token** (O(1)), append its K,V, and attend the single new query against the full cached K,V (O(S) per step, O(L) total). The cache changes *when* K,V are computed, not *what* they are.

### Q2: What is the 93.75% waste number and how does it arise?

- **Answer**: Dense KV caches pre-allocate the full `[B, H_kv, max_seq_len, D]` slab the moment a request arrives, regardless of actual generation length. For `max_seq_len=8192` and an actual response of 512 tokens: `1 − 512/8192 = 0.9375 = 93.75%` dead. Across 100 concurrent requests: 400 GiB reserved vs 25 GiB used = 375 GiB wasted. This caps batch size, caps GPU utilization, caps throughput. The fix is paged allocation.

### Q3: How does PagedAttention eliminate that waste?

- **Answer**: PagedAttention borrows OS virtual memory. The KV store is a shared pool of fixed-size pages (vLLM default: 16 tokens/page). Each request holds only a block table (logical→physical mapping). Pages are allocated from a free list on-demand and returned when the request finishes. Waste is bounded to the last partial page per sequence (< `page_size` tokens). vLLM reduced system-wide waste from 60–80% to < 4%, enabling 2–4× throughput improvement. Non-contiguous physical storage is handled by the kernel walking the block table — exactly like an OS page walker.

### Q4: Why is the RoPE offset critical, and what breaks without it?

- **Answer**: The cache stores K,V *after* RoPE rotation, encoding absolute position. When decoding at step `t`, the new token must be rotated at `offset = slice(t, t+1)` — its true position. If we use `offset = slice(0,1)` (treating every decoded token as position 0), the cached path and the all-at-once path diverge — proven empirically: correct offset → identical outputs; wrong offset → different K,V (shown in the output: `[check] WRONG-offset decode differs: True`).

### Q5: Why does `rewind()` use `ceil` and not `floor`?

- **Answer**: When speculative decoding rejects `n` tokens, `new_offset = offset - n`. The pages to *keep* = `ceil(new_offset / page_size)`. At `offset=8, rewind(1)`: `new=7`, `ceil(7/4)=2` — correct (4+3 tokens). `floor(7/4)=1` silently drops page 2 which still holds 3 valid tokens. The next decode step reads stale garbage from a freed page — a completely silent bug (no error raised, no shape mismatch).

### Q6: What is the difference between the 93.75% and 60–80% numbers?

- **Answer**: These measure different things. **93.75%** is clean per-request arithmetic: `1 − 512/8192` for one request's reserved-vs-used slab. **60–80%** is vLLM's measured *system-wide* aggregate waste in prior serving systems, combining internal fragmentation + external fragmentation + over-reservation across many heterogeneous concurrent requests. **< 4%** is PagedAttention's measured system-wide result. All three are correct — they describe different scopes.

---

## Pro-Tip: How to Impress the Interviewer

- **Name the paper and the OS analogy**: "PagedAttention (Kwon et al., SOSP 2023) explicitly models KV pages as OS virtual memory pages — 'blocks as pages, tokens as bytes, sequences as processes.'"
- **Cite all three waste numbers** and distinguish them: 93.75% (per-request arithmetic), 60–80% (system-wide before PagedAttention), < 4% (system-wide after). Interviewers often conflate these.
- **Mention Copy-on-Write**: paged storage enables beam search and parallel sampling to *share* KV pages via reference counting — a win dense layout cannot replicate without copying the entire slab.
- **Mention the `offset`/RoPE coupling**: the cache is correct *only* because each new token is rotated at its true position. Bringing up this cross-cutting constraint signals deep understanding of the full decode stack.
- **Trade-off awareness**: paged adds kernel complexity (block-table gather scatter vs sequential reads) and a small per-request overhead. The tradeoff is worthwhile at scale but adds latency for single-request benchmarks.
