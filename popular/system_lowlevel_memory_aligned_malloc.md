# Custom Memory Allocator: Aligned Malloc and Free

**Category**: Low-level Systems / Memory Management
**Difficulty**: Medium / Hard
**Target Role**: Low-Level Systems Developer / AI Compiler Developer / C++ Game Engine Engineer
**Flashcards**: [Concurrency deck](flash_cards/systems/concurrency.md)

---

## Question Description

Implement custom versions of `aligned_malloc` and `aligned_free` in C++ without using platform-specific runtime library functions (such as `_aligned_malloc`, `posix_memalign`, or C++17 `std::aligned_alloc`).

1. **Memory Layout**: Provide the code for `aligned_malloc` and `aligned_free`. Handle metadata storage and pointer alignment.
2. **Robustness**: Implement strict edge-case handling, including integer overflow checks, zero-size inputs, and non-power-of-two alignments.
3. **Hardware & OS Impact**: Detail why alignment is critical for CPU vectorization (SIMD), cache line efficiency, and virtual memory page boundaries.

---

## 1. Memory Layout and Pointer Arithmetic

To return an aligned address, we request a larger block of memory from `std::malloc` to guarantee that an aligned address exists within the allocated range. We also must store a pointer to the original memory block so we can free it later.

### Memory Layout
```
Raw Allocated Block (malloc):
+-----------------+----------------------+------------------------------------+
|  Unused Space   | Metadata: void* p1   | Aligned memory block returned (p2) |
+-----------------+----------------------+------------------------------------+
^                 ^                      ^
p1 (raw pointer)  p2 - sizeof(void*)     p2 (aligned pointer)
```

1.  **Overhead Calculation**:
    We need space for the requested `bytes`, plus up to `alignment - 1` bytes for shifting the pointer, plus `sizeof(void*)` bytes to store the original pointer `p1`.
    $$\text{Total Bytes} = \text{bytes} + \text{alignment} - 1 + \text{sizeof(void*)}$$
2.  **Pointer Alignment Math**:
    Let $p_1$ be the raw pointer returned by `std::malloc`.
    We shift $p_1$ forward by `sizeof(void*)` to make room for metadata. We then round up to the next multiple of `alignment` by clearing the lowest bits:
    $$p_2 = (p_1 + \text{sizeof(void*)} + \text{alignment} - 1) \ \& \ \sim(\text{alignment} - 1)$$
3.  **Storing Metadata**:
    We store the raw pointer `p1` in the bytes immediately preceding `p2`:
    `((void**)p2)[-1] = p1;`

---

## 2. Complete C++ Implementation

This implementation checks for integer overflow and alignment errors, and includes a C++17 standard-compliant allocator wrapper.

