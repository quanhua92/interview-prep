# CUDA Global Memory Coalescing

**Category**: Low-level Systems / CUDA
**Difficulty**: Medium / Hard
**Target Role**: Low-Level Developer / AI Kernel Engineer / GPU Architecture Engineer
**Flashcards**: [CUDA deck](flash_cards/systems/cuda.md)

---

## Question Description

NVIDIA GPUs offer massive peak memory bandwidth, but achieving it requires satisfying **Global Memory Coalescing** requirements.

1. **Hardware Mechanics**: Describe the hardware pathways of GPU global memory access (GDDR6 vs. HBM2/3/3e, memory controller routing, L1/L2 cache lines, and 32-byte sector transactions).
2. **Memory Coalescing**: Explain how a warp-wide access pattern affects the number of memory transactions issued. Show how data structure design (SoA vs. AoS) impacts coalescing.
3. **Optimized Implementation**: Provide a complete CUDA C++ kernel showcasing coalesced vs. strided memory copy with host-side benchmarks and validation.
4. **Verification**: Explain the exact Nsight Compute metrics used to analyze memory bandwidth efficiency.

---

## 1. Hardware Mechanics of Global Memory Access

GPU global memory is implemented using either **GDDR6** (Graphics Double Data Rate 6) or **HBM2/3/3e** (High Bandwidth Memory). 

```text
┌─ Warp (32 Threads) ─────────────────────────────┐
│                                                 │
│   ┌──────────────────────────┐                  │
│   │ Warp Instruction         │                  │
│   │      (Load/Store)        │                  │
│   └────────────┬─────────────┘                  │
│                │                                │
│                ▼                                │
│   ┌──────────────────────────┐                  │
│   │  Load/Store Unit (SM)    │                  │
│   └────────────┬─────────────┘                  │
└────────────────┼────────────────────────────────┘
                 │
                 ▼
┌─ Cache Hierarchy ───────────────────────────────┐
│   ┌──────────────────────────┐                  │
│   │ L1 Cache / Shared Memory │                  │
│   │   (128-Byte Lines)       │                  │
│   └────────────┬─────────────┘                  │
│                │                                │
│                ▼                                │
│   ┌──────────────────────────┐                  │
│   │ L2 Cache (partitioned    │                  │
│   │   by memory channels)    │                  │
│   └────────────┬─────────────┘                  │
└────────────────┼────────────────────────────────┘
                 │
                 ▼
┌─ Device Memory ─────────────────────────────────┐
│   ┌──────────────────────────┐                  │
│   │   Memory Controllers     │                  │
│   └────────────┬─────────────┘                  │
│                │                                │
│                ▼                                │
│   ┌──────────────────────────┐                  │
│   │ HBM / GDDR Physical Mem  │                  │
│   └──────────────────────────┘                  │
└─────────────────────────────────────────────────┘
```

### High Bandwidth Memory (HBM) vs. GDDR6
*   **GDDR6**: Uses a narrow physical bus (typically 32 bits per channel, aggregate 256-bit to 384-bit interface per GPU) operating at high frequencies (~16-20 Gbps). Peak bandwidth is around 500-1000 GB/s.
*   **HBM2/3/3e**: Stacked DRAM dies connected via a silicon interposer to the GPU. Features an ultra-wide bus interface (**1024 bits per HBM stack**). A GPU like the H100 utilizes 5 or 6 HBM3 stacks, creating a massive **5120-bit or 6144-bit memory bus** operating at ~3.2 Gbps, providing **3.35 TB/s to 4.8 TB/s** of bandwidth.
*   **Latency vs Bandwidth**: Physical memory latency for global memory accesses remains high: **100 to 150 ns**, translating to **200 to 400 clock cycles** on HBM2/3, and **400 to 800 clock cycles** on GDDR6. Warp schedulers hide this by switching execution to other active, eligible warps.
*   **Host-to-Device Bottlenecks**: Global memory bandwidth (TB/s) is orders of magnitude higher than host-to-device transfers. PCIe Gen5 x16 provides a peak of **63 GB/s**, while custom GPU-to-GPU interconnects like NVIDIA NVLink 4.0 provide **900 GB/s** bidirectional bandwidth.

