# Subsets

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / Low-Level Developer / AI Systems Architect
- **Source**: LeetCode 78, Glassdoor
- **Flashcards**: [Backtracking deck](../../flash_cards/coding/backtracking.md)

---

## Question Description

Given an integer array `nums` of **unique** elements, return all possible subsets (the power set).

The solution set **must not** contain duplicate subsets. Return the solution in **any order**.

### Examples

*   **Input**: `nums = [1,2,3]`
    *   **Output**: `[[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]`
*   **Input**: `nums = [0]`
    *   **Output**: `[[],[0]]`

---

## Detailed Solution (C++)

There are two primary paradigms to generate all subsets: **Backtracking** (DFS through the state-space tree) and **Bit Manipulation** (mapping subsets to binary integers). 

In C++, backtracking is the most intuitive approach:
1. Start with an empty path.
2. At each recursive call, the current state represents a valid subset, so we add `path` to the `result` immediately.
3. Iterate from the `start` index to the end of the array, push the element, recurse on `i + 1`, and pop to backtrack.

### Standard C++ Production Code

```cpp
#include <vector>

class Solution {
private:
    void backtrack(const std::vector<int>& nums, int start, std::vector<int>& path, std::vector<std::vector<int>>& result) {
        // Every node visited in the decision tree represents a valid subset
        result.push_back(path);

        for (int i = start; i < nums.size(); ++i) {
            path.push_back(nums[i]);
            backtrack(nums, i + 1, path, result);
            path.pop_back(); // Backtrack
        }
    }

public:
    std::vector<std::vector<int>> subsets(const std::vector<int>& nums) {
        std::vector<std::vector<int>> result;
        std::vector<int> path;
        // Pre-reserve output memory for 2^N elements to avoid vector reallocation
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
    def subsets(self, nums: List[int]) -> List[List[int]]:
        """
        Generates the power set of a list of unique numbers.
        
        Time Complexity: O(2^N * N)
        Space Complexity: O(N)
        """
        result: List[List[int]] = []
        
        def backtrack(start: int, current: List[int]):
            # Append a copy of the current subset
            result.append(list(current))
            
            for i in range(start, len(nums)):
                current.append(nums[i])
                backtrack(i + 1, current)
                current.pop()  # Backtrack

        backtrack(0, [])
        return result
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Cascading (Iterative) Approach
*   Instead of backtracking, Python is extremely well-suited for an iterative, cascading approach. Start with a list containing the empty subset `[[]]`. For each number in `nums`, we iterate through the subsets we have generated so far and create new subsets by adding the number to them.
*   **Python Code**:
    ```python
    def subsets(nums: List[int]) -> List[List[int]]:
        result = [[]]
        for num in nums:
            result += [curr + [num] for curr in result]
        return result
    ```
*   This approach is very clean, avoids recursive function call overhead entirely, and does not require explicit backtracking logic.

### 2. Deep Copies vs. Reference Copying
*   Be careful not to append `current` directly in Python. Since `current` is mutated in place, appending `current` will result in a list of empty lists. Use `list(current)` or `current[:]` to create a copy.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(2^n \cdot n)$ | There are $2^n$ total subsets. For each subset, copying the subset of size at most $n$ takes $\mathcal{O}(n)$ time. |
| **Space Complexity** | $\mathcal{O}(n)$ | The maximum depth of the recursion tree is $n$. The path vector uses at most $\mathcal{O}(n)$ auxiliary space. (Excluding the output size of $\mathcal{O}(2^n \cdot n)$). |

---

## Common Follow-Up Questions & How to Answer

### Q1: How can we implement this using bit manipulation?
*   **The Answer**: A subset of a set with $n$ elements can be represented by a bitmask of length $n$. For each number from $0$ to $2^n - 1$, the $i$-th bit indicates whether the $i$-th element of the array is present in the subset.
*   **C++ Bit Manipulation Implementation**:
    ```cpp
    std::vector<std::vector<int>> subsetsBitmask(const std::vector<int>& nums) {
        int n = nums.size();
        int num_subsets = 1 << n; // 2^n
        std::vector<std::vector<int>> result(num_subsets);
        
        for (int i = 0; i < num_subsets; ++i) {
            for (int j = 0; j < n; ++j) {
                if ((i >> j) & 1) {
                    result[i].push_back(nums[j]);
                }
            }
        }
        return result;
    }
    ```

### Q2: What if the elements in `nums` are not unique? (LeetCode 90: Subsets II)
*   **The Answer**: We must sort the input array. During backtracking, we skip elements that are identical to the previous element in the loop if they are at the same recursion depth:
    ```cpp
    if (i > start && nums[i] == nums[i - 1]) continue;
    ```
*   This ensures that we only branch on the first occurrence of a duplicate element at each level of the recursion tree.

---

## Pro-Tip: How to Impress the Interviewer

*   **Pre-reserve Vector Capacity**: In C++, standard vectors dynamically double their capacity when they exceed their current limits, which involves allocating new memory blocks and copying elements over. Because we know that the power set size is exactly $2^N$, calling `result.reserve(1 << nums.size())` prevents these costly reallocations.
*   **Mention Cache Friendliness of Bitwise Manipulation**: The bit manipulation solution is iteratively constructed and can be parallelized since each subset is calculated independently. It also avoids recursion and function call overhead, making it highly competitive on bare-metal architectures.
*   **Discuss Space Limits**: If the input size is larger (e.g. $N = 30$), the total number of subsets is $2^{30} \approx 10^9$. Point out that storing the output in memory would crash the program due to Out-Of-Memory (OOM) errors, and in real applications, we should process subsets one-by-one or stream them using generator objects.
