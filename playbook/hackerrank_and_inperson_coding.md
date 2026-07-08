# HackerRank Online Assessment & In-Person Coding Playbook

- **Category**: Playbook / Guides
- **Difficulty**: Hard
- **Target Role**: Software Engineer / Low-Level Developer / AI System Engineer / CUDA Engineer
- **Source**: NVIDIA Recruiting Process, Glassdoor, Internal Interview Guidelines
- **Flashcards**: [Coding Playbook deck](flash_cards/behavioral_qa/coding_playbook.md)

---

## 1. The HackerRank Online Assessment (OA) Playbook

The HackerRank Online Assessment is the primary filter in NVIDIA's hiring pipeline. It is designed to screen for fundamental coding proficiency, low-level system understanding, and hardware-awareness. 

### Format & Structure
* **Duration**: 90 minutes.
* **Composition**: 
  * **2 Coding Problems**: Typically LeetCode Medium to Hard, with a strong preference for array manipulation, bitwise logic, intervals, or graph traversals.
  * **10-15 Multiple Choice Questions (MCQs)**: Covering OS internals, computer architecture, and C++ basics.
* **Scoring**: You must achieve 100% correctness on the coding test cases and high accuracy on the MCQs to secure an invite to the technical phone screen.

---

### Review of Core MCQ Topics

#### A. Operating System Internals
1. **CPU Scheduling**: Focus on preemptive scheduling, Round-Robin, Priority Inversion (and how protocols like Priority Inheritance solve it), and Multi-Level Feedback Queues (MLFQ).
2. **Context Switching Overhead**: Understand what happens when a CPU context switches. The kernel must save CPU registers (including the Instruction Pointer, Stack Pointer, and general-purpose registers) into the Thread Control Block (TCB), swap page tables (if switching processes), and reload the registers of the incoming thread.
3. **Thread Memory Model**: Threads of the same process share the virtual address space (text segment, global variables, heap, file descriptors). However, each thread has its own **private stack** (for local variables, function calls, and activation records) and its own **program counter** and register set.
4. **Virtual Memory & Page Faults**: Understand the page table hierarchy, Translation Lookaside Buffer (TLB) cache, and the latency hit of page faults (trapping to the OS, loading from disk/SSD, and updating the page table).

#### B. C++ Basics & Memory Management
1. **Pointer Sizing & Alignment**: Pointers on a 64-bit architecture are always 8 bytes (32-bit are 4 bytes). Data structures are padded by the compiler to align members to their natural boundaries (e.g., an 8-byte pointer must reside on a memory address divisible by 8) to ensure single-cycle memory accesses.
2. **Virtual Tables (vtables) & Dynamic Dispatch**: 
   * Any class containing at least one `virtual` function contains a hidden virtual table pointer (`vptr`), usually at offset 0.
   * The `vptr` points to the class's `vtable` (an array of function pointers).
   * Dynamic dispatch adds a layer of redirection: loading the `vptr`, indexing into the `vtable`, and referencing the function pointer.
   * **Impact**: Dynamic dispatch prevents compiler optimizations like inlining and can cause instruction cache misses because the jump target is determined at runtime.
3. **Reference vs. Pointer**: References are syntactically aliases, must be initialized upon declaration, cannot be null, and cannot be rebound. Pointers are distinct objects storing memory addresses, can be null, can be rebound, and support pointer arithmetic.
4. **Templates & Instantiation**: C++ templates are instantiated at compile time, leading to zero runtime overhead but potentially causing code bloat (generating separate machine code for each type parameter combo).

#### C. Computer Architecture & Memory Hierarchy
1. **Caches (L1, L2, L3)**: Access speeds differ by orders of magnitude:
   * **L1 Cache**: ~1–2 ns
   * **L2 Cache**: ~5–10 ns
   * **L3 Cache**: ~15–20 ns
   * **DRAM (Main Memory)**: ~60–100 ns
2. **Spatial & Temporal Locality**: Contiguous array access utilizes spatial locality because data is fetched in cache lines (typically 64 bytes).
3. **Branch Prediction & Speculative Execution**: The CPU guesses the path of a conditional branch to keep the execution pipeline full. A misprediction results in a **pipeline stall** and flush, costing 10–20 clock cycles. Branchless programming (using arithmetic or bitwise masks instead of `if` statements) is critical for performance-critical hot paths.

---

### Sample MCQ Questions

