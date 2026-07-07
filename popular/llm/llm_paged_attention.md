# PagedAttention: Virtual Memory for KV Cache
- **Category**: LLM Systems
- **Difficulty**: Hard
- **Target Role**: LLM Inference Engineer / LLM Serving Engineer
- **Source**: paged_attention.py / PAGED_ATTENTION.md (vLLM, SOSP 2023)

---

## Concept Overview

Imagine a **library with shared shelves carved into fixed-size pages**. Before PagedAttention, every reader (request) got their own giant private shelf reserved the moment they walked in — even if they only used 500 of 8192 available slots, the other 7692 stayed empty and reserved. PagedAttention replaces this with the OS virtual-memory trick: each reader gets an **index card** (the block table) listing which physical shelf pages hold their notes, and those pages can be scattered anywhere in the shared pool. No pre-reservation, on-demand allocation, waste bounded to the last partial page.

The key insight borrowed from OS virtual memory: **"blocks as pages, tokens as bytes, sequences as processes"** (vLLM paper §3.1). The paged attention kernel reads K,V through an indirect lookup (like an OS page table walk) instead of a contiguous slab, costing one extra memory indirection per tile but enabling non-contiguous, on-demand allocation.

### The Problem It Solves

Dense KV caching pre-allocates `[B, H_kv, max_seq_len, d]` per request up front. With `max_seq_len=8192` but only 512 tokens used, **93.75%** of that slab is dead VRAM. For 100 concurrent requests, this wastes **375 GiB** of 400 GiB reserved. vLLM measured that prior serving systems wasted **60–80%** of KV memory system-wide. Dead VRAM means fewer concurrent requests → lower GPU utilization → lower throughput.

### How It Works

```text
┌──────────────────────────────────┐
│ Decode: each request needs       │
│                growing K,V       │
└────────────────┬─────────────────┘
                 │
       ┌─────────┴─────────┐
       ▼                   ▼
┌──────────────────┐  ┌──────────────────────────┐
│ DENSE cache      │  │ PAGED cache              │
│  pre-alloc       │  │  shared pool             │
│  [B,H_kv,        │  │  [num_pages,H_kv,        │
│   max_len,d]     │  │   page_size,d]           │
│  per request     │  │  block_table:            │
│   up-front       │  │   logical -> physical    │
│  wastes up to    │  │  waste < 1/page_size     │
│   93%            │  └─────────────┬────────────┘
└────────┬─────────┘                │
         │                          │
         │   60-80% system-wide     │
         │   waste (replaced by)    │
         └────────────┬─────────────┘
                      │  near-zero waste
                      │  + prefix sharing
                      ▼
         ┌────────────────────────────┐
         │ 2-4x throughput            │
         │ vs prior SOTA              │
         └────────────────────────────┘
```

---

## Worked Example

All numbers from `paged_attention_output.txt`.

### Section A: The Dense-Waste Problem

```
max_seq_len reserved = 8192, actual tokens used = 512
waste fraction = 1 - 512/8192 = 0.9375 = 93.75%
```

**Per-request dense KV bytes** (LLaMA-7B: 32 layers, 32 KV heads, d=128):
```
2(KV) × 32 × 32 × 8192 × 128 × 2 B = 4,294,967,296 bytes = 4.000 GiB
```

**100 concurrent requests** (each using only 512 tokens):
```
reserved = 400.0 GiB
used     = 25.0 GiB
wasted   = 375.0 GiB  (93.8% of reserved!)
```

**Paged cache waste bound** (only the last page of each request is partial):

| page_size | worst-case internal waste |
|-----------|--------------------------|
| 16        | 6.25% ← vLLM default    |
| 128       | 0.78% ← tiny-llm        |

> vLLM measured: PagedAttention wastes **<4%** in practice vs **60–80%** for prior systems.

Two different numbers — keep them distinct:
| Number | What it measures |
|--------|-----------------|
| **93.75%** | One request's reserved-vs-used slab (`1 − 512/8192`) |
| **60–80%** | System-wide KV waste measured by vLLM across all concurrent requests |
| **<4%** | System-wide waste under PagedAttention |

---

### Section B: Page Pool + Free List

The pool is a shared slab `[num_pages, H_kv, page_size, D]`. The free list is the OS frame allocator.

```
page_size=2, H_kv=2, D=8, num_pages=4
key_pages shape: (4, 2, 2, 8)  = [num_pages, H_kv, page_size, D]
```

