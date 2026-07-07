# Non-decreasing Subsequences

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / AI Systems Architect / QA & Test Engineer
- **Source**: LeetCode 491, Glassdoor

---

## Question Description

Given an integer array `nums`, return all the different possible **non-decreasing subsequences** of the given array with at least two elements. You may return the answer in **any order**.

### Examples

*   **Input**: `nums = [4,6,7,7]`
    *   **Output**: `[[4,6],[4,6,7],[4,6,7,7],[4,7],[4,7,7],[6,7],[6,7,7],[7,7]]`
*   **Input**: `nums = [4,4,3,2,1]`
    *   **Output**: `[[4,4]]`

### Constraints
*   $1 \le \text{nums.length} \le 15$
*   $-100 \le \text{nums}[i] \le 100$

---

## Detailed Solution (C++)

Generating subsequences is a classic backtracking problem. However, there are two tricky constraints here:
1.  **Non-decreasing Order**: We can only pick `nums[i]` if it is greater than or equal to the last element in our current path.
2.  **No Duplicate Subsequences**: Since `nums` may contain duplicate values (e.g. two `7`s in `[4, 6, 7, 7]`), we might generate the same subsequence multiple times.

Because we **cannot** sort the input array (doing so would change the indices and thus violate the subsequence definition), standard duplicate skipping techniques like `nums[i] == nums[i-1]` cannot be used. Instead:
*   We use a local `std::unordered_set` (or a flat boolean lookup table) inside each recursion level to track which values have already been chosen as the next element at the current depth.

### Standard C++ Production Code

```cpp
#include <vector>
#include <unordered_set>
#include <algorithm>

class Solution {
private:
    void backtrack(const std::vector<int>& nums, int start, std::vector<int>& path, std::vector<std::vector<int>>& result) {
        // Collect valid non-decreasing subsequences of length >= 2
        if (path.size() >= 2) {
            result.push_back(path);
        }

        // Local lookup set to avoid duplicates at the current level of the decision tree
        std::unordered_set<int> used;

        for (int i = start; i < nums.size(); ++i) {
            // Check if this value has already been branched on at this level
            if (used.count(nums[i])) {
                continue;
            }

            // Ensure non-decreasing constraint
            if (path.empty() || nums[i] >= path.back()) {
                used.insert(nums[i]);
                path.push_back(nums[i]);
                backtrack(nums, i + 1, path, result);
                path.pop_back(); // Backtrack
            }
        }
    }

public:
    std::vector<std::vector<int>> findSubsequences(const std::vector<int>& nums) {
        std::vector<std::vector<int>> result;
        std::vector<int> path;
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
    def findSubsequences(self, nums: List[int]) -> List[List[int]]:
        """
        Finds all different non-decreasing subsequences with at least two elements.
        
        Time Complexity: O(2^N * N)
        Space Complexity: O(N)
        """
        result: List[List[int]] = []

        def backtrack(start: int, path: List[int]):
            if len(path) >= 2:
                result.append(list(path))
            
            # Local set to prevent duplicates at the current level of recursion
            used = set()

            for i in range(start, len(nums)):
                if nums[i] in used:
                    continue
                if not path or nums[i] >= path[-1]:
                    used.add(nums[i])
                    path.append(nums[i])
                    backtrack(i + 1, path)
                    path.pop()

        backtrack(0, [])
        return result
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Hash Set Allocation Overhead
*   Creating a `set()` at each level of the recursion tree incurs some dynamic memory overhead in Python. Since $N \le 15$, the recursion depth is small enough that this remains highly performant.
*   An alternative representation is to use a simple boolean bitmask array if the values are tightly bounded, which is much faster than hashing.

### 2. Time-Complexity of `list(path)`
*   Similar to other backtracking problems, calling `list(path)` creates a copy of the list. Since the maximum length of `path` is $N$, each copy takes $\mathcal{O}(N)$ time.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(2^N \cdot N)$ | Where $N$ is the number of elements. There are $2^N$ possible subsequences, and copying a path into the result takes $\mathcal{O}(N)$ time in the worst case. |
| **Space Complexity** | $\mathcal{O}(N)$ | The height of the recursion stack is at most $N$. If we count the size of the local deduplication sets, the auxiliary space is bounded by $\mathcal{O}(N^2)$ (since we have at most $N$ active recursion frames, each holding a set of size at most $N$). |

---

## Common Follow-Up Questions & How to Answer

### Q1: Why can't we sort the array first to skip duplicates using `nums[i] == nums[i-1]`?
*   **The Answer**: Because the question asks for **subsequences**, which preserves the relative order of elements from the original array. Sorting the array would alter the relative ordering. For example, in `[4, 4, 3, 2, 1]`, the subsequence `[4, 4]` is valid, but if we sorted it to `[1, 2, 3, 4, 4]`, we would generate invalid subsequences like `[1, 2]`.

### Q2: How can we implement this without using hash sets at all?
*   **The Answer**: Since the values are constrained to $[-100, 100]$, we can use a local fixed-size array/buffer or a bitset instead of an `unordered_set`. 
*   **C++ Array-Based Optimization**:
    ```cpp
    // Since nums[i] is between -100 and 100, we offset by 100 to map it to [0, 200]
    bool used[201] = {false};
    for (int i = start; i < nums.size(); ++i) {
        int val_offset = nums[i] + 100;
        if (used[val_offset]) continue;
        if (path.empty() || nums[i] >= path.back()) {
            used[val_offset] = true;
            path.push_back(nums[i]);
            backtrack(nums, i + 1, path, result);
            path.pop_back();
        }
    }
    ```
*   This approach avoids heap allocation completely, resulting in a substantial performance boost.

---

## Pro-Tip: How to Impress the Interviewer

*   **Mention Value-Range Offsetting**: Proactively note that the values are constrained to $[-100, 100]$. Pointing out that you can replace the `unordered_set` with a `bool used[201]` array to prevent heap allocation shows strong low-level hardware awareness (cache locality, stack allocation vs heap allocation).
*   **Discuss Bitmask Alternatives**: Mention that for very small ranges, bitmasks are extremely efficient because checking/setting a bit takes single-cycle CPU instructions (`OR`, `AND`, `SHIFT`), which are ideal for high-performance and low-latency code.