#### MCQ 1: C++ Class Layout & Alignment
**Question**:  
Given the following C++ code compiled on a standard 64-bit Linux system with GCC:

```cpp
class Base {
public:
    virtual void func1() {}
    void func2() {}
};

class Derived : public Base {
public:
    void func1() override {}
    virtual void func3() {}
private:
    int x;
};
```

What is the output of `sizeof(Base)` and `sizeof(Derived)` (assuming default GCC alignment rules)?

* **A)** `sizeof(Base) = 8`, `sizeof(Derived) = 12`
* **B)** `sizeof(Base) = 8`, `sizeof(Derived) = 16`
* **C)** `sizeof(Base) = 16`, `sizeof(Derived) = 16`
* **D)** `sizeof(Base) = 16`, `sizeof(Derived) = 24`

**Correct Answer**: **B**

**Detailed Explanation**:
1. **`Base` Layout**: `Base` has a virtual function `func1()`. To support dynamic polymorphism, the compiler inserts a virtual table pointer (`vptr`). On a 64-bit system, this pointer takes 8 bytes. `func2()` is non-virtual, so it occupies no space in the object instance. Thus, `sizeof(Base)` is 8 bytes.
2. **`Derived` Layout**: `Derived` inherits from `Base`, so it contains `Base`'s `vptr` (8 bytes). It overrides `func1()` and introduces a new virtual function `func3()`. Both virtual functions share the same `vptr` table; hence, no new `vptr` is added. `Derived` adds a private integer member `x` (4 bytes).
3. **Memory Padding**: The raw size of `Derived` is `8 bytes (vptr) + 4 bytes (int x) = 12 bytes`. However, the largest member alignment constraint in `Derived` is 8 bytes (the `vptr`). The compiler must pad the object size to be a multiple of the largest alignment boundary. Thus, the compiler adds 4 bytes of padding at the end of the class, making `sizeof(Derived)` equal to 16 bytes.

---

#### MCQ 2: Cache Coherence & False Sharing
**Question**:  
Two threads, Thread 1 and Thread 2, run concurrently on Core A and Core B of a multi-core CPU. Thread 1 repeatedly writes to a shared 32-bit integer `structVal.x`, while Thread 2 repeatedly writes to another 32-bit integer `structVal.y`. Under which condition will this cause a massive drop in CPU throughput, and what is the underlying hardware mechanism?

* **A)** When `structVal.x` and `structVal.y` reside on different virtual memory pages; resolved by TLB flushes.
* **B)** When `structVal.x` and `structVal.y` reside within the same 64-byte cache line, causing the cache coherence protocol (e.g., MESI) to repeatedly invalidate the cache line across both cores.
* **C)** When the memory controller is forced to serialize access because both variables are not aligned to 128-bit boundaries.
* **D)** When the CPU pipeline is flushed due to a branch misprediction in the cache eviction policy.

**Correct Answer**: **B**

**Detailed Explanation**:
This scenario describes **False Sharing**. 
* Even though the two threads modify entirely independent variables (`x` and `y`), these variables reside within the same cache line (typically 64 bytes). 
* Under cache coherence protocols like MESI, when Core A writes to `x`, it must acquire exclusive ownership of the cache line containing `x`. This marks the cache line as **Invalid (I)** in Core B's L1/L2 cache.
* When Core B attempts to write to `y`, it detects that the cache line is Invalid, forcing a cache miss. Core B must write back Core A's changes or retrieve the cache line from L3 or DRAM. 
* This continuous invalidation loop ("cache line ping-ponging") blocks CPU pipelines and degrades throughput. It is resolved by aligning variables to separate cache lines using `alignas(64)`.

---

#### MCQ 3: Context Switch Penalty
**Question**:  
Why is a context switch between two threads of **different processes** significantly more expensive than a context switch between two threads of the **same process**?

* **A)** Switching threads of different processes requires storing floating-point registers, whereas same-process threads only require storing integer registers.
* **B)** Different-process context switches require flushing the Translation Lookaside Buffer (TLB) due to changing the page directory pointer (e.g., CR3 in x86), leading to subsequent memory access delays.
* **C)** Same-process threads bypass the OS kernel scheduler entirely, whereas different-process threads require a kernel interrupt trap.
* **D)** Different-process switches trigger hardware cache line write-backs for the entire L3 cache.

**Correct Answer**: **B**

