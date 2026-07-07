# Merge Intervals

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / QA & Test Engineer / Low-Level Developer
- **Source**: LeetCode 56, Glassdoor
- **Flashcards**: [Coding Playbook deck](flash_cards/behavioral_qa/coding_playbook.md)

---

## Question Description

Given an array of `intervals` where `intervals[i] = [start_i, end_i]`, merge all overlapping intervals, and return *an array of the non-overlapping intervals that cover all the intervals in the input*.

### Examples
*   **Input**: `intervals = [[1,3],[2,6],[8,10],[15,18]]`
    *   **Output**: `[[1,6],[8,10],[15,18]]`
    *   **Explanation**: Since intervals `[1,3]` and `[2,6]` overlap, merge them into `[1,6]`.
*   **Input**: `intervals = [[1,4],[4,5]]`
    *   **Output**: `[[1,5]]`
    *   **Explanation**: Intervals `[1,4]` and `[4,5]` are considered overlapping.

---

## Detailed Solution (C++)

The standard algorithm sorts the intervals based on their start times. Once sorted:
1. Initialize a container for merged intervals.
2. Iterate through the sorted intervals. For each interval:
   * If the merged list is empty or the current interval's start time is greater than the end time of the last merged interval, append it.
   * Otherwise, the current interval overlaps with the last merged interval. Update the last merged interval's end time to be the maximum of its current end time and the current interval's end time.

To optimize memory usage, we perform the merging **in-place** inside the input vector. We also leverage **C++ move semantics** (`std::move`) to prevent expensive vector reallocations and deep copies of inner elements.

```cpp
#include <vector>
#include <algorithm>
#include <cstddef>

class Solution {
public:
    std::vector<std::vector<int>> merge(std::vector<std::vector<int>>& intervals) noexcept {
        if (intervals.empty()) {
            return {};
        }

        // Sort intervals by their start point O(N log N)
        std::sort(intervals.begin(), intervals.end(), [](const std::vector<int>& a, const std::vector<int>& b) noexcept {
            return a[0] < b[0];
        });

        // Index of the last written merged interval
        std::size_t writeIdx = 0;

        for (std::size_t i = 1; i < intervals.size(); ++i) {
            // If the current interval overlaps with the last merged interval
            if (intervals[i][0] <= intervals[writeIdx][1]) {
                // Merge them by updating the end point
                intervals[writeIdx][1] = std::max(intervals[writeIdx][1], intervals[i][1]);
            } else {
                // Move write index to next slot
                writeIdx++;
                // Avoid dynamic allocation by moving the inner vector instead of copying
                intervals[writeIdx] = std::move(intervals[i]);
            }
        }

        // Resize the vector to discard the unused tail elements
        intervals.resize(writeIdx + 1);
        return intervals;
    }
};
```

---

## Detailed Solutions (Python)

In Python, we provide two approaches:
1. **Out-of-Place Merging (Standard)**: Highly readable, idiomatic Python.
2. **In-Place Merging (Optimized)**: Mimics C++ pointer swapping to minimize reference allocations.

### Method 1: Out-of-Place Merging (Idiomatic)

```python
from typing import List
from operator import itemgetter

class Solution:
    def merge(self, intervals: List[List[int]]) -> List[List[int]]:
        """
        Merges overlapping intervals using standard O(N) auxiliary space.
        """
        if not intervals:
            return []

        # Sort intervals by their start point. 
        # Using itemgetter(0) is faster than lambda x: x[0] in Python.
        intervals.sort(key=itemgetter(0))

        merged: List[List[int]] = []
        for interval in intervals:
            # If merged is empty or current interval doesn't overlap with the last merged
            if not merged or merged[-1][1] < interval[0]:
                merged.append(interval)
            else:
                # Merge current interval with the last merged one
                merged[-1][1] = max(merged[-1][1], interval[1])

        return merged
```

### Method 2: In-Place Merging (Reference Pointer Optimized)

