# CUDA Shared Memory Bank Conflicts and Padding

**Category**: Low-level Systems / CUDA
**Difficulty**: Hard
**Target Role**: Low-Level Developer / AI Kernel Engineer / GPU Architect
**Flashcards**: [CUDA deck](flash_cards/systems/cuda.md)

---

## Question Description

Shared memory in NVIDIA GPUs is a high-bandwidth, software-managed L1 cache. However, improper access patterns can trigger **Bank Conflicts**, which serialize memory accesses and degrade throughput.

1. **Hardware Architecture**: Detail the internal architecture of CUDA Shared Memory, including bank division, bank addressing math for 32-bit and 64-bit data types, and how the Load/Store Unit (LSU) handles concurrent accesses (broadcast, multicast, conflicts).
2. **Matrix Transpose Implementation**: Provide a complete CUDA C++ implementation of Matrix Transpose demonstrating bank conflicts and their mitigation using the **Padding** technique.
3. **Verification & Profiling**: Explain the exact Nsight Compute metrics to identify and measure bank conflicts in production.

---

## 1. Architectural Deep Dive: Shared Memory and Banks

### The 32-Bank Structure
Shared memory is physically partitioned into **32 independent memory modules (banks)** that can be accessed simultaneously. This matches the number of threads in a warp (32).

```
Without Padding (Stride 32):
Row 0: | Bank 0 (W0) | Bank 1 (W1) | ... | Bank 31 (W31) |
Row 1: | Bank 0 (W32)| Bank 1 (W33)| ... | Bank 31 (W63) |  <-- Column read (W0, W32...) hits Bank 0 (32-way conflict)

With Padding (Stride 33):
Row 0: | Bank 0 (W0) | Bank 1 (W1) | ... | Bank 31 (W31) | Bank 0 (PAD) |
Row 1: | Bank 1 (W32)| Bank 2 (W33)| ... | Bank 0 (W63)  | Bank 1 (PAD) |  <-- Column read (W0, W32...) hits Bank 0, Bank 1 (Conflict-free!)
```

### Bank Addressing Math & Latency Context
Shared memory is physically located on the Streaming Multiprocessor (SM) chip, yielding extremely low latency: typically **1 to 3 clock cycles**, compared to the **200 to 400 cycles** of High-Bandwidth Memory (HBM2/HBM3) or **400 to 800 cycles** of GDDR6 global memory. Because shared memory is designed to act as a high-speed scratchpad, bank conflicts that serialize access degrade performance severely—stalling the SM sub-core pipeline.

For 32-bit (4-byte) data types (e.g., `float`, `int32_t`), successive words map to successive banks. The mapping from byte address $A$ to bank index $B$ is:
$$B = \left( \frac{A}{4} \right) \pmod{32}$$

*   **Conflict-Free**: When all 32 threads in a warp access different banks, the Load/Store Unit (LSU) crossbar switch routes all requests in parallel in a single cycle.
*   **Broadcast**: If all threads in a warp read the *exact same address*, the LSU broadcasts the data to all threads in a single cycle (0 conflicts).
*   **Multicast**: If multiple threads read the same address, and other threads read distinct banks, the hardware multicasts the shared address and reads the other banks in parallel (0 conflicts).
*   **Bank Conflict**: When two or more threads request different addresses that map to the **same bank**, the crossbar routing logic is blocked. An $N$-way conflict requires the LSU to split the transaction into $N$ sequential phases, taking $N \times$ longer.

### 64-bit (8-byte) vs 16-bit (2-byte) Data Types
1.  **64-bit (`double`, `float2`)**:
    *   **4-Byte Bank Mode (Default)**: Each 64-bit access spans two adjacent 32-bit banks. A thread accessing a double at byte address $A$ requests banks:
        $$B_{even} = \left( \frac{A}{4} \right) \pmod{32}, \quad B_{odd} = \left( \frac{A}{4} + 1 \right) \pmod{32}$$
        If a warp accesses a sequential `double` array with stride 1, thread $i$ targets banks $2i \pmod{32}$ and $2i+1 \pmod{32}$. Because two threads map to each bank (e.g., thread 0 and thread 16 both access bank 0), this forces a 2-way bank conflict.
    *   **8-Byte Bank Mode**: GPUs can be configured to use 8-byte physical bank sizes using:
        `cudaDeviceSetSharedMemConfig(cudaSharedMemBankSizeEightByte)`.
        In this mode, the mapping becomes:
        $$B = \left( \frac{A}{8} \right) \pmod{32}$$
        Sequential 8-byte accesses map to consecutive banks, eliminating the conflict.
2.  **16-bit (`half`, `short`)**: Multiple threads might access different 16-bit values within the same 32-bit bank. In modern architectures (Kepler+), the LSU supports sub-word addressing, which is conflict-free as long as threads access distinct 16-bit offsets within the bank.

