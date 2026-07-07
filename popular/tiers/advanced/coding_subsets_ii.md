# Subsets II

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / Low-Level Developer / AI Systems Architect
- **Source**: LeetCode 90, Glassdoor

---

## Question Description

Given an integer array `nums` that may contain duplicate elements, return all possible subsets (the power set).

The solution set **must not** contain duplicate subsets. Return the solution in **any order**.

### Examples

*   **Input**: `nums = [1,2,2]`
    *   **Output**: `[[],[1],[1,2],[1,2,2],[2],[2,2]]`
*   **Input**: `nums = [0]`
    *   **Output**: `[[],[0]]`

### Constraints
*   $1 \le \text{nums.length} \le 10$
*   $-10 \le \text{nums}[i] \le 10$

---

## Detailed Solution (C++)

To prevent duplicate subsets without resorting to slow post-generation deduplication (e.g. using `std::set`), we sort the array first. Sorting places duplicate elements contiguously.

During backtracking:
1.  Every node in the recursion tree represents a valid subset, so we push the current `path` to the `result` list immediately.
2.  In the loop `for (int i = start; i < nums.size(); ++i)`, if `i > start` and `nums[i] == nums[i-1]`, we `continue` (skip). This ensures that we do not initiate duplicate branches at the same recursion depth.

### Standard C++ Production Code

```cpp
#include <vector>
#include <algorithm>

class Solution {
private:
    void backtrack(const std::vector<int>& nums, int start, std::vector<int>& path, std::vector<std::vector<int>>& result) {
        // Every node visited in the decision tree is a unique subset
        result.push_back(path);

        for (int i = start; i < nums.size(); ++i) {
            // Skip duplicates at the same recursion depth
            if (i > start && nums[i] == nums[i - 1]) {
                continue;
            }
            path.push_back(nums[i]);
            backtrack(nums, i + 1, path, result);
            path.pop_back(); // Backtrack
        }
    }

public:
    std::vector<std::vector<int>> subsetsWithDup(std::vector<int>& nums) {
        // Sort to bring duplicates together
        std::sort(nums.begin(), nums.end());
        
        std::vector<std::vector<int>> result;
        std::vector<int> path;
        
        // Since there are duplicates, the actual number of subsets is <= 2^N
        result.reserve(1 << nums.size());
        
        backtrack(nums, 0, path, result);
        return result;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

```python
from typing import List

class Solution:
    def subsetsWithDup(self, nums: List[int]) -> List[List[int]]:
        """
        Generates the power set of nums without duplicate subsets.
        
        Time Complexity: O(2^N * N)
        Space Complexity: O(N)
        """
        result: List[List[int]] = []
        nums.sort()

        def backtrack(start: int, current: List[int]):
            result.append(list(current))
            
            for i in range(start, len(nums)):
                # If the current element is a duplicate of the previous
                # and we are not at the starting index of this recursion level, skip
                if i > start and nums[i] == nums[i - 1]:
                    continue
                
                current.append(nums[i])
                backtrack(i + 1, current)
                current.pop()  # Backtrack

        backtrack(0, [])
        return result
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Iterative Cascading Approach with Duplicates
*   We can generate subsets iteratively. If we sort `nums`, duplicate elements will be adjacent. When processing a duplicate element `nums[i]`, we only append it to the subsets that were created in the **previous step**. This is a highly efficient way to avoid generating duplicate subsets without recursion.
*   **Python Code**:
    ```python
    def subsetsWithDupIterative(nums: List[int]) -> List[List[int]]:
        nums.sort()
        result = [[]]
        prev_size = 0
        for i in range(len(nums)):
            # If current element is duplicate, start appending from the subsets
            # created in the previous step (prev_size)
            start = prev_size if (i > 0 and nums[i] == nums[i-1]) else 0
            prev_size = len(result)
            for j in range(start, prev_size):
                result.append(result[j] + [nums[i]])
        return result
    ```
*   This approach completely avoids recursion overhead and has a smaller constant factor.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(2^n \cdot n)$ | Where $n$ is the number of elements. In the worst case (no duplicates), there are $2^n$ subsets, and copying each takes $\mathcal{O}(n)$ time. Sorting takes $\mathcal{O}(n \log n)$. |
| **Space Complexity** | $\mathcal{O}(n)$ | The recursion stack and path array require $\mathcal{O}(n)$ space. (Excluding the output size of $\mathcal{O}(2^n \cdot n)$). |

---

## Common Follow-Up Questions & How to Answer

### Q1: Why does `i > start` work to skip duplicates at the same level?
*   **The Answer**:
    *   `i > start` ensures we only skip duplicates at the **same recursion level** (in the loop).
    *   If `i == start`, it is the first time we are picking this value for the current path slot, which is valid and necessary.
    *   If `i > start` and `nums[i] == nums[i - 1]`, it means we already branched on this value at the current depth in a previous iteration of the loop. Branching on it again would generate redundant subsets.

### Q2: What if we want to return the subsets sorted by size?
*   **The Answer**: We can sort the output array of lists using a custom comparator. In Python: `result.sort(key=len)`. In C++: `std::sort(result.begin(), result.end(), [](const std::vector<int>& a, const std::vector<int>& b) { return a.size() < b.size(); });`.

---

## Pro-Tip: How to Impress the Interviewer

*   **Explain the Math behind Iterative Cascading with Duplicates**: Presenting the iterative cascading approach with the `prev_size` optimization shows an exceptionally deep understanding of combinatorial generation. It is elegant and proves you can write highly optimized, non-recursive code.
*   **Explain Memory Reserving**: Emphasize that calling `reserve(1 << nums.size())` in C++ allocates memory for the maximum possible subsets upfront, eliminating the costly overhead of dynamic array resizing and vector copying during backtracking.