**Detailed Explanation**:
* All threads within a single process share the exact same virtual address space (and therefore the same page table directory). When switching between them, the CPU's memory management unit (MMU) does not change its page table root pointer.
* When switching between threads of different processes, the CPU must switch to a new virtual address space by changing the page directory root register (e.g., loading the CR3 register in x86).
* Changing the page table root invalidates all virtual-to-physical translations cached in the **Translation Lookaside Buffer (TLB)**. The TLB must be flushed. 
* Consequently, the newly scheduled thread will experience a high rate of TLB misses for its initial instructions, requiring costly multi-level page table walks in main memory (which can add hundreds of clock cycles per access).

---

### Sample HackerRank Coding Problem: Bitwise Subarray Operations

#### Problem Statement
> **Shortest Subarray with OR at Least K**
>
> You are given an array of non-negative integers `nums` and a positive integer `k`.
> Find the length of the **shortest** non-empty contiguous subarray of `nums` such that the bitwise OR of all elements in the subarray is at least `k`. If no such subarray exists, return `-1`.

#### Constraints
* $1 \le \text{nums.length} \le 10^5$
* $0 \le \text{nums}[i] \le 10^9$
* $0 \le k \le 10^9$

#### Algorithmic Strategy
Since bitwise OR is a non-decreasing operation (i.e., adding an element to a set can only set more bits, never clear them), we can employ a **Sliding Window** (two-pointer) approach.
However, unlike sum or product operations, bitwise OR does not have an inverse. If we shrink the window from the left, we cannot simply "subtract" or "divide" the left element out of the current OR value.

**Solution**:
1. Maintain a bit count array `bitCounts` of size 32, where `bitCounts[i]` stores the number of elements in the current window that have their $i$-th bit set.
2. Maintain a running window `[left, right]`.
3. When expanding the window by adding `nums[right]`:
   * Update the bit counts by iterating through all 32 bits of `nums[right]`.
4. We can reconstruct the window's bitwise OR value in $\mathcal{O}(32)$ time:
   * $\text{ORValue} = \sum_{i=0}^{31} (1 \ll i) \text{ if } \text{bitCounts}[i] > 0$.
5. If the current OR value is at least `k`:
   * Update the minimum subarray length.
   * Shrink the window from the left by removing `nums[left]` and updating `bitCounts`. Repeat this until the OR value falls below `k`.

---

#### C++ Implementation (Optimized for Cache Locality & Zero Allocation)

```cpp
#include <vector>
#include <algorithm>
#include <cstdint>

class Solution {
private:
    // Update bit counts inline without dynamic allocation
    inline void updateBits(int32_t bitCounts[32], uint32_t val, int32_t delta) noexcept {
        for (int i = 0; i < 32; ++i) {
            if ((val >> i) & 1) {
                bitCounts[i] += delta;
            }
        }
    }

    // Reconstruct the OR sum from bit counts in O(32) operations
    inline uint32_t getOrSum(const int32_t bitCounts[32]) noexcept {
        uint32_t orSum = 0;
        for (int i = 0; i < 32; ++i) {
            if (bitCounts[i] > 0) {
                orSum |= (1U << i);
            }
        }
        return orSum;
    }

public:
    int shortestSubarrayWithOR(const std::vector<int>& nums, int k) noexcept {
        if (k == 0) return 1;

        const int n = nums.size();
        int32_t bitCounts[32] = {0}; // Fixed-size stack allocation
        int minLen = n + 1;
        int left = 0;

        for (int right = 0; right < n; ++right) {
            updateBits(bitCounts, static_cast<uint32_t>(nums[right]), 1);

            // Shrink window from the left as long as the OR sum is at least k
            while (left <= right && getOrSum(bitCounts) >= static_cast<uint32_t>(k)) {
                minLen = std::min(minLen, right - left + 1);
                updateBits(bitCounts, static_cast<uint32_t>(nums[left]), -1);
                left++;
            }
        }

        return (minLen == n + 1) ? -1 : minLen;
    }
};
```

---

#### Python Implementation

