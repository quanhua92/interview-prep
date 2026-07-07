# Russian Doll Envelopes

- **Category**: Coding
- **Difficulty**: Hard
- **Target Role**: Software Engineer / Low-Level Developer / AI Systems Architect
- **Source**: LeetCode 354, Glassdoor

---

## Question Description

You are given a 2D array of integers `envelopes` where `envelopes[i] = [wi, hi]` represents the width and the height of an envelope.

One envelope can fit into another if and only if both the width and height of one envelope are greater than the other envelope's width and height.

Return the maximum number of envelopes you can Russian doll (i.e., put one inside the other).

**Note**: You cannot rotate an envelope.

### Examples

*   **Input**: `envelopes = [[5,4],[6,4],[6,7],[2,3]]`
    *   **Output**: `3`
    *   **Explanation**: The maximum number of envelopes you can Russian doll is `3` (`[2,3]` $\Rightarrow$ `[5,4]` $\Rightarrow$ `[6,7]`).
*   **Input**: `envelopes = [[1,1],[1,1],[1,1]]`
    *   **Output**: `1`

### Constraints
*   $1 \le \text{envelopes.length} \le 10^5$
*   $\text{envelopes}[i].\text{length} == 2$
*   $1 \le w_i, h_i \le 10^5$

---

## Detailed Solution (C++)

A naive Longest Increasing Subsequence (LIS) dynamic programming approach takes $\mathcal{O}(n^2)$ time, which will result in a Time Limit Exceeded (TLE) error since $n \le 10^5$. 

To solve this in $\mathcal{O}(n \log n)$ time, we can combine **Sorting** with **Binary Search**:
1.  **Sort the Envelopes**:
    *   Sort the width in ascending order.
    *   For envelopes with the **same width**, sort their heights in **descending order**.
2.  **Longest Increasing Subsequence (LIS)**:
    *   After sorting, the widths are sorted, so we only need to find the LIS of the heights.
    *   By sorting heights of the same width in descending order, we ensure that we cannot select multiple envelopes of the same width (since LIS requires strictly increasing heights, and a descending sequence of heights will never allow more than one element to be picked for the same width).
    *   We maintain an active LIS heights array `dp` and use `std::lower_bound` to update elements in-place.

### Standard C++ Production Code

```cpp
#include <vector>
#include <algorithm>

class Solution {
public:
    int maxEnvelopes(std::vector<std::vector<int>>& envelopes) {
        if (envelopes.empty()) {
            return 0;
        }

        // Sort width ascending, height descending for identical widths
        std::sort(envelopes.begin(), envelopes.end(), [](const std::vector<int>& a, const std::vector<int>& b) {
            if (a[0] != b[0]) {
                return a[0] < b[0];
            }
            return a[1] > b[1];
        });

        std::vector<int> dp;
        dp.reserve(envelopes.size()); // Pre-allocate memory to avoid multiple reallocations

        for (const auto& env : envelopes) {
            int h = env[1];
            // Binary search for the insertion index of height h
            auto it = std::lower_bound(dp.begin(), dp.end(), h);
            
            if (it == dp.end()) {
                dp.push_back(h);
            } else {
                *it = h;
            }
        }

        return static_cast<int>(dp.size());
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the iterative, type-hinted Python implementation using the built-in `bisect` library.

```python
import bisect
from typing import List

class Solution:
    def maxEnvelopes(self, envelopes: List[List[int]]) -> int:
        """
        Calculates the maximum number of envelopes that can be nested.
        
        Time Complexity: O(N log N)
        Space Complexity: O(N)
        """
        if not envelopes:
            return 0

        # Sort: width ascending (x[0]), then height descending (-x[1])
        envelopes.sort(key=lambda x: (x[0], -x[1]))

        heights: List[int] = []
        for _, h in envelopes:
            idx = bisect.bisect_left(heights, h)
            if idx == len(heights):
                heights.append(h)
            else:
                heights[idx] = h

        return len(heights)
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Complex Sorting Keys
* In Python, sorting using a custom lambda function like `key=lambda x: (x[0], -x[1])` is optimized natively in C through Timsort. The negative operator `-x[1]` works directly for numeric types. If sorting non-numeric objects or complex criteria, a custom comparator would need `functools.cmp_to_key` which adds interpreter overhead.

### 2. Space Overhead of List Manipulation
* Resizing list arrays in Python involves dynamic array resizing strategies. Pre-allocating list elements or using list comprehensions is usually faster. However, since the LIS length is bounded by $N$, building `heights` dynamically using `append()` is highly efficient.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(n \log n)$ | Sorting takes $\mathcal{O}(n \log n)$ time. The loop performs $n$ binary searches, each taking $\mathcal{O}(\log n)$ time. |
| **Space Complexity** | $\mathcal{O}(n)$ | Stores the sorted arrays/heights up to size $n$. |

---

## Common Follow-Up Questions & How to Answer

### Q1: What if we can rotate the envelopes?
* **Answer**: If we can rotate envelopes, we can treat each envelope as two options: `[w, h]` and `[h, w]`. We can generate both options for each envelope (ensuring `w >= h` by swapping to standard format: long side as width, short side as height). Once standardized, we apply the same sorting and LIS logic.

### Q2: What if we are matching in 3 dimensions (Boxes instead of Envelopes)?
* **Answer**: In 3D (width, height, depth), we can sort by width ascending, depth descending, and then we must find the 2D LIS (height and depth must both be strictly increasing). This is typically solved using a **Segment Tree** or **Fenwick Tree** (Binary Indexed Tree) in combination with divide and conquer (CDQ Divide and Conquer) to resolve the multidimensional constraints in $\mathcal{O}(n \log^2 n)$ time.

---

## Pro-Tip: How to Impress the Interviewer

* **Explain the Height Descending Trick Clearly**: Many candidates struggle to explain *why* the descending sort for identical widths is necessary. Explain it clearly: *"If widths are equal and heights are sorted ascending, standard LIS would allow nesting them (e.g. `[3, 3]` and `[3, 4]`). By sorting heights descending, the LIS check on `[4, 3]` prevents both from being included because 3 is smaller than 4, forcing us to choose at most one envelope per width."*
* **Mention Binary Search Alternatives**: Show depth by discussing that `std::lower_bound` is a binary search. In performance-critical systems, if `dp` is very small, a simple linear scan or branchless binary search could perform faster due to cache locality and compiler optimization.