---

## 2. Complete CUDA C++ Implementation

The following code implements Matrix Transpose using a 2D grid. It contains a CPU verification reference to guarantee correctness and benchmarks the conflict-prone vs. padded kernels.

```cpp
#include <cuda_runtime.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <stdexcept>
#include <string>

#define TILE_DIM 32
#define BLOCK_ROWS 8

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
// 1. Matrix Transpose with Bank Conflicts
// The shared memory tile has dimensions [TILE_DIM][TILE_DIM].
// Writing columns to global memory requires reading columns from shared memory,
// causing a 32-way bank conflict.
// ============================================================================
__global__ void transposeWithConflicts(float* __restrict__ odata, 
                                       const float* __restrict__ idata, 
                                       int width, int height) {
    __shared__ float tile[TILE_DIM][TILE_DIM];

    int x = blockIdx.x * TILE_DIM + threadIdx.x;
    int y = blockIdx.y * TILE_DIM + threadIdx.y;

    // Read coalesced from global memory, write to shared memory
    for (int j = 0; j < TILE_DIM; j += BLOCK_ROWS) {
        if (x < width && (y + j) < height) {
            tile[threadIdx.y + j][threadIdx.x] = idata[(y + j) * width + x];
        }
    }

    __syncthreads();

    // Read from shared memory transposed (conflict!) and write coalesced to global
    int x_t = blockIdx.y * TILE_DIM + threadIdx.x;
    int y_t = blockIdx.x * TILE_DIM + threadIdx.y;

    for (int j = 0; j < TILE_DIM; j += BLOCK_ROWS) {
        if (x_t < height && (y_t + j) < width) {
            // Because threadIdx.x varies and threadIdx.y + j is static for a warp step,
            // tile[threadIdx.x][threadIdx.y + j] accesses column elements.
            // Since TILE_DIM is 32, every row is exactly 32 words wide.
            // (threadIdx.x * 32) % 32 = 0 -> All threads map to Bank 0 (32-way conflict).
            odata[(y_t + j) * height + x_t] = tile[threadIdx.x][threadIdx.y + j];
        }
    }
}

// ============================================================================
// 2. Matrix Transpose with Padding (Conflict-Free)
// The shared memory tile has dimensions [TILE_DIM][TILE_DIM + 1].
// Adding 1 extra column changes the row stride to 33, skewing the bank alignment.
// ============================================================================
__global__ void transposeWithPadding(float* __restrict__ odata, 
                                     const float* __restrict__ idata, 
                                     int width, int height) {
    // TILE_DIM + 1 padding breaks the 32-word alignment boundary
    __shared__ float tile[TILE_DIM][TILE_DIM + 1];

    int x = blockIdx.x * TILE_DIM + threadIdx.x;
    int y = blockIdx.y * TILE_DIM + threadIdx.y;

    for (int j = 0; j < TILE_DIM; j += BLOCK_ROWS) {
        if (x < width && (y + j) < height) {
            tile[threadIdx.y + j][threadIdx.x] = idata[(y + j) * width + x];
        }
    }

    __syncthreads();

    int x_t = blockIdx.y * TILE_DIM + threadIdx.x;
    int y_t = blockIdx.x * TILE_DIM + threadIdx.y;

    for (int j = 0; j < TILE_DIM; j += BLOCK_ROWS) {
        if (x_t < height && (y_t + j) < width) {
            // (threadIdx.x * 33) % 32 = threadIdx.x % 32.
            // Thread 0 maps to Bank 0, Thread 1 to Bank 1, etc. -> 0 conflicts.
            odata[(y_t + j) * height + x_t] = tile[threadIdx.x][threadIdx.y + j];
        }
    }
}

// Host-side CPU transpose for validation
void cpuTranspose(float* odata, const float* idata, int width, int height) {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            odata[x * height + y] = idata[y * width + x];
        }
    }
}

int main() {
    try {
        const int width = 2048;
        const int height = 2048;
        if (width % TILE_DIM != 0 || height % TILE_DIM != 0) {
            throw std::invalid_argument("Matrix dimensions must be multiples of TILE_DIM (32)");
        }

        const int N = width * height;
        const size_t bytes = N * sizeof(float);

        std::vector<float> h_in(N);
        std::vector<float> h_out_conflict(N, 0.0f);
        std::vector<float> h_out_padded(N, 0.0f);
        std::vector<float> h_ref(N, 0.0f);

        // Initialize input data
        for (int i = 0; i < N; ++i) {
            h_in[i] = static_cast<float>(i % 100);
        }

        // Run CPU verification reference
        cpuTranspose(h_ref.data(), h_in.data(), width, height);

        // Device pointers
        float *d_in = nullptr, *d_out = nullptr;
        CUDA_CHECK(cudaMalloc(&d_in, bytes));
        CUDA_CHECK(cudaMalloc(&d_out, bytes));

        CUDA_CHECK(cudaMemcpy(d_in, h_in.data(), bytes, cudaMemcpyHostToDevice));

        dim3 blockSize(TILE_DIM, BLOCK_ROWS);
        dim3 gridSize(width / TILE_DIM, height / TILE_DIM);

        cudaEvent_t start, stop;
        CUDA_CHECK(cudaEventCreate(&start));
        CUDA_CHECK(cudaEventCreate(&stop));
        float ms = 0.0f;

        // ----------------------------------------------------
        // 1. Conflict Kernel
        // ----------------------------------------------------
        CUDA_CHECK(cudaEventRecord(start));
        transposeWithConflicts<<<gridSize, blockSize>>>(d_out, d_in, width, height);
        CUDA_CHECK(cudaEventRecord(stop));
        check_kernel_execution("transposeWithConflicts");
        CUDA_CHECK(cudaMemcpy(h_out_conflict.data(), d_out, bytes, cudaMemcpyDeviceToHost));
        CUDA_CHECK(cudaEventElapsedTime(&ms, start, stop));
        std::cout << "Conflicting Transpose Time: " << ms << " ms\n";

        // ----------------------------------------------------
        // 2. Padded Kernel
        // ----------------------------------------------------
        CUDA_CHECK(cudaEventRecord(start));
        transposeWithPadding<<<gridSize, blockSize>>>(d_out, d_in, width, height);
        CUDA_CHECK(cudaEventRecord(stop));
        check_kernel_execution("transposeWithPadding");
        CUDA_CHECK(cudaMemcpy(h_out_padded.data(), d_out, bytes, cudaMemcpyDeviceToHost));
        CUDA_CHECK(cudaEventElapsedTime(&ms, start, stop));
        std::cout << "Padded (Conflict-free) Transpose Time: " << ms << " ms\n";

        // ----------------------------------------------------
        // Correctness Validation
        // ----------------------------------------------------
        for (int i = 0; i < N; ++i) {
            if (std::abs(h_out_conflict[i] - h_ref[i]) > 1e-5f || 
                std::abs(h_out_padded[i] - h_ref[i]) > 1e-5f) {
                throw std::runtime_error("Validation failed! Mismatch at index " + std::to_string(i));
            }
        }
        std::cout << "Verification SUCCESS: All outputs match CPU reference.\n";

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

## 3. Complexity & Space Overhead Analysis

*   **Time Complexity**: $\mathcal{O}(\text{Width} \times \text{Height})$ for both.
*   **Space Complexity**:
    *   Conflicting: $\text{TILE\_DIM} \times \text{TILE\_DIM} \times 4\text{ bytes} = 4096\text{ bytes}$ per block.
    *   Padded: $\text{TILE\_DIM} \times (\text{TILE\_DIM} + 1) \times 4\text{ bytes} = 4224\text{ bytes}$ per block.
*   **Memory Overhead**: The padding increases Shared Memory utilization by only $\approx 3.1\%$, which has zero impact on occupancy (block execution limits per SM).

---

## 4. Verification using Nsight Compute

To verify shared memory behavior in production:
*   Tool: **NVIDIA Nsight Compute (ncu)**
*   Metric 1: `l1tex__data_bank_conflicts_pipe_lsu.sum` (tracks count of shared memory bank conflicts).
*   Metric 2: `l1tex__shared_backpressure_cycles` (tracks the number of cycles execution was stalled in L1/Shared Memory due to address conflicts).
*   *Validation Check*: The padded transpose kernel should reduce `l1tex__data_bank_conflicts_pipe_lsu.sum` to exactly **0**.

---

## 5. Common Follow-Up Questions & How to Answer

### Q1: How do bank conflicts apply to `double` (64-bit) types, and how do you resolve them?
**A**: A `double` occupies 8 bytes (two consecutive 32-bit banks). In default 4-byte bank mode, a sequential read by 32 threads (`double` array, stride 1) maps thread $i$ to banks $2i \pmod{32}$ and $2i+1 \pmod{32}$, which causes a 2-way bank conflict.
*   **Resolution 1**: Set the shared memory configuration to 8-byte mode:
    `cudaDeviceSetSharedMemConfig(cudaSharedMemBankSizeEightByte)`. This maps consecutive 8-byte words to consecutive banks, eliminating conflict on sequential double accesses.
*   **Resolution 2**: Align shared memory structures to offset double variables on odd strides.

### Q2: What is the difference between Shared Memory Bank Conflicts and Global Memory Coalescing?
**A**:
*   **Shared Memory Bank Conflicts** occur inside the SM at the shared memory crossbar routing logic when threads access the same physical bank.
*   **Global Memory Coalescing** occurs outside the SM at the memory controllers and DRAM/HBM interfaces. It requires that threads in a warp access memory addresses that fall within a contiguous segment (e.g., 32, 64, or 128-byte alignment) so they can be serviced in a single memory transaction.

### Q3: How do you handle alignment when packing multiple different types into dynamic shared memory?
**A**:
When dynamically launching shared memory (`extern __shared__ char s_mem[]`), packing multiple arrays requires manual alignment calculations:
```cpp
extern __shared__ char s_mem[];
int* array1 = (int*)s_mem;
// Align next pointer to 16-byte boundary (required for float4/vectorized loads)
float4* array2 = (float4*)((((uintptr_t)&array1[N]) + 15) & ~15);
```
Failing to align pointers on 16-byte boundaries can trigger alignment faults or force the LSU to split a single vector load (`LDG.128`) into multiple slow instructions.

---

## 6. Python Integration & GIL Context

When writing GPU kernels in Python, avoiding bank conflicts requires the same design principles as C++, implemented through Python-specific libraries like **Numba** or **PyCUDA**.

### 1. Declaring Padded Shared Memory in Numba
Numba's `@cuda.jit` compiler allows direct allocation of static shared memory inside kernels using `cuda.shared.array`. Adding padding is straightforward:
```python
import numba
from numba import cuda