```cpp
#include <iostream>
#include <cstdlib>
#include <cstdint>
#include <cassert>
#include <new>
#include <vector>
#include <stdexcept>

// ============================================================================
// 1. Custom Aligned Malloc & Free
// ============================================================================

void* aligned_malloc(size_t bytes, size_t alignment) {
    // 1. Validate alignment is a power of two
    if (alignment == 0 || (alignment & (alignment - 1)) != 0) {
        throw std::invalid_argument("Alignment must be a non-zero power of 2");
    }

    if (bytes == 0) {
        return nullptr;
    }

    // Force alignment to be at least a pointer size to guarantee metadata fits
    if (alignment < sizeof(void*)) {
        alignment = sizeof(void*);
    }

    // 2. Prevent integer overflow during size calculations
    size_t offset = alignment - 1 + sizeof(void*);
    if (bytes > SIZE_MAX - offset) {
        throw std::bad_alloc(); // Size calculation would overflow size_t
    }

    size_t total_size = bytes + offset;

    // 3. Allocate memory
    void* p1 = std::malloc(total_size);
    if (!p1) {
        return nullptr;
    }

    // 4. Align the address
    uintptr_t raw_addr = reinterpret_cast<uintptr_t>(p1);
    uintptr_t aligned_addr = (raw_addr + sizeof(void*) + alignment - 1) & ~(alignment - 1);

    void* p2 = reinterpret_cast<void*>(aligned_addr);

    // 5. Store the metadata (original pointer p1) in the preceding slot
    static_cast<void**>(p2)[-1] = p1;

    return p2;
}

void aligned_free(void* ptr) {
    if (!ptr) {
        return;
    }

    // Step back by one pointer width to retrieve the raw address
    void* p1 = static_cast<void**>(ptr)[-1];
    std::free(p1);
}

// ============================================================================
// 2. Custom C++17 Aligned Allocator (for std::vector, etc.)
// ============================================================================

template <typename T, size_t Align>
struct AlignedAllocator {
    using value_type = T;

    AlignedAllocator() = default;
    template <typename U> constexpr AlignedAllocator(const AlignedAllocator<U, Align>&) noexcept {}

    T* allocate(std::size_t n) {
        if (n > std::size_t(-1) / sizeof(T)) {
            throw std::bad_alloc();
        }
        void* p = aligned_malloc(n * sizeof(T), Align);
        if (!p) {
            throw std::bad_alloc();
        }
        return static_cast<T*>(p);
    }

    void deallocate(T* p, std::size_t) noexcept {
        aligned_free(p);
    }

    bool operator==(const AlignedAllocator&) const { return true; }
    bool operator!=(const AlignedAllocator&) const { return false; }
};

// ============================================================================
// Verification and Benchmarking
// ============================================================================
int main() {
    try {
        // Test basic alignments
        size_t alignments[] = {8, 16, 32, 64, 128};
        for (size_t align : alignments) {
            void* p = aligned_malloc(1024, align);
            uintptr_t addr = reinterpret_cast<uintptr_t>(p);

            std::cout << "Requested: " << align << " | Allocated: 0x" 
                      << std::hex << addr << " | Remainder: " 
                      << (addr % align) << std::dec << std::endl;

            assert(addr % align == 0 && "Memory misalignment detected!");
            aligned_free(p);
        }

        // Test with std::vector using 64-byte alignment (useful for AVX-512)
        std::cout << "Testing std::vector with 64-byte alignment...\n";
        std::vector<double, AlignedAllocator<double, 64>> vec(100, 3.14);
        
        uintptr_t vec_addr = reinterpret_cast<uintptr_t>(vec.data());
        std::cout << "Vector data address: 0x" << std::hex << vec_addr 
                  << " (Alignment % 64 = " << (vec_addr % 64) << ")" << std::dec << "\n";
        
        assert(vec_addr % 64 == 0);
        std::cout << "Verification SUCCESS.\n";

    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
```

---

## 3. Complexity Analysis

*   **Time Complexity**: $\mathcal{O}(1)$ for both operations. Bitwise arithmetic takes 1-2 CPU cycles.
*   **Space Complexity**: $\mathcal{O}(1)$ auxiliary space per allocation.
*   **Memory Overhead**: The allocated size exceeds the requested size by up to $\text{alignment} + \text{sizeof(void*)} - 1$ bytes. For 64-byte alignment on a 64-bit OS, the maximum overhead is $71$ bytes.

---

## 4. Hardware Importance of Memory Alignment

### SIMD and Vector Registers
Modern CPUs process data in parallel using vector registers (SSE: 128-bit, AVX: 256-bit, AVX-512: 512-bit).
*   **Alignment Restrictions**: Hardware instructions that load data into these registers (e.g., `_mm256_load_ps` for AVX) require the memory address to be aligned to the register width (e.g., 32-byte alignment for AVX). Loading from an unaligned address triggers a **General Protection Fault (`#GP(0)`)** and crashes the program.
*   **Unaligned Instructions**: While unaligned instructions (e.g., `_mm256_loadu_ps`) exist, they can cause **Cache Line Splits** (where a single vector load spans two cache lines), requiring two cache accesses instead of one.

### CPU Cache Lines
CPUs fetch memory in **64-byte cache lines**. If an unaligned data structure spans two cache lines, operations on it require the CPU to fetch, lock, and synchronize two cache lines, doubling memory access times.

### Virtual Memory and Page Faults
Operating systems manage virtual memory in **Pages** (typically 4KB). 
*   If a data structure is unaligned, it can cross a page boundary.
*   If page $A$ is in physical memory but page $B$ has been swapped to disk, accessing the structure triggers a **Page Fault**. The CPU suspends execution, invokes the OS page fault handler, loads the missing page, and restarts the instruction, causing a massive latency spike.

---

## 5. Common Follow-Up Questions & How to Answer

### Q1: How does `std::malloc` guarantee alignment?
**A**:
`std::malloc` is guaranteed to return a pointer aligned to support any basic type (in C++11, this is `alignof(std::max_align_t)`, which is typically 16 bytes on 64-bit platforms). It cannot, however, guarantee alignments for larger requirements (like 32-byte AVX or 64-byte cache line alignment).