```python
class Solution:
    def shortestSubarrayWithOR(self, nums: list[int], k: int) -> int:
        if k == 0:
            return 1
            
        n = len(nums)
        bit_counts = [0] * 32
        min_len = n + 1
        left = 0
        
        def update_bits(val: int, delta: int) -> None:
            # Shift value and update counts
            for i in range(32):
                if (val >> i) & 1:
                    bit_counts[i] += delta
                    
        def get_or_sum() -> int:
            or_sum = 0
            for i in range(32):
                if bit_counts[i] > 0:
                    or_sum |= (1 << i)
            return or_sum

        for right in range(n):
            update_bits(nums[right], 1)
            
            # Attempt to shrink the window
            while left <= right and get_or_sum() >= k:
                min_len = min(min_len, right - left + 1)
                update_bits(nums[left], -1)
                left += 1
                
        return -1 if min_len == n + 1 else min_len
```

---

### Complexity Analysis
* **Time Complexity**: $\mathcal{O}(32 \cdot N) \approx \mathcal{O}(N)$ where $N$ is the length of `nums`. Each element is added to and removed from the sliding window at most once. For each addition and removal, we perform 32 bitwise operations.
* **Space Complexity**: $\mathcal{O}(1)$ auxiliary space. The `bitCounts` array is fixed-size (32 elements), representing the 32 bits of a 32-bit unsigned integer.

---
---

## 2. The In-Person/Onsite Coding Round Playbook

At NVIDIA, the onsite coding interview is rarely a simple "write an algorithm and leave" exercise. It is highly interactive and systems-oriented.

### Format & Flow
* **Duration**: 45–60 minutes.
* **Platform**: Laptop (CoderPad) or Whiteboard.
* **Evolutionary Nature**: The interviewer begins with a straightforward coding question and iteratively layers on real-world constraints:

```
[Naive Implementation] ──> [Algorithmic Optimization] ──> [Memory Layout (Cache Locality)] ──> [Concurrency & Thread-Safety] ──> [Hardware / GPU Scale]
```

To clear the bar, you must demonstrate comfort across the entire spectrum.

---

### Onsite Problem Walkthrough: Thread-Safe Key-Value Store with Expiry

#### Phase 1: The Initial Problem (Single-Threaded Correctness)
**Interviewer**: *"Design a key-value store where entries have a Time-To-Live (TTL) in milliseconds. Implement `put(key, value, ttl_ms)` and `get(key)`."*

**Your Approach**: 
* Use an `std::unordered_map` mapping keys to a struct containing the value and the absolute expiry timestamp (`std::chrono::steady_clock::time_point`).
* In `get(key)`, retrieve the entry. Compare `now` with `entry.expiry`. If it has expired, remove the entry from the map (passive eviction) and return an empty result.

#### Phase 2: Introducing Concurrency
**Interviewer**: *"This key-value store is now accessed by multiple threads concurrently. How do you prevent data races?"*

**Your Progress**:
* **Initial thought**: Wrap all map accesses in an `std::mutex` lock.
* **Critique**: A global mutex means only one thread can read from the map at a time. This creates a severe bottleneck for read-heavy workloads (which is typical for caches).
* **Optimization**: Use `std::shared_mutex` (C++17). Readers acquire a shared lock (`std::shared_lock`), allowing multiple concurrent reads. Writers acquire an exclusive lock (`std::unique_lock`).

#### Phase 3: Garbage Collection & Memory Leaks
**Interviewer**: *"Passive eviction only cleans up keys when they are accessed. What if keys are written once with a TTL, never read again, and fill up memory? How would you solve this?"*

**Your Progress**:
* **Strategy**: Introduce **Active Eviction**.
* **Active Eviction Design Alternatives**:
  1. *Background Thread with Periodic Sweep*: Spawn a worker thread that wakes up periodically (e.g., every 100ms) and deletes expired keys. 
     * *Problem*: Sweeping the entire map requires holding the exclusive write lock for a long time, blocking all client reads/writes.
     * *Optimized Sweeping (Redis-style)*: In each tick, select a random bucket and check a small sample of keys (e.g., 20 keys). If expired, evict them. If more than 25% of the sampled keys are expired, repeat. This bounds the locking duration.
  2. *Priority Queue (Min-Heap)*: Maintain a min-heap of keys ordered by expiry time. The worker thread sleeps until the top of the heap is expired, waking up to evict it.
     * *Problem*: The min-heap becomes a single point of lock contention across all threads.

#### Phase 4: Systems Performance & Cache Line Friendly Design
**Interviewer**: *"Under high concurrent write load, even `std::shared_mutex` causes lock contention. How do you scale this?"*