### Transaction Granularity (Sectors and Cache Lines)
*   **Cache Line**: L1 and L2 cache lines are **128 bytes** wide.
*   **Sectors**: Each 128-byte cache line is divided into four physical **32-byte sectors**.
*   **Memory Controller (MC) Transactions**: The physical memory interface accesses memory at the granularity of a 32-byte sector. Therefore, if a warp requests data, the Load/Store Unit (LSU) detects which unique 32-byte sectors are covered by the active threads' target addresses.
*   **LSU Coalescing**:
    *   **Fully Coalesced**: If 32 threads read/write contiguous 4-byte values (e.g., `float`, `int32_t`) aligned to a 128-byte boundary, they span exactly four 32-byte sectors. The LSU executes a **single 128-byte transaction** (4 sectors) over the memory bus.
    *   **Strided**: If threads access memory with stride $K$, the footprint spans $128 \times K$ bytes. If $K=2$, the footprint is 256 bytes, requiring the LSU to request 8 sectors (two 128-byte transactions). Only half of the loaded bytes are utilized, reducing efficiency to $50\%$. For $K \ge 8$, the 32 threads request 32 separate sectors, causing 32 transactions. This represents the worst-case scenario: $\approx 12.5\%$ bandwidth efficiency (4 bytes used per 32-byte sector).

```
Coalesced (Stride 1, 32-bit float):
Thread: | 0 | 1 | 2 | ... | 31 | (Contiguous 128 bytes)
Sectors: [  Sec 0  ][  Sec 1  ][  Sec 2  ][  Sec 3  ] (Single 128-byte transaction)

Strided (Stride 2, 32-bit float):
Thread: | 0 |   | 1 |   | ... | 31 | (Spans 256 bytes)
Sectors: [Sec 0][Sec 1][Sec 2][Sec 3][Sec 4][Sec 5][Sec 6][Sec 7] (Two 128-byte transactions, 50% efficiency)
```

*   **Fully Coalesced**: If 32 threads access contiguous 4-byte values aligned to a 128-byte boundary, the warp's requests are completed in a **single 128-byte transaction** (4 sectors).
*   **Strided**: If threads access memory with a stride $K$, the memory footprint spans $128 \times K$ bytes, forcing the LSU to execute multiple 32-byte sector transactions, reducing bandwidth efficiency to $\approx \frac{100}{K}\%$.

---

## 2. Structure of Arrays (SoA) vs. Array of Structures (AoS)

Data layout in global memory is critical for coalescing:

*   **Array of Structures (AoS)**:
    ```cpp
    struct Particle { float x; float y; float z; };
    Particle particles[N]; // AoS
    ```
    If a kernel only accesses the `x` field, thread $i$ reads `particles[i].x`, which is separated from `particles[i+1].x` by the size of `y` and `z` (a stride of 3 words, or 12 bytes). This results in uncoalesced loads.
*   **Structure of Arrays (SoA)**:
    ```cpp
    struct Particles { float* x; float* y; float* z; }; // SoA
    ```
    If a kernel accesses `x`, thread $i$ reads `particles.x[i]`. Adjacent threads read contiguous floats, enabling 100% coalesced access.

---

## 3. CUDA C++ Coalesced vs. Strided Copy Implementation

