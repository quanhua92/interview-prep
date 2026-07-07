# Combination Sum

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / AI Systems Architect / QA & Test Engineer
- **Source**: LeetCode 39, Glassdoor
- **Flashcards**: [Backtracking deck](../../flash_cards/coding/backtracking.md)

---

## Question Description

Given an array of **distinct** integers `candidates` and a target integer `target`, return a list of all **unique combinations** of `candidates` where the chosen numbers sum to `target`. You may return the combinations in any order.

The **same** number may be chosen from `candidates` an **unlimited number of times**. Two combinations are unique if the frequency of at least one of the chosen numbers is different.

It is guaranteed that the number of unique combinations that sum up to `target` is less than `150` combinations for the given input.

### Examples

*   **Input**: `candidates = [2,3,6,7]`, `target = 7`
    *   **Output**: `[[2,2,3],[7]]`
    *   **Explanation**:
        *   `2` and `3` are candidates, and `2 + 2 + 3 = 7`. Note that `2` can be used multiple times.
        *   `7` is a candidate, and `7 = 7`.
*   **Input**: `candidates = [2,3,5]`, `target = 8`
    *   **Output**: `[[2,2,2,2],[2,3,3],[3,5]]`
*   **Input**: `candidates = [2]`, `target = 1`
    *   **Output**: `[]`

---

## Detailed Solution (C++)

The backtracking state is defined by the current index `start` in candidates and the `remaining` target sum.
Sorting the candidates beforehand is a vital optimization:
1.  **Early Pruning**: If `candidates[i]` is greater than `remaining`, then all candidates to its right will also be greater than `remaining` (since the array is sorted). We can immediately `break` the loop, pruning the entire subtree.
2.  **Avoiding Duplicates**: We start iterating the loop from the current candidate's index `start`. Since we pass `i` (and not `start` or `0`) as the new `start` in the recursive call, we naturally avoid permutations like `[2, 3, 2]` vs `[2, 2, 3]` and ensure unique combinations.

### Standard C++ Production Code

```cpp
#include <vector>
#include <algorithm>

class Solution {
private:
    void backtrack(const std::vector<int>& candidates, int start, int remaining, std::vector<int>& path, std::vector<std::vector<int>>& result) {
        if (remaining == 0) {
            result.push_back(path);
            return;
        }

        for (int i = start; i < candidates.size(); ++i) {
            // Early Pruning: candidates is sorted, so subsequent candidates will also exceed remaining
            if (candidates[i] > remaining) {
                break;
            }

            path.push_back(candidates[i]);
            // i is passed instead of i + 1 because we can reuse the same element
            backtrack(candidates, i, remaining - candidates[i], path, result);
            path.pop_back(); // Backtrack
        }
    }

public:
    std::vector<std::vector<int>> combinationSum(std::vector<int>& candidates, int target) {
        // Sort candidates to enable early pruning
        std::sort(candidates.begin(), candidates.end());
        
        std::vector<std::vector<int>> result;
        std::vector<int> path;
        
        backtrack(candidates, 0, target, path, result);
        return result;
    }
};
```

---

## Detailed Solution (Python)

The Python implementation mirrors this backtracking strategy. We use list slicing `current[:]` or `list(current)` to push a copy of the path to the results list when `remaining == 0`.

### Standard Python Production Code

```python
from typing import List

class Solution:
    def combinationSum(self, candidates: List[int], target: int) -> List[List[int]]:
        """
        Finds all unique combinations in candidates that sum to target.
        Candidates can be used an unlimited number of times.
        
        Time Complexity: O(N^(T/M + 1))
        Space Complexity: O(T/M)
        """
        result: List[List[int]] = []
        candidates.sort()

        def backtrack(start: int, remaining: int, current: List[int]):
            if remaining == 0:
                result.append(list(current))
                return
            
            for i in range(start, len(candidates)):
                # Early Pruning: since candidates is sorted, candidates[i] > remaining
                # means all subsequent elements are also too large.
                if candidates[i] > remaining:
                    break
                
                current.append(candidates[i])
                # Pass i as start index to allow reuse of the current candidate
                backtrack(i, remaining - candidates[i], current)
                current.pop()

        backtrack(0, target, [])
        return result
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. `list(current)` vs `current[:]`
*   In Python, appending `current` directly to `result` (`result.append(current)`) stores a reference to the mutable list object. As the backtracking algorithm modifies `current`, all entries in `result` would eventually point to the same empty list.
*   To prevent this, we must copy the list. Both `result.append(list(current))` and `result.append(current[:])` create a shallow copy. Performance-wise, they are extremely close, but `list()` is often considered more readable and pythonic.

### 2. Recursion Limit
*   The maximum recursion depth occurs when target is formed by using the smallest candidate repeatedly. If `target = 40` and candidate is `2`, the recursion depth is `20`. This is well below Python’s default stack depth limit of `1000`, so no `RecursionError` will occur.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(N^{\frac{T}{M} + 1})$ | Where $N$ is the number of candidates, $T$ is the target, and $M$ is the minimum value in `candidates`. The height of the recursion tree is at most $T/M$, with a branching factor of at most $N$. Sorting takes $\mathcal{O}(N \log N)$, which is dominated by backtracking. |
| **Space Complexity** | $\mathcal{O}(\frac{T}{M})$ | The recursion stack and the path storage `current` can reach a maximum depth of $T/M$ when selecting the smallest candidate repeatedly. |

---

## Common Follow-Up Questions & How to Answer

### Q1: What if candidates can only be used at most once, and they might contain duplicate numbers? (Combination Sum II)
*   **The Answer**:
    1.  Sort the array first.
    2.  In the backtracking loop, if the current element is equal to the previous element at the same recursion level, skip it to prevent duplicate combinations: `if (i > start && candidates[i] == candidates[i-1]) continue;`.
    3.  Pass `i + 1` to the next recursion level to ensure each number is used at most once.
*   **C++ Implementation Snippet**:
    ```cpp
    for (int i = start; i < candidates.size(); ++i) {
        if (candidates[i] > remaining) break;
        if (i > start && candidates[i] == candidates[i-1]) continue; // Skip duplicates
        path.push_back(candidates[i]);
        backtrack(candidates, i + 1, remaining - candidates[i], path, result); // i + 1
        path.pop_back();
    }
    ```

### Q2: What if we want to find the number of combinations instead of generating all paths? (Combination Sum IV)
*   **The Answer**: Backtracking would be too slow ($\mathcal{O}(N^T)$) and trigger TLE. We can solve it using Dynamic Programming (similar to Unbounded Knapsack/Coin Change). Let `dp[i]` represent the number of combinations that sum up to `i`. The transition is `dp[i] = sum(dp[i - c])` for each candidate `c`.
*   **Python DP Code**:
    ```python
    def combinationSum4(nums: List[int], target: int) -> int:
        dp = [0] * (target + 1)
        dp[0] = 1
        for i in range(1, target + 1):
            for num in nums:
                if i >= num:
                    dp[i] += dp[i - num]
        return dp[target]
    ```

---

## Pro-Tip: How to Impress the Interviewer

*   **Explicitly Highlight Sorting and Early Pruning**: Interviewers look for candidate solutions that optimize early. Explain clearly that sorting candidates reduces the search space significantly by changing the inner loop's condition from an `if` block with a `continue` to a `break`.
*   **Discuss Space Optimization**: Show that storing the result elements consumes memory, and in systems with tight memory limits, yielding solutions lazily via C++ generator structures (like standard coroutines in C++20) or Python generator expressions is ideal.
