# Merge Intervals

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / Low-Level Developer
- **Source**: LeetCode 56, Glassdoor

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

To merge intervals efficiently, we can use a greedy sorting approach:
1.  **Sort the intervals** by their starting value. This ensures that any intervals that could potentially overlap are placed next to each other.
2.  **Iterate through the sorted list** and maintain a list of merged intervals.
    *   Initialize `merged` with the first interval.
    *   For each subsequent interval `current`, compare its start with the end of the last interval in `merged`.
    *   If `current[0] <= merged.back()[1]`, they overlap. Merge them by updating the end of the last interval to `max(merged.back()[1], current[1])`.
    *   If they do not overlap, simply append `current` to `merged`.

### Standard C++ Production Code

```cpp
#include <vector>
#include <algorithm>

class Solution {
public:
    std::vector<std::vector<int>> merge(std::vector<std::vector<int>>& intervals) {
        // Edge Case: Empty input
        if (intervals.empty()) {
            return {};
        }

        // Sort intervals by starting time. std::sort on std::vector<int> compares elements lexicographically,
        // which naturally sorts by start time (intervals[i][0]).
        std::sort(intervals.begin(), intervals.end());

        std::vector<std::vector<int>> merged;
        merged.push_back(intervals[0]);

        for (size_t i = 1; i < intervals.size(); ++i) {
            // Overlap check: if current start is <= previous end
            if (intervals[i][0] <= merged.back()[1]) {
                merged.back()[1] = std::max(merged.back()[1], intervals[i][1]);
            } else {
                // No overlap, push to merged result
                merged.push_back(intervals[i]);
            }
        }

        return merged;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the type-hinted Python implementation. It avoids copying list elements by modifying the last element of the result in-place.

```python
from typing import List

class Solution:
    def merge(self, intervals: List[List[int]]) -> List[List[int]]:
        """
        Merges overlapping intervals by sorting by start time.
        
        Time Complexity: O(N log N)
        Space Complexity: O(N) for the merged output
        """
        if not intervals:
            return []

        # Sort intervals in-place by starting point
        intervals.sort(key=lambda x: x[0])

        merged = [intervals[0]]

        for start, end in intervals[1:]:
            last_end = merged[-1][1]
            
            # If current interval overlaps with the last merged one, merge them
            if start <= last_end:
                merged[-1][1] = max(last_end, end)
            else:
                # Disjoint interval, append directly
                merged.append([start, end])

        return merged
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. TimSort and Custom Sorting Key
*   Python's `list.sort()` uses **Timsort** under the hood, which runs in $\mathcal{O}(n \log n)$ time. Timsort is highly optimized for runs of already sorted data.
*   Sorting lists of lists: using `intervals.sort(key=lambda x: x[0])` tells Python to sort solely based on the first element (start time). If we did not provide `key=lambda x: x[0]`, Python would fall back to comparing the second elements when the first elements are equal. Since we only need to order by the start time, specifying `key=lambda x: x[0]` is slightly more efficient.

### 2. In-Place List Operations
*   Instead of copying subarrays (which incurs memory allocation overhead), the solution appends references to the sublists or unpacks them. Be aware that `merged = [intervals[0]]` adds a reference to `intervals[0]`. In a system environment where the original input must not be modified, you should create a copy, e.g., `merged = [list(intervals[0])]`.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(n \log n)$ | Sorting the array of $n$ intervals takes $\mathcal{O}(n \log n)$ time. The linear traversal and merging phase take $\mathcal{O}(n)$ time. |
| **Space Complexity** | $\mathcal{O}(n)$ | Standard implementations allocate memory for the merged list. (If sorted in-place, auxiliary space is $\mathcal{O}(\log n)$ or $\mathcal{O}(1)$ depending on the sort implementation). |

---

## Common Follow-Up Questions & How to Answer

### Q1: Can we perform the merge in-place to achieve $\mathcal{O}(1)$ auxiliary space?
*   **The Answer**: Yes. We can reuse the input vector as a buffer by keeping track of a `write_idx` pointer.
*   **Implementation (C++)**:
    ```cpp
    std::sort(intervals.begin(), intervals.end());
    int write_idx = 0;
    for (size_t i = 1; i < intervals.size(); ++i) {
        if (intervals[i][0] <= intervals[write_idx][1]) {
            intervals[write_idx][1] = std::max(intervals[write_idx][1], intervals[i][1]);
        } else {
            write_idx++;
            intervals[write_idx] = intervals[i];
        }
    }
    intervals.resize(write_idx + 1);
    ```
    This avoids allocating a new vector and returns the filtered array in-place, which is critical for memory-constrained system programming.

### Q2: What if the input intervals are already sorted by their start values?
*   **The Answer**: If the input is pre-sorted, we can skip the sorting step entirely. The algorithm's time complexity becomes $\mathcal{O}(n)$ and we can perform the merge in a single linear scan.

### Q3: How do you handle an online/streaming data version of this problem?
*   **The Answer**: If intervals arrive one by one in real-time, we cannot sort the array every time.
    *   Instead, we maintain a balanced BST of disjoint intervals (like `std::set` in C++).
    *   When a new interval $[S, E]$ arrives, we query the BST to find all intervals overlapping with $[S, E]$ in $\mathcal{O}(\log n)$ time.
    *   We merge $[S, E]$ with the overlapping intervals, remove the old intervals, and insert the new merged interval.

---

## Pro-Tip: How to Impress the Interviewer

*   **Design for Memory Safety**: In C++, explain that using `std::move` when inserting non-overlapping intervals (e.g. `merged.push_back(std::move(intervals[i]))`) can save heap allocations and copies if the sub-containers are large.
*   **Mention Cache Coherency of 2D Vectors**: Note that `std::vector<std::vector<int>>` is a vector of vector structures, which stores pointers to heap-allocated sub-vectors. This structure has poor cache locality. For a high-performance engine, we would store intervals as a flat `std::vector<std::pair<int, int>>` or a flat `int*` array, where elements are stored contiguously in memory.