**Your Progress**:
* **Solution**: **Bucket Sharding**. 
  * Instead of a single map and a single lock, partition the cache into $M$ independent buckets (e.g., $M = 64$).
  * Hash the key to determine which bucket it belongs to: $\text{idx} = \text{hash}(\text{key}) \pmod M$.
  * Each bucket contains its own map and its own `std::shared_mutex`. This reduces lock contention by a factor of $M$.
* **Hardware Optimization (False Sharing Prevention)**:
  * Since the buckets are allocated contiguously in a vector, adjacent bucket locks and maps may reside on the same L1/L2 cache line (64 bytes).
  * Use `alignas(64)` on the `Bucket` struct to force each bucket to reside on its own cache line, preventing false sharing between thread modifications.

---

### Architectural Layout of Concurrent Sharded Key-Value Store

```text
   ┌──────────┐         ┌─────────────────────┐
   │  Client  │────────▶│   Hash Function:    │
   │ Request: │         │    Hash(Key) % M    │
   │ get/put  │         └──┬──────┬───────┬───┘
   └────┬─────┘            │      │       │
        │                  ▼      ▼       ▼
        │            ┌────────┐┌──────┐┌────────┐
        │            │Bucket 0││Bkt 1 ││Bucket  │
        │            └───┬────┘└──────┘│ M-1    │
        │                │             └────────┘
        │                ▼
        │       ┌──────────────────────────────────────────┐
        │       │ Bucket Structure                          │
        │       │ ┌──────────────────────────────────────┐ │
        │       │ │ std::shared_mutex (aligned to 64B)   │ │
        │       │ └──────────────────────────────────────┘ │
        │       │ ┌──────────────────────────────────────┐ │
        │       │ │ std::unordered_map<Key, CacheEntry>  │◀┼─┐
        │       │ └──────────────────┬───────────────────┘ │ │
        │       └────────────────────┼─────────────────────┘ │
        │                            ▼                       │
        │       ┌──────────────────────────────────────────┐ │
        │       │ Cache Entry                               │ │
        │       │ ┌──────────────────────────────────────┐ │ │
        │       │ │ Value & Expiry Timestamp             │ │ │
        │       │ └──────────────────────────────────────┘ │ │
        │       └──────────────────────────────────────────┘ │
        │                                                  │
        │       Passive Eviction on get                    │
        └──────────────────────────────────────────────────┘


┌──────────────────────────────────────────────────────────────┐
│  Eviction Mechanics (Active)                                 │
│                                                              │
│   ┌──────────────────────────────┐                           │
│   │ Background Active Eviction   │                           │
│   │      Thread (GC)             │                           │
│   └──┬──────────┬──────────┬─────┘                           │
│      │ Locks &  │ Locks &  │ Locks &                         │
│      │ Samples  │ Samples  │ Samples                         │
│      ▼          ▼          ▼                                 │
│   [Bucket 0] [Bucket 1] [Bucket M-1]                         │
│                                                              │
└──────────────────────────────────────────────────────────────┘
```

---

### Production-Grade C++ Implementation (Bucket-Sharded, Thread-Safe, Active Eviction)