| step | action         | free_list after | pool.used   |
|------|----------------|-----------------|-------------|
| 1    | allocate() → 0 | [1, 2, 3]       | [0]         |
| 2    | allocate() → 1 | [2, 3]          | [0, 1]      |
| 3    | allocate() → 2 | [3]             | [0, 1, 2]   |
| 4    | free_page(0)   | [0, 3]          | [1, 2]      |
| 5    | allocate() → 0 | [3]             | [0, 1, 2]   |

> Step 5: `free_page(0)` returned page 0, and the next `allocate()` immediately **reused** it. No fragmentation.

---

### Section C: The Block Table (Logical → Physical)

**Analogy**: each request gets an *index card* listing which physical pages hold their tokens IN ORDER. Pages can be scattered anywhere in the pool.

```text
┌─ Request A — block table (index card) ─────────┐
│   logical 0  ───────────────────────▶ page 0   │
│   logical 1  ───────────────────────▶ page 2   │
└────────────────────────────────────────────────┘

┌─ Request B — block table ─────────────────────┐
│   logical 0  ───────────────────────▶ page 1   │
└────────────────────────────────────────────────┘

┌─ Physical page pool (shared 'RAM') — ids 0..7 ──────────────┐
│                                                              │
│  ┌──────────────┐  ┌──────────────┐  ┌──────────────┐  ┌──────────────┐
│  │   page 0     │  │   page 1     │  │   page 2     │  │  pages 3..7  │
│  │ (A's notes)  │  │ (B's notes)  │  │ (A's notes)  │  │  free        │
│  └──────────────┘  └──────────────┘  └──────────────┘  └──────────────┘
└──────────────────────────────────────────────────────────────┘
```

From the output (interleaved allocation so storage is scattered):

```
A.page_ids  = [0, 2]   (logical 0 -> phys 0, logical 1 -> phys 2)
A.page_lens = [2, 1]   (page 0 full, page 1 partial — the ONLY waste)
B.page_ids  = [1]      (logical 0 -> phys 1)
B.page_lens = [2]
pool.used   = [0, 1, 2]
pool.free   = [3, 4, 5, 6, 7]
```

**A's storage is scattered `[0, 2]` — non-contiguous!** A interleaved with B in the free list.

**Logical → Physical address translation for Request A** (`page_size=2`):

| logical pos `t` | `page_idx = t//PS` | `slot = t%PS` | `page_id = block_table[t//PS]` |
|-----------------|---------------------|---------------|-------------------------------|
| 0               | 0                   | 0             | 0                             |
| 1               | 0                   | 1             | 0                             |
| 2               | 1                   | 0             | **2**                         |

> **GOLD**: `A logical pos 2 → page_id 2, slot 0`

---

### Section F: The Paged Attention Kernel (Indirect K/V Gather)

The kernel gathers K,V from **scattered pages** via the block table. This is a FlashAttention variant where the K/V fetch is indirect.

**Indirect-lookup formula** (the heart of the kernel):
```
For logical token position `col` of request `batch`:
    page_idx = col // page_size                     # logical page
    slot     = col %  page_size                     # offset within page
    page_id  = block_table[batch, page_idx]         # OS page-table lookup
    k_idx    = ((page_id * H_kv + kv_head) * page_size + slot) * D + c
    score   += q[c] * key_pages[k_idx]             # dot-product contribution
```

**Contrast with dense sequential addressing:**
```
    k_ptr = k_base + (j * Bc + b) * D + c          # one slab, contiguous
```

**Worked example** (logical pos 2, head 0, dim 0):
```
page_idx = 2 // 2 = 1
slot     = 2 %  2 = 0
page_id  = block_table[1] = 1
k_idx    = ((1*2 + 0)*2 + 0)*8 + 0 = 32
K via formula   = 0.3010
K via tensor[…] = 0.3010  ✓ MATCH
```

**Attention output comparison** (token 2 as query, head 0, dims 0..3):
```
paged (indirect gather): [0.7067, 0.7077, 0.7087, 0.7097]
dense  (gather+matmul):  [0.7067, 0.7077, 0.7087, 0.7097]
[check] paged-attn == dense-attn at tol 1e-05: OK
```

---

### Section G: Paged == Dense == Raw (Invariant)

Building the same 4-token K cache three ways:

| path | K[0,0,0,:4] (token0) | K[0,0,3,:4] (token3) |
|------|-----------------------|-----------------------|
| no-cache (raw) | [0.101, 0.102, 0.103, 0.104] | [0.401, 0.402, 0.403, 0.404] |
| dense cache    | [0.101, 0.102, 0.103, 0.104] | [0.401, 0.402, 0.403, 0.404] |
| paged cache (PS=2) | [0.101, 0.102, 0.103, 0.104] | [0.401, 0.402, 0.403, 0.404] |

```
[check] ALL THREE PATHS MATCH: OK
```