### Q2: What is the benefit of C++17 `std::aligned_alloc`, and how does it compare?
**A**:
C++17 introduced `std::aligned_alloc(alignment, size)`. It avoids the metadata memory overhead of our custom wrapper. However:
1.  **Strict Rules**: The `size` parameter *must* be a multiple of `alignment`, otherwise the behavior is undefined.
2.  **Platform Support**: Its implementation was historically inconsistent across MSVC (which does not support it, requiring `_aligned_malloc`) and GCC/Clang.

### Q3: How do modern memory allocators (like jemalloc or tcmalloc) avoid lock contention in multithreaded systems?
**A**:
If multiple threads frequently call `aligned_malloc`, lock contention on the global heap lock will bottleneck performance.
*   **Thread-Local Arenas**: Modern allocators allocate large chunks of memory to individual threads as Thread-Local caches (t-caches).
*   When a thread requests memory, the allocator satisfies it from the thread-local pool without acquiring global locks.

---

## 6. Python Integration & GIL Context

While memory alignment is fundamentally a C++/hardware concept, it deeply impacts Python's numerical stack (NumPy, PyTorch, CuPy) when interfacing with vectorized operations:

### 1. Python PyMalloc and the GIL
Python's standard memory manager (`PyObject_Malloc` or **PyMalloc**) is optimized for small allocations (< 512 bytes) using a system of Arenas, Pools, and Blocks.
*   **Safety under the GIL**: The Global Interpreter Lock (GIL) serializes all memory management calls inside PyMalloc, protecting it from race conditions without needing internal locks.
*   **Alignment Limitations**: PyMalloc does *not* support custom memory alignments (e.g., aligning memory to 64-byte boundaries for AVX-512). 

### 2. NumPy Memory Alignment
To execute vectorized operations, NumPy requires memory alignment:
*   **Internal Allocations**: When a new NumPy array is created, its underlying C data buffer is allocated via standard C library allocators (which guarantee alignment to 16 bytes on 64-bit platforms).
*   **Vectorization Flags**: A NumPy array contains flags, including `ALIGNED`. This flag is set to `True` if the data buffer is aligned according to the data type's requirements (e.g., a float32 array aligned to a multiple of 4 bytes).
*   **Unaligned Slices**: If you slice or transpose an array (e.g., `arr[1::2]`), NumPy returns a strided view. The `ALIGNED` flag will be set to `False` if the starting address of the view does not match the scalar type alignment, preventing C-level SIMD operations from executing or forcing them to fall back to slow scalar loops.

### 3. Interfacing Aligned C++ Buffers with Python
To pass custom aligned memory from C++ (using `aligned_malloc`) to Python without copying data:
```cpp
// pybind11 snippet to wrap aligned C++ memory in a NumPy array
py::handle get_aligned_array(size_t size) {
    // Allocate 64-byte aligned memory block
    float* data = static_cast<float*>(aligned_malloc(size * sizeof(float), 64));
    
    // Create a capsule to clean up memory when the NumPy array is garbage collected
    py::capsule free_when_done(data, [](void* f) {
        aligned_free(f);
    });

    // Wrap the raw pointer as a NumPy array view
    return py::array_t<float>(
        {size},          // Shape
        {sizeof(float)}, // Strides
        data,            // Raw pointer
        free_when_done   // Capsule owner
    ).release();
}
```
Through this method, when Numba, PyTorch, or NumPy executes vectorized CPU code on the array, the memory is perfectly aligned to 64 bytes. The CPU can issue aligned load instructions (like `vmovaps` for AVX-2) rather than unaligned loads (`vmovups`), avoiding cache-line splits and general protection faults completely, even after the GIL is released.

---

## 7. Pro-Tip: How to Impress the Interviewer

*   **Key Terms**: "General Protection Fault (`#GP(0)`)", "Cache Line Split", "Translation Lookaside Buffer (TLB) Page Walk", "Integer Overflow Mitigation", "Metadata Offset Overhead", "TCMalloc Thread-Local Arenas", "SIMD alignment (`vmovaps` vs `vmovups`)".
*   **Common Mistakes to Avoid**:
    *   *Mistake*: Forgetting the integer overflow check. In security audits, checking `bytes + alignment` for size overflow is critical.
    *   *Mistake*: Forgetting to validate that the alignment argument is a power of 2.