```cpp
#include <unordered_map>
#include <shared_mutex>
#include <mutex>
#include <chrono>
#include <thread>
#include <vector>
#include <string>
#include <optional>
#include <atomic>
#include <random>

template <typename K, typename V>
class ShardedConcurrentCache {
private:
    struct CacheEntry {
        V value;
        std::chrono::steady_clock::time_point expiry;
    };

    // Align to 64 bytes to prevent false sharing between adjacent buckets in the vector
    struct alignas(64) Bucket {
        std::shared_mutex mutex;
        std::unordered_map<K, CacheEntry> table;
    };

    const size_t numBuckets;
    std::vector<Bucket> buckets;
    std::atomic<bool> stopGc{false};
    std::thread gcThread;

    size_t getBucketIndex(const K& key) const noexcept {
        return std::hash<K>{}(key) % numBuckets;
    }

    // Active Eviction Loop
    void runActiveEviction() {
        std::default_random_engine generator(std::random_device{}());
        std::uniform_int_distribution<size_t> distribution(0, numBuckets - 1);

        while (!stopGc.load(std::memory_order_relaxed)) {
            // Sleep to minimize idle CPU consumption
            std::this_thread::sleep_for(std::chrono::milliseconds(50));

            // Select a random bucket to check
            size_t bucketIdx = distribution(generator);
            auto& bucket = buckets[bucketIdx];

            // Try to acquire an exclusive lock to avoid blocking active client threads
            std::unique_lock<std::shared_mutex> lock(bucket.mutex, std::try_to_lock);
            if (!lock.owns_lock()) {
                continue; // Skip if bucket is currently heavily contested
            }

            auto now = std::chrono::steady_clock::now();
            size_t checked = 0;
            auto it = bucket.table.begin();

            // Evict up to 20 expired keys to bound lock-hold duration
            while (it != bucket.table.end() && checked < 20) {
                if (now >= it->second.expiry) {
                    it = bucket.table.erase(it);
                } else {
                    ++it;
                }
                ++checked;
            }
        }
    }

public:
    explicit ShardedConcurrentCache(size_t numBuckets = 64) 
        : numBuckets(numBuckets), buckets(numBuckets) {
        gcThread = std::thread(&ShardedConcurrentCache::runActiveEviction, this);
    }

    ~ShardedConcurrentCache() {
        stopGc.store(true, std::memory_order_release);
        if (gcThread.joinable()) {
            gcThread.join();
        }
    }

    // Disable copy/move semantics to guarantee memory-safety under concurrent access
    ShardedConcurrentCache(const ShardedConcurrentCache&) = delete;
    ShardedConcurrentCache& operator=(const ShardedConcurrentCache&) = delete;
    ShardedConcurrentCache(ShardedConcurrentCache&&) = delete;
    ShardedConcurrentCache& operator=(ShardedConcurrentCache&&) = delete;

    // Insert or update an entry with TTL in milliseconds
    void put(const K& key, const V& value, int64_t ttlMs) {
        size_t idx = getBucketIndex(key);
        auto expiryTime = std::chrono::steady_clock::now() + std::chrono::milliseconds(ttlMs);

        std::unique_lock<std::shared_mutex> lock(buckets[idx].mutex);
        buckets[idx].table[key] = CacheEntry{value, expiryTime};
    }

    // Retrieve an entry (with passive eviction)
    std::optional<V> get(const K& key) {
        size_t idx = getBucketIndex(key);
        auto now = std::chrono::steady_clock::now();

        // 1. Acquire shared lock for concurrent reading
        std::shared_lock<std::shared_mutex> lock(buckets[idx].mutex);
        auto it = buckets[idx].table.find(key);

        if (it == buckets[idx].table.end()) {
            return std::nullopt;
        }

        // 2. Check expiration
        if (now >= it->second.expiry) {
            // Must release shared lock before acquiring exclusive lock to avoid deadlock
            lock.unlock();
            
            std::unique_lock<std::shared_mutex> writeLock(buckets[idx].mutex);
            // Double-check lock condition (avoid Time-of-Check to Time-of-Use race condition)
            auto writeIt = buckets[idx].table.find(key);
            if (writeIt != buckets[idx].table.end() && now >= writeIt->second.expiry) {
                buckets[idx].table.erase(writeIt);
            }
            return std::nullopt;
        }

        return it->second.value;
    }
};
```

---

## 3. Strategy for Onsite Coding Success

To stand out in an NVIDIA onsite coding loop, adopt these strategies:

1. **Clarify Constraints Up Front**: 
   * "What is the expected read-to-write ratio?" (e.g., 99% reads justifies a shared lock or reader-writer lock).
   * "What is the scale of the dataset?" (Fits in memory? Do we need to shard?).
   * "What are the latency/throughput SLA targets?"
2. **Think Out Loud (With Systems Context)**:
   * Do not just talk about time complexity (e.g., $\mathcal{O}(1)$). Discuss how memory hierarchy affects performance (e.g., "A hash map has $\mathcal{O}(1)$ average access time, but pointer-chasing in bucket chains causes L3/DRAM cache misses. An array search of small elements might actually be faster due to continuous cache lines").
3. **Dry-Run code with Thread Interactions**:
   * Trace execution steps using two imaginary threads executing at different interleavings (e.g., Thread A calling `get` while Thread B calls `put` or when GC runs). Show how your locks protect against race conditions.
4. **Mention Hardware Hardware-specific limits**:
   * Bring up concepts like **False Sharing**, **Memory Barriers (Fences)**, **Lock-Free CAS (Compare-And-Swap) atomic primitives**, and **PCIe bandwidth bottlenecks** to show you can write code that runs efficiently on real silicon.
