# Combinations

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / AI Systems Architect / QA & Test Engineer
- **Source**: LeetCode 77, Glassdoor

---

## Question Description

Given two integers `n` and `k`, return all possible combinations of `k` numbers chosen from the range `[1, n]`.

You may return the answer in **any order**.

### Examples

*   **Input**: `n = 4, k = 2`
    *   **Output**: `[[1,2],[1,3],[1,4],[2,3],[2,4],[3,4]]`
    *   **Explanation**: There are $\binom{4}{2} = 6$ total combinations. Note that combinations are unordered, i.e., `[1,2]` and `[2,1]` are considered to be the same combination.
*   **Input**: `n = 1, k = 1`
    *   **Output**: `[[1]]`

### Constraints
*   $1 \le n \le 20$
*   $1 \le k \le n$

---

## Detailed Solution (C++)

This problem can be modeled as finding all subsets of size `k` from the set $\{1, 2, \dots, n\}$.
A naive backtracking implementation branches on all elements. However, we can perform a highly effective **search space pruning** optimization:
*   At any state, if the number of elements in our current `path` plus the number of remaining elements in the range `[i, n]` is less than `k`, it is mathematically impossible to construct a combination of size `k`.
*   Thus, we only loop `i` up to `n - (k - path.size()) + 1`.

### Standard C++ Production Code

```cpp
#include <vector>

class Solution {
private:
    void backtrack(int start, int n, int k, std::vector<int>& path, std::vector<std::vector<int>>& result) {
        if (path.size() == k) {
            result.push_back(path);
            return;
        }

        // Optimization: limit the range to avoid building branches that cannot reach size k
        // Number of elements we still need to select is (k - path.size())
        int limit = n - (k - static_cast<int>(path.size())) + 1;
        for (int i = start; i <= limit; ++i) {
            path.push_back(i);
            backtrack(i + 1, n, k, path, result);
            path.pop_back(); // Backtrack
        }
    }

public:
    std::vector<std::vector<int>> combine(int n, int k) {
        std::vector<std::vector<int>> result;
        std::vector<int> path;
        backtrack(1, n, k, path, result);
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
    def combine(self, n: int, k: int) -> List[List[int]]:
        """
        Generates all combinations of k numbers from [1, n].
        
        Time Complexity: O(k * C(n, k))
        Space Complexity: O(k)
        """
        result: List[List[int]] = []

        def backtrack(start: int, path: List[int]):
            if len(path) == k:
                result.append(list(path))
                return

            # Optimization: prune branches where remaining elements are insufficient
            limit = n - (k - len(path)) + 1
            for i in range(start, limit + 1):
                path.append(i)
                backtrack(i + 1, path)
                path.pop()  # Backtrack

        backtrack(1, [])
        return result
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Built-in `itertools.combinations`
*   Python's standard library provides `itertools.combinations(range(1, n + 1), k)`. This is implemented in C and is significantly faster than any user-space recursive function.
*   **Python Code**:
    ```python
    import itertools
    def combine(n: int, k: int) -> List[List[int]]:
        return [list(c) for c in itertools.combinations(range(1, n + 1), k)]
    ```
*   Always mention this built-in capability in interviews to show you write production-grade code.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}\left(k \cdot \binom{n}{k}\right)$ | There are $\binom{n}{k}$ combinations. For each combination, we copy the path of size $k$ into the result. |
| **Space Complexity** | $\mathcal{O}(k)$ | The depth of the recursion tree is at most $k$, requiring $\mathcal{O}(k)$ stack space. |

---

## Common Follow-Up Questions & How to Answer

### Q1: How can we implement this iteratively (without recursion)?
*   **The Answer**: We can generate combinations in lexicographical order. Start with the first combination `[1, 2, ..., k]`. To find the next, we find the rightmost index `i` that is less than `n - k + i + 1`, increment it, and reset all elements to its right to be consecutive values.
*   **C++ Iterative Code**:
    ```cpp
    std::vector<std::vector<int>> combineIterative(int n, int k) {
        std::vector<std::vector<int>> result;
        std::vector<int> path(k, 0);
        int i = 0;
        while (i >= 0) {
            path[i]++;
            if (path[i] > n - k + i + 1) {
                i--;
            } else if (i == k - 1) {
                result.push_back(path);
            } else {
                i++;
                path[i] = path[i - 1];
            }
        }
        return result;
    }
    ```

### Q2: How can we generate combinations using bit manipulation (Gosper's Hack)?
*   **The Answer**: Gosper's Hack is an advanced bit manipulation algorithm that finds the next integer with the same number of set bits ($k$ bits).
*   **C++ Gosper's Hack Snippet**:
    ```cpp
    std::vector<std::vector<int>> combineGosper(int n, int k) {
        std::vector<std::vector<int>> result;
        int mask = (1 << k) - 1;
        int limit = 1 << n;
        while (mask < limit) {
            std::vector<int> path;
            for (int i = 0; i < n; ++i) {
                if ((mask >> i) & 1) path.push_back(i + 1);
            }
            result.push_back(path);
            
            // Gosper's Hack transition
            int c = mask & -mask;
            int r = mask + c;
            mask = (((r ^ mask) >> 2) / c) | r;
        }
        return result;
    }
    ```

---

## Pro-Tip: How to Impress the Interviewer

*   **In-Place Array Pruning Boundary**: Proactively explain the math behind the loop upper limit: `n - (k - path.size()) + 1`. This shows you are not just writing standard recursion but are actively optimizing the loop boundaries to prune dead search spaces.
*   **Discuss Gosper's Hack**: Mentioning Gosper's Hack in a systems/low-level developer interview is a major plus. It proves you understand bitwise arithmetic and know how to traverse set bits in $O(1)$ transitions per state.
