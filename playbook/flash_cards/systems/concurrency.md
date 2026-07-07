# Concurrency & Memory Allocation (Flashcards)

Click the bold text to reveal the answer. Click the file link for the full deep dive.

---

<details><summary><b>Implement a thread-safe bounded producer-consumer queue</b></summary>

Topic: Producer-Consumer Pattern (C++)
Key concepts:
- Backing store is a pre-allocated circular ring buffer (vector-backed) to avoid per-op heap allocation and keep cache lines hot; track `head_`, `tail_`, `size_` with modular indexing.
- Two condition variables (`cv_not_full_`, `cv_not_empty_`) + one mutex guard against spurious wakeups; `is_shutdown_` flag lets waiting threads terminate cleanly on graceful shutdown.
- Python `queue.Queue` serializes via the GIL (one bytecode thread at a time); bypass with `multiprocessing` queues (separate interpreters) for true parallel producers/consumers.
File: [system_lowlevel_concurrency_producer_consumer.md](../../system_lowlevel_concurrency_producer_consumer.md)
</details>

<details><summary><b>Build a lock-free SPSC queue and explain the memory ordering</b></summary>

Topic: Lock-Free Single-Producer Single-Consumer (SPSC) Queue
Key concepts:
- Power-of-two capacity lets modulo (`%`) become a bitwise AND (`&`); producer writes `tail`, consumer reads `head`, both `std::atomic`.
- Use acquire-release ordering: producer `store(release)` on tail after writing data so consumer `load(acquire)` sees it; full `seq_cst` is unnecessarily expensive. `_mm_pause()` prevents pipeline starvation on spin-waits.
- False sharing is eliminated by aligning `head` and `tail` to cache lines (`alignas(64)`); MESI/MOESI protocols bounce the line between cores otherwise, killing latency.
File: [system_lowlevel_concurrency_lock_free_queue.md](../../system_lowlevel_concurrency_lock_free_queue.md)
</details>

<details><summary><b>Implement aligned_malloc / aligned_free without platform APIs</b></summary>

Topic: Custom Aligned Memory Allocator
Key concepts:
- Allocate `bytes + alignment - 1 + sizeof(void*)` from `malloc`; the returned aligned pointer is `p2 = (p1 + sizeof(void*) + alignment - 1) & ~(alignment - 1)`, clearing low bits to round up.
- Store the original raw pointer in the bytes just before `p2` (`((void**)p2)[-1] = p1`) so `aligned_free` can recover and free the real block.
- Alignment is critical for SIMD vectorization (unaligned loads fault on some ISAs), cache line efficiency (avoid crossing 64-byte lines), and page boundaries. PyMalloc pools, NumPy's `ALIGNED` flag, and pybind11 capsules all lean on aligned allocations.
File: [system_lowlevel_memory_aligned_malloc.md](../../system_lowlevel_memory_aligned_malloc.md)
</details>

---

[Flashcard Index](../README.md)
