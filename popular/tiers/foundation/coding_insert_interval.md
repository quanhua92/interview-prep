# Insert Interval

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / Low-Level Developer
- **Source**: LeetCode 57, Glassdoor

---

## Question Description

You are given an array of non-overlapping intervals `intervals` where `intervals[i] = [start_i, end_i]` represent the start and the end of the $i$-th interval and `intervals` is sorted in ascending order by `start_i`. You are also given an interval `newInterval = [start, end]` that represents the start and end of another interval.

Insert `newInterval` into `intervals` such that `intervals` is still sorted in ascending order by `start_i` and `intervals` still does not have any overlapping intervals (merge overlapping intervals if necessary).

Return `intervals` after the insertion.

**Note**: You do not need to modify `intervals` in-place. You can make a new array and return it.

### Examples
*   **Input**: `intervals = [[1,3],[6,9]]`, `newInterval = [2,5]`
    *   **Output**: `[[1,5],[6,9]]`
    *   **Explanation**: The new interval `[2,5]` overlaps with `[1,3]`, merging them into `[1,5]`.
*   **Input**: `intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]]`, `newInterval = [4,8]`
    *   **Output**: `[[1,2],[3,10],[12,16]]`
    *   **Explanation**: Because the new interval `[4,8]` overlaps with `[3,5],[6,7],[8,10]`, they are merged into one single interval `[3,10]`.

---

## Detailed Solution (C++)

Because the input `intervals` is already sorted, we can build the result in a single pass of three sequential steps:
1.  **Add all intervals** that end before the `newInterval` starts (no overlap possible).
2.  **Merge all intervals** that overlap with the `newInterval`. An interval overlaps with `newInterval` if its start point is less than or equal to `newInterval[1]`. For each overlapping interval, we update `newInterval`'s start to the minimum of both starts, and its end to the maximum of both ends. Once the overlap loop finishes, we push the merged `newInterval` to our result.
3.  **Add all remaining intervals** that start after `newInterval` ends.

### Standard C++ Production Code

```cpp
#include <vector>
#include <algorithm>

class Solution {
public:
    std::vector<std::vector<int>> insert(const std::vector<std::vector<int>>& intervals, std::vector<int>& newInterval) {
        std::vector<std::vector<int>> result;
        const size_t n = intervals.size();
        result.reserve(n + 1);
        size_t i = 0;

        // Step 1: Add all intervals that end before newInterval starts
        while (i < n && intervals[i][1] < newInterval[0]) {
            result.push_back(intervals[i]);
            i++;
        }

        // Step 2: Merge overlapping intervals
        while (i < n && intervals[i][0] <= newInterval[1]) {
            newInterval[0] = std::min(newInterval[0], intervals[i][0]);
            newInterval[1] = std::max(newInterval[1], intervals[i][1]);
            i++;
        }
        result.push_back(newInterval);

        // Step 3: Add all remaining intervals
        while (i < n) {
            result.push_back(intervals[i]);
            i++;
        }

        return result;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the type-hinted Python implementation using the three-stage linear traversal.

```python
from typing import List

class Solution:
    def insert(self, intervals: List[List[int]], newInterval: List[int]) -> List[List[int]]:
        """
        Inserts a new interval into a sorted list of non-overlapping intervals,
        merging overlapping intervals as needed.
        
        Time Complexity: O(N)
        Space Complexity: O(N)
        """
        result: List[List[int]] = []
        i = 0
        n = len(intervals)

        # Step 1: Add all intervals ending before newInterval starts
        while i < n and intervals[i][1] < newInterval[0]:
            result.append(intervals[i])
            i += 1

        # Step 2: Merge overlapping intervals
        while i < n and intervals[i][0] <= newInterval[1]:
            newInterval[0] = min(newInterval[0], intervals[i][0])
            newInterval[1] = max(newInterval[1], intervals[i][1])
            i += 1
        result.append(newInterval)

        # Step 3: Add all remaining intervals
        while i < n:
            result.append(intervals[i])
            i += 1

        return result
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Sublist Copying vs Reference Appends
*   In Python, `result.append(intervals[i])` appends a reference to the existing list object, which is fast ($\mathcal{O}(1)$ time).
*   However, `result.append(newInterval)` references the mutable `newInterval` list. Since `newInterval` was modified during the merging phase, appending it directly is fine as long as we do not modify `newInterval` afterwards. To be completely safe and avoid mutating shared objects, `result.append(list(newInterval))` or `result.append(newInterval[:])` can be used.

### 2. Guarding against Out-Of-Bounds
*   The indexing checks `while i < n` must precede the sub-index accesses `intervals[i][1]` or `intervals[i][0]` to prevent `IndexError` exceptions. Python evaluates logical conditions lazily, so placing `i < n` first guarantees the index is valid before evaluation.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(n)$ | We perform a single pass over the intervals array, processing each interval at most once. |
| **Space Complexity** | $\mathcal{O}(n)$ | We allocate a new list/vector to store the resulting list of intervals. |

---

## Common Follow-Up Questions & How to Answer

### Q1: Can we use Binary Search to find the insertion and merging points?
*   **The Answer**: Yes. Because the list is sorted, we can search for the first interval that might overlap.
    *   Find the insertion index using binary search: the first interval whose end time is $\ge$ `newInterval[0]`.
    *   Find the termination index: the first interval whose start time is $>$ `newInterval[1]`.
    *   While binary search identifies these indices in $\mathcal{O}(\log n)$ time, constructing the merged array (or performing in-place insertion/deletion in C++) still takes $\mathcal{O}(n)$ due to shifting elements in contiguous memory. Thus, the asymptotic time complexity remains $\mathcal{O}(n)$, but it reduces the number of comparisons.

### Q2: What if we are required to do it strictly in-place in C++?
*   **The Answer**: We can do it by finding the overlap bounds, replacing the first overlapping element with the merged interval, and erasing the remaining overlapping elements using `std::vector::erase`. However, vector `erase` calls shift all subsequent elements, which runs in $\mathcal{O}(n)$ time anyway.

---

## Pro-Tip: How to Impress the Interviewer

*   **Explain the Trade-offs of Vector Reservation**: In C++, we can optimize our memory footprint by reserving memory for the result vector: `result.reserve(intervals.size() + 1)`. This avoids multiple reallocations and copies as the vector grows dynamically, which is a major system-level optimization.
*   **Point out cache locality advantages**: If intervals are structured as a custom struct rather than `std::vector<int>` (e.g. `struct Interval { int start; int end; };`), the compiler can pack them contiguously in memory without double-indirection, resulting in vastly superior cache performance.
