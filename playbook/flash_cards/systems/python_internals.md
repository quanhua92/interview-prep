# Python Internals & PyTorch Systems (Flashcards)

Click the bold text to reveal the answer. Click the file link for the full deep dive.

---

<details><summary><b>Explain the Python GIL and how to bypass it for CPU-bound work</b></summary>

Topic: Python GIL & High-Performance Concurrency
Key concepts:
- GIL is a single mutex protecting all bytecode execution; exists because CPython uses non-thread-safe reference counting. Without it, two threads mutating `ob_refcnt` would corrupt memory.
- Since Python 3.2 the GIL uses a condition variable + mutex with `sys.getswitchinterval()` (default 5 ms) instead of the old 100-bytecode ticker, which fixes the convoy effect.
- Bypass routes: release the GIL in C extensions (`Py_BEGIN_ALLOW_THREADS`), use `multiprocessing` (separate interpreters), or PEP 703 free-threaded build (no-GIL). Zero-copy IPC via `multiprocessing.shared_memory` avoids pickle overhead between processes.
File: [system_lowlevel_python_gil_concurrency.md](../../system_lowlevel_python_gil_concurrency.md)
</details>

<details><summary><b>How does CPython manage memory? (ref counting, cyclic GC, PyMalloc)</b></summary>

Topic: Python Memory Management & Garbage Collection
Key concepts:
- Primary reclamation is reference counting (`Py_INCREF`/`Py_DECREF` in `PyObject.ob_refcnt`); when refcount hits 0 the object is freed immediately. Fails on reference cycles.
- Cyclic GC handles unreachable cycles across 3 generations; uses `gc_refs` to find unreachable subgraphs and runs when generation thresholds are exceeded.
- PyMalloc layers: Arenas (256 KB) → Pools (4 KB) → Blocks, cutting OS fragmentation for small objects. PyTorch CUDA leak debugging uses `gc`, `tracemalloc`, `objgraph` to find retained loss-graph tensors causing CUDA OOM.
File: [system_lowlevel_python_memory_gc.md](../../system_lowlevel_python_memory_gc.md)
</details>

<details><summary><b>Compare ctypes / cffi / pybind11 / Cython and how to pass memory safely</b></summary>

Topic: Python C-Bindings & Foreign Function Interfaces (FFI)
Key concepts:
- ctypes: no compile step but ~50-150 ns/call overhead (dynamic arg checking). cffi (~5-20 ns API mode), pybind11 (~5-15 ns, C++ objects/CUDA), Cython (<=5 ns, hybrid algos).
- Zero-copy NumPy transfer: array must be C-contiguous; pass `.ctypes.data` raw pointer with `numpy.ctypeslib.ndpointer` enforcing dtype/shape in `argtypes`. C writes straight to the buffer.
- Three ownership models (Python alloc/frees, C alloc/frees, C alloc/Python frees); prevent leaks/segfaults with custom RAII wrappers and explicit lifetime control rather than raw pointer exchange.
File: [system_lowlevel_python_c_bindings_ctypes.md](../../system_lowlevel_python_c_bindings_ctypes.md)
</details>

<details><summary><b>Optimize PyTorch at the systems level for 10B-100B parameter training</b></summary>

Topic: PyTorch Systems-Level Optimization
Key concepts:
- DDP replicates full model states on every GPU; FSDP/ZeRO-3 shards optimizer states + gradients + parameters and reconstitutes them via All-Gather (forward) and Reduce-Scatter (backward). ZeRO-1 shards only optimizer states.
- `torch.compile` path: TorchDynamo (graph capture) → AOTAutograd (backward graph) → TorchInductor (kernel fusion). CUDA Graphs replay a recorded stream to eliminate per-op CPU launch overhead.
- Mixed precision: FP16 needs dynamic loss scaling; BF16 has wide exponent range (no scaling). Activation checkpointing trades compute for memory. Triton block-programming model beats raw C++/CUDA for fused custom kernels.
File: [system_lowlevel_pytorch_systems_optimization.md](../../system_lowlevel_pytorch_systems_optimization.md)
</details>

---

[Flashcard Index](../README.md)