```python
from typing import List
from operator import itemgetter

class SolutionInPlace:
    def merge(self, intervals: List[List[int]]) -> List[List[int]]:
        """
        Merges intervals in-place inside the original list to optimize allocations.
        """
        if not intervals:
            return []

        # Sort in-place
        intervals.sort(key=itemgetter(0))

        write_idx = 0
        for i in range(1, len(intervals)):
            # Overlap check
            if intervals[i][0] <= intervals[write_idx][1]:
                intervals[write_idx][1] = max(intervals[write_idx][1], intervals[i][1])
            else:
                write_idx += 1
                # Swap references (Python stores list elements as references)
                intervals[write_idx] = intervals[i]

        # Truncate the list in-place to drop the trailing unused items
        del intervals[write_idx + 1:]
        return intervals
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Timsort Complexity and Overhead
*   Python’s built-in `list.sort()` and `sorted()` functions use **Timsort** (a hybrid of merge sort and insertion sort).
*   **Time Complexity**: Runs in $\mathcal{O}(n \log n)$ worst-case, but features $\mathcal{O}(n)$ best-case behavior on pre-sorted or partially-sorted arrays.
*   **Space Complexity**: Timsort requires $\mathcal{O}(n)$ auxiliary space to store temporary run metadata. This differs from C++ `std::sort` which uses Introsort ($\mathcal{O}(\log n)$ stack space).

### 2. Lambda Call Overhead vs `operator.itemgetter`
*   Using `key=lambda x: x[0]` calls a Python interpreter function for every item in the list, creating a frame overhead for each check.
*   Using `key=operator.itemgetter(0)` delegates the indexing logic entirely to Python's C-compiled runtime, bypassing the Python-level function call stack and improving sorting speed by **$20\% - 30\%$**.

### 3. Object Reference Copying vs Deep Copies
*   In Python, arrays/lists contain references to objects. When doing `intervals[write_idx] = intervals[i]`, Python copies only the **reference** (a 64-bit pointer), not the underlying integer array.
*   This makes operations like swapping or overwriting elements run in $\mathcal{O}(1)$ time. Unlike C++, there is no need for dynamic allocations or explicit move semantics (`std::move`).

### 4. Modifying List Sizes In-Place
*   `del intervals[write_idx + 1:]` deletes items from the end of the array in-place. Because it only clears references at the tail of the list without shifting remaining elements, it runs in $\mathcal{O}(k)$ where $k$ is the number of elements deleted, maintaining maximum efficiency.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(n \log n)$ | Dominated by `std::sort`. The subsequent linear scan and in-place swapping take $\mathcal{O}(n)$ time. |
| **Space Complexity** | $\mathcal{O}(\log n)$ or $\mathcal{O}(1)$ | The auxiliary space is $\mathcal{O}(\log n)$ to store recursion stack frames for `std::sort` (Introsort). By modifying the input vector in-place, we achieve $\mathcal{O}(1)$ extra user-allocated space. |

---

## Common Follow-Up Questions & How to Answer

### Q1: What if the intervals are already sorted by start time?
*   **Answer**: If the input is guaranteed to be pre-sorted, we can bypass `std::sort`. The time complexity drops to $\mathcal{O}(n)$, and the space complexity drops to $\mathcal{O}(1)$ auxiliary space.

### Q2: How do you support dynamic interval insertion and query (e.g., LeetCode 57 "Insert Interval")?
*   **Answer**:
    *   **Vector Implementation**: If intervals are stored in a sorted vector, we can insert the new interval and merge overlaps in a single pass of $\mathcal{O}(n)$ time.
    *   **Interval Tree / Balanced BST**: For high-frequency read/write environments (e.g., scheduling engines or virtual memory trackers), a balanced BST like `std::set` containing non-overlapping intervals can be used. When inserting a new interval:
        1. Find the insertion position using binary search (`std::set::lower_bound`) in $\mathcal{O}(\log n)$ time.
        2. Merge overlapping intervals adjacent to the newly inserted interval.
        3. Delete the redundant merged intervals.
        Each dynamic update runs in $\mathcal{O}(\log n)$ amortized time.

### Q3: How does this apply to memory allocators and fragmentation?
*   **Answer**: Real-world operating systems and GPU drivers implement custom memory allocators (e.g., virtual memory managers) that track allocated and free blocks.
    *   When memory is freed, the allocator runs an interval merging step called **coalescing** to join adjacent free blocks. This prevents external heap fragmentation.
    *   Instead of sorting blocks, allocators track free blocks using **boundary tags** (pointers inside the block header pointing to adjacent physical blocks) or **Balanced Binary Trees** sorted by memory address. This allows coalescing with left/right neighbors in $\mathcal{O}(1)$ time.

---

## Pro-Tip: How to Impress the Interviewer

*   **Highlight Move Semantics**: Standard code uses `intervals[writeIdx] = intervals[i]` which triggers a heap allocation and deep-copy of the inner `std::vector<int>`. Explicitly using `std::move` transfers ownership of the underlying pointer of the inner vector, converting a slow heap allocation into a lightning-fast pointer swap.
*   **Point out cache locality issues with Vector of Vectors**: Mention that `std::vector<std::vector<int>>` is a "vector of pointers" that causes pointer chasing and cache misses. Suggest that in high-performance computing, we define a flat contiguous layout (e.g., a custom `struct Interval { int start; int end; };` inside a single vector) to maximize L1/L2 cache prefetching.
*   **Signed/Unsigned Hygiene**: Using `std::size_t` instead of `int` for vector indices avoids warnings about comparing signed and unsigned integers, demonstrating code-quality rigor.