```cpp
#include <cuda_runtime.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <stdexcept>
#include <string>

#define CUDA_CHECK(call)                                                      \
    do {                                                                      \
        cudaError_t err = (call);                                             \
        if (err != cudaSuccess) {                                             \
            throw std::runtime_error(std::string("CUDA Error: ") +            \
                                     cudaGetErrorString(err) + " at " +       \
                                     __FILE__ + ":" + std::to_string(__LINE__));\
        }                                                                     \
    } while (0)

inline void check_kernel_execution(const std::string& name) {
    CUDA_CHECK(cudaGetLastError());
    CUDA_CHECK(cudaDeviceSynchronize());
}

// ============================================================================
// 1. Coalesced Copy (Stride = 1)
// ============================================================================
__global__ void coalescedCopy(float* __restrict__ d_out, const float* __restrict__ d_in, int N) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx < N) {
        d_out[idx] = d_in[idx];
    }
}

// ============================================================================
// 2. Strided Copy (Stride > 1)
// ============================================================================
__global__ void stridedCopy(float* __restrict__ d_out, const float* __restrict__ d_in, int stride, int N) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    int target_idx = idx * stride;
    if (target_idx < N) {
        d_out[target_idx] = d_in[target_idx];
    }
}

int main() {
    try {
        const int N = 1 << 24; // 16M elements
        const size_t bytes = N * sizeof(float);
        const int stride = 4;

        if (N <= 0 || stride <= 0) {
            throw std::invalid_argument("N and stride must be positive integers.");
        }

        std::vector<float> h_in(N);
        std::vector<float> h_out(N, 0.0f);
        for (int i = 0; i < N; ++i) {
            h_in[i] = static_cast<float>(i);
        }

        float *d_in = nullptr, *d_out = nullptr;
        CUDA_CHECK(cudaMalloc(&d_in, bytes));
        CUDA_CHECK(cudaMalloc(&d_out, bytes));

        CUDA_CHECK(cudaMemcpy(d_in, h_in.data(), bytes, cudaMemcpyHostToDevice));
        CUDA_CHECK(cudaMemset(d_out, 0, bytes));

        int blockSize = 256;
        int numBlocks = (N + blockSize - 1) / blockSize;

        cudaEvent_t start, stop;
        CUDA_CHECK(cudaEventCreate(&start));
        CUDA_CHECK(cudaEventCreate(&stop));
        float ms = 0.0f;

        // ----------------------------------------------------
        // 1. Run Coalesced Copy
        // ----------------------------------------------------
        CUDA_CHECK(cudaEventRecord(start));
        coalescedCopy<<<numBlocks, blockSize>>>(d_out, d_in, N);
        CUDA_CHECK(cudaEventRecord(stop));
        check_kernel_execution("coalescedCopy");
        CUDA_CHECK(cudaEventElapsedTime(&ms, start, stop));

        // Effective Bandwidth = (Bytes Read + Bytes Written) / Time
        double coalesced_bw = (2.0 * bytes) / (ms / 1000.0) / 1e9;
        std::cout << "Coalesced Copy Time: " << ms << " ms (" << coalesced_bw << " GB/s)\n";

        // Verify correctness of coalesced copy
        CUDA_CHECK(cudaMemcpy(h_out.data(), d_out, bytes, cudaMemcpyDeviceToHost));
        for (int i = 0; i < N; ++i) {
            if (std::abs(h_out[i] - h_in[i]) > 1e-5f) {
                throw std::runtime_error("Coalesced validation failed!");
            }
        }

        // Reset output
        CUDA_CHECK(cudaMemset(d_out, 0, bytes));

        // ----------------------------------------------------
        // 2. Run Strided Copy
        // ----------------------------------------------------
        int stridedBlocks = (N / stride + blockSize - 1) / blockSize;
        CUDA_CHECK(cudaEventRecord(start));
        stridedCopy<<<stridedBlocks, blockSize>>>(d_out, d_in, stride, N);
        CUDA_CHECK(cudaEventRecord(stop));
        check_kernel_execution("stridedCopy");
        CUDA_CHECK(cudaEventElapsedTime(&ms, start, stop));

        // Strided copy writes/reads only (N / stride) elements
        size_t strided_bytes = (N / stride) * sizeof(float);
        double strided_bw = (2.0 * strided_bytes) / (ms / 1000.0) / 1e9;
        std::cout << "Strided Copy (Stride=" << stride << ") Time: " << ms << " ms (" << strided_bw << " GB/s)\n";

        // Cleanup
        CUDA_CHECK(cudaFree(d_in));
        CUDA_CHECK(cudaFree(d_out));
        CUDA_CHECK(cudaEventDestroy(start));
        CUDA_CHECK(cudaEventDestroy(stop));

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
```

---

## 4. Complexity & Performance Analysis

| Metric | Coalesced Access | Strided Access (Stride = $K$) |
| :--- | :--- | :--- |
| **Transaction Count** | 1 per 128 bytes (Warp) | $K$ per 128 bytes (up to 32) |
| **Bandwidth Efficiency** | $\approx 100\%$ | $\approx \frac{100}{K}\%$ |
| **Time Complexity** | $\mathcal{O}(\frac{N}{\text{threads}})$ | $\mathcal{O}(\frac{N}{\text{threads}})$ (Memory bottlenecked) |

---

## 5. Common Follow-Up Questions & How to Answer

### Q1: How does the L1 Cache Mode (Caching vs. Non-caching) affect Coalescing?
**A**: Under the hood, memory load instructions can be modified at the PTX assembly level:
*   **Cache at L1 and L2 (`ld.ca`)**: The L1 cache line size is 128 bytes. The memory fetch granularity is a full 128-byte block. Misaligned or strided loads here fetch the entire 128 bytes, which can lead to high waste if threads only use small chunks.
*   **Cache at L2 only (`ld.cg` - Cache Global)**: Bypasses the L1 cache. The transaction size drops to the 32-byte sector level. For sparse or scattered access, `ld.cg` is significantly faster because it only fetches the requested 32-byte sectors, conserving L2 cache capacity and memory bus bandwidth.