TILE_DIM = 32

@cuda.jit
def numba_transpose_padded(odata, idata, width, height):
    # Padding the second dimension to change row stride from 32 to 33.
    # This skews bank mapping of column reads and eliminates 32-way bank conflicts.
    tile = cuda.shared.array(shape=(TILE_DIM, TILE_DIM + 1), dtype=numba.float32)
    
    tx = cuda.threadIdx.x
    ty = cuda.threadIdx.y
    bx = cuda.blockIdx.x
    by = cuda.blockIdx.y
    
    x = bx * TILE_DIM + tx
    y = by * TILE_DIM + ty
    
    # Coalesced read from global memory into padded shared memory
    if x < width and y < height:
        tile[ty, tx] = idata[y * width + x]
        
    cuda.syncthreads()
    
    # Read from shared memory transposed (now conflict-free due to TILE_DIM + 1 stride)
    x_t = by * TILE_DIM + tx
    y_t = bx * TILE_DIM + ty
    
    if x_t < height and y_t < width:
        odata[y_t * height + x_t] = tile[tx, ty]
```

### 2. GIL Bypass During Execution
The Python Global Interpreter Lock (GIL) only constrains operations executing on the CPU interpreter.
*   **Kernel Launches**: When a Python thread launches `numba_transpose_padded[grid, block](d_out, d_in, w, h)`, the Numba runtime invokes the CUDA driver API to push the kernel to the GPU hardware command queue. During this invocation, Numba **releases the GIL**.
*   **GPU Execution**: Once dispatched, the GPU executes the threads, manages the shared memory crossbar routing, and handles any potential bank conflicts entirely independent of Python. The GIL has 0 impact on the physical performance of the GPU's memory pipelines.

### 3. NumPy Strides and Memory Layout
In C++, multi-dimensional arrays are typically flattened manually. In Python, NumPy manages multi-dimensional arrays using **strides** (metadata indicating how many bytes to jump in memory to reach the next element in each dimension).
*   **Implicit Transposes**: Calling `.T` or `np.transpose()` on a NumPy array does not copy data; it merely swaps the strides (e.g., converting a C-contiguous array to F-contiguous).
*   **Hazard**: If a transposed NumPy/CuPy array is passed directly to a CUDA kernel, its non-contiguous stride configuration can break global memory coalescing assumptions in the read phase. To avoid this, arrays should be made contiguous using `np.ascontiguousarray()` or its CuPy equivalent before GPU memory allocation.

---

## 7. Pro-Tip: How to Impress the Interviewer

*   **Key Terms**: "LSU (Load/Store Unit) serialization", "n-way bank conflict", "Shared Memory Config: `cudaSharedMemBankSizeEightByte`", "Crossbar routing latency", "LDG/LDS instructions", "128-bit vectorization (`float4`)".
*   **Common Mistakes to Avoid**:
    *   *Mistake*: Thinking padding always requires adding exactly `1` element. *Correction*: Padding requires changing the row stride to be coprime with 32 (e.g., a stride of 33, 35, or 37). If the stride is already coprime, no padding is needed.
    *   *Mistake*: Stating that a broadcast (all threads reading the same address) causes bank conflicts. *Correction*: Broadcast is a hardware-accelerated, single-cycle operation with 0 conflicts.
