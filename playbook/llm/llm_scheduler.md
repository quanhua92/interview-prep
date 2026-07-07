# Continuous Batching & LLM Scheduler

- **Category**: LLM Systems
- **Difficulty**: Hard
- **Target Role**: LLM Inference Engineer / LLM Serving Engineer
- **Source**: Orca (OSDI 2022) / vLLM paper (SOSP 2023)
- **Flashcards**: [LLM Systems deck](../flash_cards/llm/llm_systems.md)

---

## Concept Overview

In standard deep learning serving, requests are batched together at the request level (**static batching**): the server waits for a batch of requests to arrive, runs them all together, and returns the results only when the longest request completes. For LLM generation, which is autoregressive (token-by-token), static batching leads to terrible GPU efficiency because different requests generate different numbers of tokens, leaving GPU cores idle while waiting for the longest request. 

The **LLM Scheduler** implements **continuous batching** (also known as iteration-level scheduling), making scheduling decisions after every single model forward pass (one token step). It manages a state machine that transitions requests from `WAITING` to `RUNNING` and `FINISHED`, dynamically inserting new prompts and evicting sequences on Out-Of-Memory (OOM) conditions.

### The Problem It Solves

Static batching pads shorter requests in a batch with dummy tokens until the longest request completes. If Request A needs 3 tokens and Request A's neighbor Request B needs 6 tokens, Request A's slot is padded and stays idle for 3 steps, wasting **25% or more** of GPU compute. 

Continuous batching solves this by immediately evicting Request A when it finishes, and slotting in a new waiting request (e.g., Request C) at the very next iteration. This raises GPU utilization from ~75% to **92%+** under heterogeneous workloads.

### How It Works

The scheduler orchestrates execution by running a cycle: **Schedule** $\rightarrow$ **Execute (Model Forward)** $\rightarrow$ **Postprocess**.

```text
               [*] (Request Arrives)
                │
                ▼
         ┌─────────────┐
         │   WAITING   │◄──────────────────────────┐
         └──────┬──────┘                           │
                │                                  │
                │ schedule() ->                    │ preempt() ->
                │ prefill prompt                   │ OOM during decode
                ▼                                  │ (re-queue FRONT)
         ┌─────────────┐                           │
         │   RUNNING   ├───────────────────────────┘
         └──────┬──────┘
                │
                │ postprocess() ->
                │ EOS / max_tokens reached
                ▼
         ┌─────────────┐
         │  FINISHED   │
         └──────┬──────┘
                │
                ▼
               [*] (Release KV blocks)
```

* **Prefill Priority**: New prompts in the `WAITING` queue are scheduled before running decodes to minimize Time-to-First-Token (TTFT).
* **Chunked Prefill**: Processing a massive prompt (e.g., 8192 tokens) in a single step would starve all active decodes. The scheduler chunks long prompts over multiple steps using `num_cached_tokens` to track progress. To prevent multiple prompts from starting and chunking simultaneously, **only the first sequence in the waiting queue is allowed to chunk per step**.
* **Preemption (Recompute Mode)**: If a decode step needs a new block and the VRAM pool is empty, the scheduler evicts the **newest** running sequence back to `WAITING` at the front of the queue, freeing its physical blocks. It will be re-prefilled from its cached token boundary once VRAM is free.

---

## Worked Example

### 1. Static vs. Continuous Batching Timeline
Consider two requests: R0 requires 3 tokens, R1 requires 6 tokens. Later, R2 arrives requiring 2 tokens.

**Static Batching Timeline (wastes 3 slots; 75% useful):**
* Steps 1–3: R0 and R1 both execute.
* Steps 4–6: R0 is finished. Its slot is padded with idle work. R1 continues executing.
* R2 must wait until Step 7 to begin.

**Continuous Batching Timeline (wastes 1 slot; 92% useful):**
* Steps 1–3: R0 and R1 both execute.
* Step 4: R0 finishes. **R2 immediately slots into R0's freed seat**.
* Steps 5–6: R1 and R2 execute. R2 finishes at Step 5, and R1 finishes at Step 6.

### 2. Decode Preemption Trace
* **VRAM Pool**: 2 physical blocks.
* **Running Queue**: `[s0, s1]`. Each holds 1 block. VRAM is full (`free = 0`).
* **Decode Step**: Sequence 0 generates a token that crosses a block boundary (length grows $2 \rightarrow 3$). It needs a new physical block, but none are free.
* **Preemption Action**: The scheduler pops the newest sequence (`s1`) from the running queue, deallocates its blocks, sets its status to `WAITING` and `is_prefill = True`, and pushes it to the **front** of the waiting queue.
* **Result**: `s1`'s block is freed and immediately allocated to `s0`, allowing `s0` to complete its decode step.

### 3. Full Multi-Step Schedule Trace
We trace three sequences with prompt lengths `[3, 5, 2]` under a budget of `max_num_batched_tokens = 4`, `block_size = 2`, and `max_tokens = 2`.

