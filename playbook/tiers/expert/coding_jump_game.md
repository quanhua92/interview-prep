# Jump Game

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / Low-Level Developer
- **Source**: LeetCode 55, Glassdoor
- **Flashcards**: [Greedy deck](../../flash_cards/coding/greedy.md)

---

## Question Description

You are given an integer array `nums`. You are initially positioned at the array's **first index**, and each element in the array represents your maximum jump length at that position.

Return `true` if you can reach the last index, or `false` otherwise.

### Examples
*   **Input**: `nums = [2,3,1,1,4]`
    *   **Output**: `true`
    *   **Explanation**: Jump 1 step from index 0 to 1, then 3 steps to the last index.
*   **Input**: `nums = [3,2,1,0,4]`
    *   **Output**: `false`
    *   **Explanation**: You will always arrive at index 3 no matter what. Its maximum jump length is 0, which makes it impossible to reach the last index.

---

## Detailed Solution (C++)

The problem can be solved in a single pass using a **Greedy Algorithm**. We maintain a variable `max_reach` representing the farthest index we can reach at any point in time.
1. We iterate through the array from left to right.
2. At each index `i`, we first check if `i` is greater than `max_reach`. If it is, then index `i` is unreachable, meaning we cannot proceed further or reach the end. We immediately return `false`.
3. Otherwise, we update `max_reach` to be $\max(\text{max\_reach}, i + \text{nums}[i])$.
4. If the loop completes successfully, it means we could reach every index along the way, including the last one. We return `true`.

### Standard C++ Production Code

```cpp
#include <vector>
#include <algorithm>

class Solution {
public:
    bool canJump(std::vector<int>& nums) {
        // Edge Case: An empty vector or single-element vector
        if (nums.empty()) {
            return false;
        }

        int max_reach = 0;
        const int n = static_cast<int>(nums.size());

        for (int i = 0; i < n; ++i) {
            // If the current index is beyond the farthest reachable index, we fail
            if (i > max_reach) {
                return false;
            }
            
            // Update the farthest reachable index
            max_reach = std::max(max_reach, i + nums[i]);

            // Early exit: if we can already reach or exceed the last index
            if (max_reach >= n - 1) {
                return true;
            }
        }

        return true;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the type-hinted Python implementation using an optimized iterative loop.

```python
from typing import List

class Solution:
    def canJump(self, nums: List[int]) -> bool:
        """
        Determines if you can reach the last index in a list of maximum jump lengths.
        
        Time Complexity: O(N)
        Space Complexity: O(1)
        """
        if not nums:
            return False

        max_reach = 0
        n = len(nums)

        for i, jump in enumerate(nums):
            # If the current index is beyond the farthest reachable index, we fail
            if i > max_reach:
                return False
            
            # Update the farthest reachable index
            # Inline conditional is faster than calling built-in max() in Python
            current_reach = i + jump
            if current_reach > max_reach:
                max_reach = current_reach

            # Early exit: if we can already reach or exceed the last index
            if max_reach >= n - 1:
                return True

        return True
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Built-in `max()` Function Overhead
*   In Python, calling the built-in `max()` function within a loop introduces function-call overhead. For performance-critical code where $N \le 10^5$, replacing `max_reach = max(max_reach, i + jump)` with an inline `if i + jump > max_reach:` check avoids the overhead of frame creation and variable lookup in Python's VM, leading to a measurable speedup.

### 2. Space Overhead of Recursion / Memoization
*   While Jump Game can be formulated as a Dynamic Programming / DFS + Memoization problem ($O(N^2)$ or $O(N)$ with memoized states), doing so in Python can easily hit the recursion depth limit (default 1000) for large test cases. 
*   Furthermore, storing the memoization table (e.g., via `@lru_cache` or a `list`/`dict`) degrades auxiliary space complexity to $\mathcal{O}(N)$. The greedy approach runs in $\mathcal{O}(1)$ space and is highly preferred.

### 3. Enumeration vs Range Indexing
*   Using `enumerate(nums)` is preferred in Python over `range(len(nums))` when both index and value are needed. `enumerate` is implemented in C and yields a tuple containing the index and object reference directly, minimizing index lookup overhead inside the loop.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(n)$ | We perform a single linear scan of the array. |
| **Space Complexity** | $\mathcal{O}(1)$ | Only a constant number of integer variables are used. |

---

## Common Follow-Up Questions & How to Answer

### Q1: How do we return the minimum number of jumps to reach the last index? (Jump Game II / LeetCode 45)
*   **Answer**: We can solve this greedily as well. Instead of just tracking the absolute farthest index, we track the boundary of the current jump level (`current_end`) and the farthest we can reach with the next jump (`farthest`). Every time we reach `current_end`, we increment our jump count and update `current_end = farthest`.
*   **C++ Snippet**:
    ```cpp
    int jump(const std::vector<int>& nums) {
        int jumps = 0, current_end = 0, farthest = 0;
        for (int i = 0; i < (int)nums.size() - 1; ++i) {
            farthest = std::max(farthest, i + nums[i]);
            if (i == current_end) {
                jumps++;
                current_end = farthest;
            }
        }
        return jumps;
    }
    ```

### Q2: What if we want to print one actual sequence of indices leading to the last index?
*   **Answer**: We can keep a parent array `parent` where `parent[i]` stores the index we jumped from to reach `i`. Since we only need any valid path, we can construct the path during our greedy traversal. Alternatively, we can traverse backward: start from the last index, find the smallest index `j` that can reach `i`, set `parent[i] = j`, and update `i = j` until `i == 0`.

---

## Pro-Tip: How to Impress the Interviewer

*   **Mention Backward Traversal**: Mention that the problem can also be solved by traversing the array from right to left, keeping track of the "closest index that can reach the destination" (initially `n-1`). If we find an index `i` such that `i + nums[i] >= goal`, we update `goal = i`. At the end, if `goal == 0`, return `true`. This backward greedy approach is equivalent but sometimes easier to reason about.
*   **Early-Exit Optimization**: Always include the early exit condition `if (max_reach >= n - 1) return true;`. For arrays where you can jump to the end immediately (e.g., `[100000, 1, 2, ...]`), the algorithm stops on the first iteration rather than scanning the remaining elements.
*   **Explain Hardware Prefetching**: In C++, scanning a contiguous `std::vector` leverages the CPU's L1/L2 cache prefetchers. The greedy forward scan accesses contiguous memory blocks, making it highly cache-friendly compared to recursion or pointer-based structures.
