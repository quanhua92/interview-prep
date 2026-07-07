# Array Nesting

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / Low-Level Developer
- **Source**: LeetCode 565, Glassdoor
- **Flashcards**: [DFS deck](../../flash_cards/coding/dfs.md)

---

## Question Description

You are given an integer array `nums` of length `n` where `nums` is a **permutation** of the numbers in the range `[0, n - 1]`.

You should build a set $s[k] = \{ \text{nums}[k], \text{nums}[\text{nums}[k]], \text{nums}[\text{nums}[\text{nums}[k]]], \dots \}$ subjected to the following rule:
*   The first element in $s[k]$ starts with $\text{nums}[k]$.
*   The next element in $s[k]$ is $\text{nums}[\text{nums}[k]]$, and then $\text{nums}[\text{nums}[\text{nums}[k]]]$, etc.
*   Stop adding right before a duplicate element occurs in $s[k]$.

Return the **longest length** of a set $s[k]$.

### Examples
*   **Input**: `nums = [5,4,0,3,1,6,2]`
    *   **Output**: `4`
    *   **Explanation**: 
        *   `nums[0] = 5`, `nums[1] = 4`, `nums[2] = 0`, `nums[3] = 3`, `nums[4] = 1`, `nums[5] = 6`, `nums[6] = 2`.
        *   One of the longest sets $s[k]$ is:
            $s[0] = \{ \text{nums}[0], \text{nums}[5], \text{nums}[6], \text{nums}[2] \} = \{ 5, 6, 2, 0 \}$ (length 4).
*   **Input**: `nums = [0,1,2]`
    *   **Output**: `1`

---

## Detailed Solution (C++)

This problem can be modeled as finding the size of the largest **strongly connected component** (specifically, **disjoint cycles**) in a directed graph where each node $i$ has exactly one outgoing edge to $\text{nums}[i]$.
Because `nums` is a permutation of range `[0, n-1]`, every node has an **in-degree of 1** and an **out-degree of 1**. This mathematical property guarantees that:
1. Every element belongs to exactly one closed loop (cycle).
2. The cycles are completely disjoint.

We can traverse each cycle, mark its elements as visited, and measure its length. Once an element is visited, we can skip it in future loops because any start node in the same cycle would produce the same loop.

### Standard C++ Production Code

To optimize memory to $\mathcal{O}(1)$ auxiliary space, we mutate `nums` in-place by setting visited elements to `-1` (an invalid permutation value).

```cpp
#include <vector>
#include <algorithm>

class Solution {
public:
    int arrayNesting(std::vector<int>& nums) noexcept {
        int max_len = 0;
        const int n = static_cast<int>(nums.size());

        for (int i = 0; i < n; ++i) {
            // If the element has been visited, skip it
            if (nums[i] == -1) {
                continue;
            }

            int count = 0;
            int curr = i;
            
            // Traverse the cycle in-place
            while (nums[curr] != -1) {
                int next_idx = nums[curr];
                nums[curr] = -1; // Mark current index as visited
                curr = next_idx;
                count++;
            }
            
            max_len = std::max(max_len, count);
        }

        return max_len;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the Python implementation using the same in-place modification strategy.

```python
from typing import List

class Solution:
    def arrayNesting(self, nums: List[int]) -> int:
        """
        Finds the longest length of nesting sets from a permutation array.
        
        Time Complexity: O(N)
        Space Complexity: O(1) in-place modification
        """
        max_len = 0
        n = len(nums)

        for i in range(n):
            # Skip visited indices
            if nums[i] == -1:
                continue

            count = 0
            curr = i
            
            # Follow the permutation cycle
            while nums[curr] != -1:
                next_idx = nums[curr]
                nums[curr] = -1  # Mark as visited
                curr = next_idx
                count += 1
                
            max_len = max(max_len, count)

        return max_len
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. In-place Mutation Warnings
*   Negating values (e.g. `nums[i] = -nums[i]`) does not work here because `0` is a valid number in the permutation and `0` cannot be distinguished from `-0`.
*   Using `-1` or a sentinel value like `len(nums)` is required.
*   If in-place mutation of the input parameters is forbidden, you must use a boolean array `visited = [False] * len(nums)`. This increases auxiliary space complexity to $\mathcal{O}(n)$.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(n)$ | Each element is visited at most twice (once to mark it as visited, and once in the outer loop check). |
| **Space Complexity** | $\mathcal{O}(1)$ | Modifying the input array in-place avoids allocating any auxiliary arrays or structures. |

---

## Common Follow-Up Questions & How to Answer

### Q1: What if elements can point out-of-bounds or don't form a permutation?
*   **Answer**: If `nums` is not a permutation, elements can have in-degrees other than 1. This means cycles can lead to "tail" nodes (like the shape of a $\rho$ or $\sigma$), and we could get stuck in infinite loops.
    *   To solve this, we must use a cycle detection algorithm (like **Floyd's Tortoise and Hare**) or maintain an explicit state (e.g. `visited` set or three-color DFS: unvisited, visiting, visited) to identify loops.

### Q2: Can we parallelize this cycle detection?
*   **Answer**: Yes. Since all cycles are disjoint, they can be processed independently. 
    *   We can partition the index search space across multiple threads.
    *   To make it thread-safe without locks on a shared `visited` table, we can use atomic flags (`std::atomic<bool>`) or disjoint-set structures.

---

## Pro-Tip: How to Impress the Interviewer

*   **Explain Permutation Group Theory**: Mention that this problem is a direct representation of the **cycle decomposition theorem** in symmetric group theory ($S_n$). Every permutation can be uniquely written as a product of disjoint cycles. Showing this mathematical intuition shows a deep CS background.
*   **Discuss CPU Cache Locality**: Note that while the outer loop is sequential, jumping through `nums[curr]` creates arbitrary memory hops which can cause **cache misses** (non-sequential memory access). Explain that while the algorithm is $\mathcal{O}(n)$ theoretically, cache misses make it slower than a linear scan of memory.
