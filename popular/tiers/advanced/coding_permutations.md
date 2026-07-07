# Permutations

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / Low-Level Developer / AI Systems Architect
- **Source**: LeetCode 46, Glassdoor

---

## Question Description

Given an array `nums` of **distinct** integers, return all the possible permutations. You can return the answer in **any order**.

### Examples

*   **Input**: `nums = [1,2,3]`
    *   **Output**: `[[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]`
*   **Input**: `nums = [0,1]`
    *   **Output**: `[[0,1],[1,0]]`
*   **Input**: `nums = [1]`
    *   **Output**: `[[1]]`

### Constraints
*   $1 \le \text{nums.length} \le 6$
*   $-10 \le \text{nums}[i] \le 10$
*   All the integers of `nums` are **unique**.

---

## Detailed Solution (C++)

There are two primary ways to generate permutations:
1.  **Backtracking with Swapping (In-Place)**: Swap the current element with elements in the range `[start, nums.size() - 1]`, recurse to the next position, and swap back. This method modifies the array in-place, using constant auxiliary space (excluding the recursion stack).
2.  **Iterative Cascading (Level-by-Level Insertion)**: Start with an empty permutation `[[]]`. For each number in `nums`, insert it at all possible positions of the previously generated permutations.

We implement the swap-based backtracking approach as it is the most standard, space-efficient, production-grade technique in C++.

### Standard C++ Production Code

```cpp
#include <vector>
#include <utility>

class Solution {
private:
    void backtrack(std::vector<int>& nums, int start, std::vector<std::vector<int>>& result) {
        // Base case: we have formed a complete permutation
        if (start == nums.size()) {
            result.push_back(nums);
            return;
        }

        for (int i = start; i < nums.size(); ++i) {
            std::swap(nums[start], nums[i]);    // Swapping to place elements at position 'start'
            backtrack(nums, start + 1, result); // Recurse
            std::swap(nums[start], nums[i]);    // Backtrack (restore array)
        }
    }

public:
    std::vector<std::vector<int>> permute(std::vector<int>& nums) {
        std::vector<std::vector<int>> result;
        backtrack(nums, 0, result);
        return result;
    }
};
```

---

## Detailed Solution (Python)

In Python, we can write a clean iterative cascading solution that avoids recursion overhead and builds the permutations by inserting the new element into every possible slot of the existing permutations.

### Standard Python Production Code

```python
from typing import List

class Solution:
    def permute(self, nums: List[int]) -> List[List[int]]:
        """
        Generates all permutations using an iterative cascading approach.
        
        Time Complexity: O(N! * N)
        Space Complexity: O(N! * N)
        """
        perms = [[]]
        
        for num in nums:
            new_perms = []
            for p in perms:
                # Insert the current number at every possible index of the existing permutation
                for i in range(len(p) + 1):
                    new_perms.append(p[:i] + [num] + p[i:])
            perms = new_perms
            
        return perms
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Built-in `itertools.permutations`
*   In Python production code, it is almost always better to use `itertools.permutations(nums)`. It is implemented in C and runs substantially faster than hand-written backtracking loops.
*   **Python Code**:
    ```python
    import itertools
    def permute(nums: List[int]) -> List[List[int]]:
        return [list(p) for p in itertools.permutations(nums)]
    ```
*   In interviews, write the backtracking or cascading approach first, but mention `itertools` to show language proficiency.

### 2. Space Slicing Penalty
*   In the iterative approach, slicing list `p[:i] + [num] + p[i:]` creates three new list objects at each step. While simple, it has higher constant factor overhead compared to in-place backtracking swapping.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(n! \cdot n)$ | There are $n!$ permutations. For each permutation, copying the array of size $n$ takes $\mathcal{O}(n)$ time. |
| **Space Complexity** | $\mathcal{O}(n)$ | For swap-based backtracking, the recursion stack depth is $n$. (Excluding the output size of $\mathcal{O}(n! \cdot n)$). |

---

## Common Follow-Up Questions & How to Answer

### Q1: What if duplicates are allowed in the input array? (Permutations II)
*   **The Answer**:
    1.  Sort the input array `nums`.
    2.  Use a boolean array `visited` of size $n$.
    3.  In the backtracking loop, if `nums[i] == nums[i-1]` and `!visited[i-1]`, skip the element to prevent duplicate branches.
*   **C++ Code Snippet**:
    ```cpp
    void backtrack(const std::vector<int>& nums, std::vector<bool>& visited, std::vector<int>& path, std::vector<std::vector<int>>& result) {
        if (path.size() == nums.size()) {
            result.push_back(path);
            return;
        }
        for (int i = 0; i < nums.size(); ++i) {
            if (visited[i]) continue;
            // Prevent duplicates
            if (i > 0 && nums[i] == nums[i - 1] && !visited[i - 1]) continue;
            
            visited[i] = true;
            path.push_back(nums[i]);
            backtrack(nums, visited, path, result);
            path.pop_back();
            visited[i] = false;
        }
    }
    ```

### Q2: How can we generate permutations in lexicographical order?
*   **The Answer**:
    *   Swap-based backtracking does not naturally generate permutations in lexicographical order.
    *   To get lexicographical order without sorting the final result, we can sort `nums` initially and use `std::next_permutation` in C++, or use the boolean array backtracking strategy where we iterate indices from left to right.
*   **C++ next_permutation example**:
    ```cpp
    std::vector<std::vector<int>> permuteLex(std::vector<int>& nums) {
        std::sort(nums.begin(), nums.end());
        std::vector<std::vector<int>> result;
        do {
            result.push_back(nums);
        } while (std::next_permutation(nums.begin(), nums.end()));
        return result;
    }
    ```

---

## Pro-Tip: How to Impress the Interviewer

*   **In-Place Memory Management**: Emphasize that the swap-based method requires no extra memory allocations for local arrays or visited states. This is ideal for system programming or embedded systems where heap allocation is constrained.
*   **Mention `std::next_permutation` Internals**: Explain that `std::next_permutation` works by finding the longest non-increasing suffix, locating the pivot to the left of it, swapping the pivot with the smallest element in the suffix that is larger than the pivot, and reversing the suffix. Showing you know the underlying mechanics of standard library functions is highly impressive.