### Q2: How does `cudaMallocPitch` ensure coalesced memory access for 2D matrices?
**A**: A 2D matrix dynamic allocation via `cudaMalloc` can result in rows that are not aligned to 128-byte boundaries (e.g., if width is 33 floats, row 1 starts at byte 132). This causes misalignment for all subsequent rows.
*   `cudaMallocPitch(&d_ptr, &pitch, width_bytes, height)` allocates the matrix with **row padding** (pitch).
*   The GPU guarantees that each row's start address is aligned to the hardware coalescing boundaries (e.g., multiples of 256 bytes). 
*   In the kernel, developers access elements using the pitch stride:
    `float* row = (float*)((char*)d_ptr + y * pitch); float val = row[x];`.

### Q3: What is the purpose of the `__ldg()` intrinsic?
**A**: `__ldg()` directs the compiler to route global memory reads through the read-only data cache (also known as the texture cache). 
*   This cache is optimized for spatial locality and uses 32-byte cache lines.
*   It is particularly useful for irregular, read-only accesses where bypassing L1 standard cache reduces cache pollution.
*   Modern NVCC compilers automatically insert `__ldg()` if the kernel argument has `const __restrict__` qualifiers and the compiler can prove the data is read-only.

---

## 6. Python Integration & GIL Context

When orchestrating GPU workloads from Python (via **PyCUDA**, **CuPy**, or **Numba**), Global Memory Coalescing remains the primary driver of memory bandwidth. However, Python's internal memory management introduces unique constraints:

### 1. Bypassing the GIL for High-Throughput Compute
The Global Interpreter Lock (GIL) is completely bypassed during GPU kernel execution:
*   **Compilation**: Libraries like Numba (`@cuda.jit`) translate Python code to LLVM IR and compile it directly to machine-level SASS, bypassing the Python bytecode interpreter.
*   **Execution**: When launching a kernel, the GIL is released by the runtime (e.g., CuPy or Numba). The GPU's Load/Store Units (LSUs) perform physical hardware coalescing independent of CPU states or locks.

### 2. NumPy Stride Behaviors and Coalescing Hazards
In Python, NumPy and CuPy utilize a **stride array** metadata system. Strides define the step size in bytes needed to move to the next element along any dimension.
*   **Slicing and Strided Copies**: Slicing an array in Python (e.g., `sliced_arr = arr[::2]`) does *not* copy data in memory; it merely updates the stride metadata (doubling the step size).
*   **The Hazard**: If you pass `sliced_arr` to a Numba kernel:
    ```python
    @cuda.jit
    def process_kernel(d_arr):
        idx = cuda.grid(1)
        # Even though idx is contiguous (0, 1, 2...), the underlying pointer
        # has a stride of 2 elements, forcing uncoalesced 32-byte sector reads!
        val = d_arr[idx] 
    ```
*   **Solution**: Convert strided/sliced arrays to a C-contiguous layout in memory using `cp.ascontiguousarray(sliced_arr)` or `np.ascontiguousarray()` before passing them to the GPU.

### 3. Structure of Arrays (SoA) in Python
Python developers often use NumPy's structured arrays:
```python
# NumPy AoS (Array of Structures) representation
particles_aos = np.zeros(N, dtype=[('x', 'f4'), ('y', 'f4'), ('z', 'f4')])
```
While convenient, passing a structured array to the GPU results in an **AoS** layout, degrading coalescing efficiency. To achieve optimal coalescing, developers must structure data as **SoA**:
```python
# NumPy/CuPy SoA (Structure of Arrays) representation
x = cp.zeros(N, dtype=cp.float32)
y = cp.zeros(N, dtype=cp.float32)
z = cp.zeros(N, dtype=cp.float32)
```

---

## 7. Pro-Tip: How to Impress the Interviewer

*   **Key Terms**: "32-byte cache sectors", "L1/L2 cache line granularity", "LDG/STG instructions", "`ld.cg` vs `ld.ca` PTX cache modifiers", "Dynamic Row Pitch Alignment (`cudaMallocPitch`)", "Structure of Arrays (SoA)", "Texture/Read-Only Cache routing".
*   **Common Mistakes to Avoid**:
    *   *Mistake*: Confusing GPU memory coalescing with CPU cache prefetching. *Correction*: CPU caches fetch contiguous blocks for sequential reuse *by a single thread* over time (temporal/spatial locality). GPUs coalesce memory *across 32 parallel threads* within the same clock cycle.
    *   *Mistake*: Thinking coalesced access must be ordered by thread ID (e.g., thread 0 must access index 0, thread 1 index 1). *Correction*: The LSU only cares if the requested addresses fall within the same 32-byte sectors. The mapping of thread ID to offset can be permuted or out-of-order, and it will still coalesce.
