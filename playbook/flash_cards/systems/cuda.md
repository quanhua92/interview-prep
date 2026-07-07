# CUDA Execution Model (Flashcards)

Click the bold text to reveal the answer. Click the file link for the full deep dive.

---

<details><summary><b>What is warp divergence and how do you fix it?</b></summary>

Topic: CUDA Warp Divergence & SIMT Execution
Key concepts:
- SIMT schedules a warp of 32 threads lockstep on a warp scheduler; a divergent `if/else` serializes both paths, idling half the lanes each pass and halving throughput.
- Pre-Volta relied on a reconvergence stack with implicit rejoin at the post-dominator; Volta+ Independent Thread Scheduling (ITS) gives each thread its own PC/call-stack, loosening ordering but complicating reconvergence guarantees.
- Fix by warp-aligned loops (so the whole warp takes one branch), branchless predication (compiler replaces short branches with select instructions), or restructuring data so threads in a warp share the control flow. Nsight Compute `warp_execution_efficiency` flags divergence.
File: [system_lowlevel_cuda_warp_divergence.md](../../system_lowlevel_cuda_warp_divergence.md)
</details>

<details><summary><b>What are shared-memory bank conflicts and how is padding applied?</b></summary>

Topic: CUDA Shared Memory Bank Conflicts
Key concepts:
- Shared memory is split into 32 banks (one per warp lane); for 32-bit data, bank index is `(address / 4) % 32`. A warp accessing 32 different banks completes in one cycle (~1-3 cycles latency).
- A strided/column access where multiple lanes hit the same bank serializes into an N-way conflict (e.g., stride-32 read = 32-way conflict). Broadcast/multicast handle identical-address reads for free.
- Mitigation is padding: declare a `[TILE][TILE+1]` array so the column stride becomes 33 instead of 32, spreading accesses across banks. Nsight Compute `l1_tex__bank_conflicts` measures it.
File: [system_lowlevel_cuda_bank_conflicts.md](../../system_lowlevel_cuda_bank_conflicts.md)
</details>

<details><summary><b>How does global memory coalescing work, and why does layout matter?</b></summary>

Topic: CUDA Global Memory Coalescing
Key concepts:
- Memory controllers service 32-byte sector transactions; a warp issuing 32 contiguous 4-byte loads (128 bytes) coalesces into ~4 sector transactions, approaching HBM3 (~2-3 TB/s) / GDDR6 peak bandwidth.
- Strided or scattered access explodes the transaction count (each lane hits a different sector), wasting bandwidth. Structure-of-Arrays (SoA) layouts coalesce; Array-of-Structs (AoS) does not.
- PCIe Gen5 (~63 GB/s) and NVLink (~900 GB/s) carry H2D/D2H copies; align strides to 128-byte cache lines and use `cudaMemcpyAsync` with pinned host memory to overlap transfer and compute.
File: [system_lowlevel_cuda_global_memory_coalescing.md](../../system_lowlevel_cuda_global_memory_coalescing.md)
</details>

---

[Flashcard Index](../README.md)