PagedAttention only changes **where** the bytes live (scattered pages vs contiguous slab) — never **what** they are.

---

## Complexity & Trade-offs

| Metric | Dense Cache | Paged Cache | Notes |
|--------|------------|-------------|-------|
| Memory reserved | `[B,H_kv,max_len,d]` up-front | on-demand pages | Dense wastes 93.75% for short seqs |
| Worst-case waste | **93.75%** (one req) / **60–80%** (system) | **<4%** (system) | vLLM paper §3.2 |
| K/V addressing | sequential: `base + j*D` | indirect: `((page_id*H+head)*PS+slot)*D+c` | One extra indirection |
| Prefix sharing | impossible (private slabs) | ref-counted pages | CoW for forked sequences |
| Rewind (spec decode) | truncate offset | pop pages to free list | Use `ceil`, not `floor` |
| Throughput gain | baseline | **2–4× vs prior SOTA** | vLLM paper §5 |
| page_size tradeoff | — | smaller = finer sharing, more overhead | vLLM default: 16 |

---

## Common Interview Questions & How to Answer

### Q1: How does PagedAttention eliminate KV cache fragmentation?
- **Answer**: Dense KV caching pre-allocates `max_seq_len` slots per request at admission, wasting 93.75% for a 512-token sequence on an 8192 slot slab. PagedAttention uses the OS virtual-memory trick: a shared pool of fixed-size pages and a per-request block table mapping logical page indices to physical page ids. Pages are allocated on-demand and returned to the pool when the request finishes. The only waste is the last partial page per request — bounded by `1/page_size` (<4% in practice).

### Q2: Explain the block table and how the paged attention kernel uses it.
- **Answer**: The block table is the per-request logical→physical page index: `page_ids[logical_page] = physical_page_id`. For logical token position `t`, the kernel computes `page_idx = t // page_size`, `slot = t % page_size`, then looks up `page_id = block_table[page_idx]`. The K address is then `k_idx = ((page_id*H_kv + kv_head)*page_size + slot)*D + c`. This one extra indirection enables scattered physical storage. Concrete example: for logical pos 2 with page_size=2, `page_idx=1, slot=0, page_id=2, k_idx=32` — verified to produce K=0.3010, matching dense.

### Q3: What is the `rewind` operation and why must it use `ceil` not `floor`?
- **Answer**: `rewind(n)` undoes the last `n` appended K,V tokens during speculative decoding rejection. It computes `target_pages = ceil(new_offset / page_size)` and pops pages beyond that target to the free list. Using `floor` would be wrong at exact page boundaries: `offset=8, rewind(1)` → `new=7`, `ceil(7/4)=2` pages kept (correct: 4+3 tokens), but `floor(7/4)=1` would drop a still-needed page → silent data loss.

### Q4: How does PagedAttention enable prefix sharing across requests?
- **Answer**: Because pages are allocated from a shared pool with a block table, two requests that wrote identical token prefixes can reference the **same physical page** (ref-counted). The `BlockManager` uses content-addressing (chained hash of token ids) to detect when an incoming request's prefix matches an already-allocated page, and assigns it the same physical page id with `ref_count++`. This enables sharing system prompts, few-shot contexts, and chat history without recomputing KV.

### Q5: What are the two distinct waste numbers from the vLLM paper and what do each measure?
- **Answer**: (1) **93.75%**: per-request arithmetic `1 − 512/8192` — illustrates how wasteful dense pre-allocation is for one sequence. (2) **60–80%**: system-wide KV memory waste measured by vLLM across heterogeneous concurrent requests (internal + external fragmentation + over-reservation). PagedAttention brings this to **<4%** system-wide. Don't confuse the two — one is illustrative per-request math, the other is a production measurement.

---

## Pro-Tip: How to Impress the Interviewer

- **State the OS analogy precisely**: "blocks as pages, tokens as bytes, sequences as processes" — directly from the vLLM paper §3.1. This shows you've read the primary source.
- **Give the indirect-lookup formula**: `k_idx = ((page_id*H_kv + kv_head)*page_size + slot)*D + c`. Know it cold — interviewers love candidates who can trace through the address computation.
- **Mention the kernel equivalence proof**: paged and dense attention produce identical outputs (verified at tol 1e-05). PagedAttention changes *where* bytes live, never *what* they are.
- **Know the ceil vs floor trap**: `rewind` with `floor` at exact page multiples silently drops tokens. Always `ceil(new_offset / page_size)`.
- **Connect to throughput**: the 2–4× throughput gain comes almost entirely from fitting more concurrent sequences in the same GPU VRAM by eliminating wasted reservations.
