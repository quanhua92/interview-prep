# House Robber

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / AI Systems Architect
- **Source**: LeetCode 198, Glassdoor
- **Flashcards**: [Dynamic Programming deck](../../flash_cards/coding/dynamic_programming.md)

---

## Question Description

You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed. The only constraint stopping you from robbing each of them is that adjacent houses have security systems connected, and it will automatically contact the police if two adjacent houses were broken into on the same night.

Given an integer array `nums` representing the amount of money of each house, return *the maximum amount of money you can rob tonight without alerting the police*.

### Examples
*   **Input**: `nums = [1,2,3,1]`
    *   **Output**: `4`
    *   **Explanation**: Rob house 1 (money = 1) and then rob house 3 (money = 3).
        Total amount you can rob = 1 + 3 = 4.
*   **Input**: `nums = [2,7,9,3,1]`
    *   **Output**: `12`
    *   **Explanation**: Rob house 1 (money = 2), rob house 3 (money = 9) and rob house 5 (money = 1).
        Total amount you can rob = 2 + 9 + 1 = 12.

**Constraints**:
*   $1 \le \text{nums.length} \le 100$
*   $0 \le \text{nums}[i] \le 400$

---

## Detailed Solution (C++)

The problem is a classic dynamic programming problem. At each house $i$, the robber has two choices:
1.  **Rob house $i$**: If we rob house $i$, we cannot rob house $i-1$. The total value would be $\text{nums}[i]$ plus the maximum money robbed from houses up to $i-2$.
2.  **Skip house $i$**: If we skip house $i$, the total value would be the maximum money robbed from houses up to $i-1$.

The recurrence relation is:
$$DP[i] = \max(DP[i-1], DP[i-2] + \text{nums}[i])$$

Rather than maintaining a full array of size $n$, we can optimize the space to $\mathcal{O}(1)$ by keeping only two variables representing $DP[i-1]$ (`curr`) and $DP[i-2]$ (`prev`).

### Standard C++ Production Code

```cpp
#include <vector>
#include <algorithm>

class Solution {
public:
    int rob(std::vector<int>& nums) {
        // Guard against empty collection
        if (nums.empty()) {
            return 0;
        }

        int prev = 0; // Represents DP[i-2]
        int curr = 0; // Represents DP[i-1]

        for (int num : nums) {
            int next_rob = std::max(curr, prev + num);
            prev = curr;
            curr = next_rob;
        }

        return curr;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the iterative space-optimized Python implementation.

```python
from typing import List

class Solution:
    def rob(self, nums: List[int]) -> int:
        """
        Calculates the maximum amount of money that can be robbed without alerting the police.
        
        Time Complexity: O(N)
        Space Complexity: O(1)
        """
        if not nums:
            return 0

        prev, curr = 0, 0
        for num in nums:
            # Simultaneously update prev and curr
            prev, curr = curr, max(curr, prev + num)
            
        return curr
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Simultaneous Assignment (`prev, curr = curr, max(curr, prev + num)`)
*   In Python, simultaneous assignments evaluate the entire right-hand side first (creating a temporary tuple in memory) before binding the values to the variables on the left.
*   This allows us to write the state transitions compactly in one line without needing a temporary variable `t`.
*   Behind the scenes, this is highly optimized in CPython, making it faster and cleaner than manual temp-variable swaps.

### 2. Space Optimization
*   Avoid allocating a list `dp = [0] * len(nums)` because it wastes $\mathcal{O}(n)$ memory.
*   Interviewers for systems-related or low-resource roles appreciate the $\mathcal{O}(1)$ auxiliary space optimization, as it avoids heap allocation overhead entirely.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(n)$ | We iterate through the array `nums` exactly once. |
| **Space Complexity** | $\mathcal{O}(1)$ | Only two scalar integer variables are maintained to track the maximum profits. |

---

## Common Follow-Up Questions & How to Answer

### Q1: What if the houses are arranged in a circle? (House Robber II - LeetCode 213)
*   **Answer**: Since the first and the last house are adjacent, robbing both is not allowed. We can split this into two sub-problems:
    1.  Rob houses from index $0$ to $n-2$ (exclude the last house).
    2.  Rob houses from index $1$ to $n-1$ (exclude the first house).
    The overall result is the maximum of these two options.

### Q2: What if the houses are organized in a binary tree? (House Robber III - LeetCode 337)
*   **Answer**: This is solved using Tree DP. For each node, we return a pair of values:
    *   The maximum money if we rob this node: $\text{node.val} + \text{left.notRobbed} + \text{right.notRobbed}$
    *   The maximum money if we do not rob this node: $\max(\text{left.robbed}, \text{left.notRobbed}) + \max(\text{right.robbed}, \text{right.notRobbed})$
    This can be calculated bottom-up using Post-order Traversal in $\mathcal{O}(n)$ time and $\mathcal{O}(h)$ space (call stack depth).

---

## Pro-Tip: How to Impress the Interviewer

*   **Explain Cache Locality**: Discuss how iterating sequentially through the vector utilizes spatial locality. The CPU can easily prefetch elements of `nums` into L1 cache lines, leading to optimal throughput.
*   **Point out Input Mutation**: Some candidates overwrite the input array `nums` to store the DP results. Point out that mutating inputs is generally bad practice in production systems (e.g., if the vector is passed as a `const` reference or is owned/shared by other parts of the application). The variable-based solution is both cleaner and avoids modifying input data.