| Step | Scheduled Sequences (Seq:Tokens) | Total Tokens | Is Prefill? | Notes |
|---|---|---|---|---|
| **1** | `seq0: 3` | 3 | True | `seq0` fits fully in the budget of 4. |
| **2** | `seq1: 4` | 4 | True | `seq1` needs 5 tokens. It is **chunked** (4 scheduled). `seq1` stays WAITING. |
| **3** | `seq1: 1`, `seq2: 2` | 3 | True | `seq1` tail (1 token) + `seq2` full prompt (2 tokens) scheduled. |
| **4** | `seq0: 1`, `seq1: 1`, `seq2: 1` | 3 | False | **Decode Step**: All three generate 1 token, hit `max_tokens=2`, and finish. |

**Sequence 1 `num_cached_tokens` growth**: `0 -> 4 -> 5 -> 6`. It caches 4 prompt tokens in Step 2, completes the last prompt token in Step 3, and decodes in Step 4.

**Why `seq0` Idled in Steps 2–3**:
Because new prefills (`seq1` and `seq2`) have priority over active decodes to keep TTFT low, `seq0` must wait for the prefill queue to clear before it is allowed to decode.

---

## Complexity & Trade-offs

| Metric | Value / Behavior | Notes |
|---|---|---|
| **Scheduling Overhead** | $\mathcal{O}(\text{active\_sequences})$ | Executed on the CPU every step. Must be kept $< 1$ ms to avoid stalling the GPU. |
| **Budget Limit** | `max_num_batched_tokens` | Limits the number of tokens processed in a single forward pass to prevent GPU out-of-memory. |
| **Preemption Recovery** | **Recomputation** (Default) | Discards KV cache and re-prefills. Wastes GPU compute but requires no PCIe transfer overhead. |
| **Preemption Recovery** | **Swapping** | Swaps KV cache to CPU RAM. Saves compute but introduces high PCIe copy latency. |

### Prefill vs. Decode Co-batching Trade-offs
* **Separate Steps** (nano-vllm default):
  * *Pros*: Simple to batch. Keeps CUDA shapes uniform (either all prefill matrix-multiplication kernels or all decode vector-matrix kernels).
  * *Cons*: Prefilled sequences must idle while waiting for other sequences' prefill chunks to complete.
* **Mixed Co-batching** (production vLLM):
  * *Pros*: High GPU efficiency by overlapping compute-bound prefills with memory-bound decodes in the same forward pass.
  * *Cons*: Requires complex attention kernels (e.g., FlashDecoding) that can handle heterogeneous query lengths and block offsets.

---

## Common Interview Questions & How to Answer

### Q1: What is continuous batching (iteration-level scheduling) and how does it improve serving throughput compared to static batching?
- **Answer**: Static batching treats a batch as a single unit, running all sequences to completion and padding finished slots with dummy work. Continuous batching schedules at the iteration level (one forward pass/token generation). It inspects the batch after every step, allowing completed sequences to be released and new sequences to be added immediately. This eliminates padding waste and significantly increases GPU occupancy under varying sequence lengths.

### Q2: How does the scheduler handle preemption when VRAM is exhausted, and how does it determine which sequence to preempt?
- **Answer**: When a decode step requires a new KV block but the memory manager has none free, the scheduler must preempt one or more sequences. It preempts sequences in reverse-chronological order, evicting the **newest running sequence** first. This sequence's physical blocks are deallocated, its state is set back to `WAITING` with `is_prefill = True`, and it is re-queued at the **front** of the waiting queue. The newest sequence is chosen because it has completed the least amount of generation work, minimizing the wasted GPU compute of recomputation. Under First-Come-First-Serve (FCFS) scheduling, evicting the newest sequence approximates a Least Recently Used (LRU) policy.

### Q3: Why does chunked prefill restrict chunking to only the first waiting sequence per step?
- **Answer**: If multiple waiting sequences were allowed to chunk simultaneously, each would consume a portion of the step's token budget, causing a "parade" of partial prefill chunks that would continuously starve active decode sequences. By restricting chunking to only the first sequence in the waiting queue, the scheduler ensures at most one sequence runs in a partial chunked prefill state. Once it completes its prefill and transitions to `RUNNING`, the next sequence in line can begin chunking. This protects active decodes from long-term latency starvation.

---

## Pro-Tip: How to Impress the Interviewer

- **TTFT vs. ITL Trade-off**: Explain that while prefill priority minimizes Time-To-First-Token (TTFT), it can cause Inter-Token Latency (ITL) spikes for already-running decodes. In production, serving systems use **chunked prefill co-batching** to limit the maximum number of prefill tokens per step. By mixing small prefill chunks with decodes, they bound the step latency, keeping ITL smooth while maintaining reasonable TTFT.
