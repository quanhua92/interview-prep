# Random Pick Index

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / Low-Level Developer
- **Source**: LeetCode 398, Glassdoor

---

## Question Description

Given an integer array `nums` with possible duplicates, randomly output the index of a given `target` number. You can assume that the given `target` number must exist in the array.

Implement the `Solution` class:

*   `Solution(int[] nums)` Initializes the object with the array `nums`.
*   `int pick(int target)` Picks a random index `i` where `nums[i] == target`. Each index where `nums[i] == target` must have the **same probability** of being returned.

### Examples

*   **Input**:
    ```
    ["Solution", "pick", "pick", "pick"]
    [[[1, 2, 3, 3, 3]], [3], [1], [3]]
    ```
*   **Output**:
    ```
    [null, 4, 0, 2]
    ```
*   **Explanation**:
    ```cpp
    Solution solution({1, 2, 3, 3, 3});
    solution.pick(3); // returns 2, 3, or 4 randomly. Each index should have equal probability (33.3%).
    solution.pick(1); // returns 0 since nums[0] is the only element equal to 1.
    solution.pick(3); // returns 2, 3, or 4 randomly.
    ```

---

## Detailed Solution (C++)

There are two main approaches to this problem, presenting a classic memory-versus-time trade-off:

1.  **Hash Map Precomputation (Time-Optimal for Queries)**:
    *   Store indices of all values in a hash map: `std::unordered_map<int, std::vector<int>>`.
    *   Querying takes $\mathcal{O}(1)$ average time by selecting a random index from the mapped vector.
    *   Requires $\mathcal{O}(N)$ additional space.
2.  **Reservoir Sampling (Space-Optimal)**:
    *   Only store a reference/pointer to `nums` during initialization ($\mathcal{O}(1)$ space).
    *   In `pick(target)`, iterate through `nums` and count matching elements. For the $k$-th matching element, select its index with probability $1/k$.
    *   Querying takes $\mathcal{O}(N)$ time but uses $\mathcal{O}(1)$ auxiliary space.

Below is the **Hash Map Precomputation** approach, which is ideal when multiple queries are expected.

### Standard C++ Production Code

```cpp
#include <vector>
#include <unordered_map>
#include <random>

class Solution {
private:
    std::unordered_map<int, std::vector<int>> idx_map;
    mutable std::mt19937 rng;

public:
    Solution(const std::vector<int>& nums) : rng(std::random_device{}()) {
        for (int i = 0; i < static_cast<int>(nums.size()); ++i) {
            idx_map[nums[i]].push_back(i);
        }
    }
    
    int pick(int target) const {
        const auto& indices = idx_map.at(target);
        std::uniform_int_distribution<size_t> dist(0, indices.size() - 1);
        return indices[dist(rng)];
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

```python
import random
from collections import defaultdict
from typing import List

class Solution:
    def __init__(self, nums: List[int]):
        """
        Initializes the object with the array nums.
        Precomputes indices for O(1) query time.
        """
        self.idx_map = defaultdict(list)
        for i, val in enumerate(nums):
            self.idx_map[val].append(i)

    def pick(self, target: int) -> int:
        """
        Picks a random index where nums[i] == target.
        Time Complexity: O(1)
        """
        # random.choice returns an element from a non-empty sequence in O(1)
        return random.choice(self.idx_map[target])
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Default Dictionary (`defaultdict`)
*   Using `collections.defaultdict(list)` simplifies construction by avoiding boilerplate check-and-initialize operations (`if target not in map: map[target] = []`).
*   This pattern executes faster than standard `dict.setdefault()` in CPython because it relies on C-level lookup optimizations.

### 2. Large Memory Footprint of `defaultdict`
*   Storing a list of indices for every number in the input array can be memory-heavy in Python. Each integer object has a 28-byte overhead, and each list has dynamic resizing overallocation.
*   If memory footprint is constrained, we should implement the **Reservoir Sampling** option.

---

## Complexity Analysis

### Hash Map Precomputation Approach (Shown Above)

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity (Init)** | $\mathcal{O}(N)$ | We iterate through the array of length $N$ exactly once. |
| **Time Complexity (Pick)** | $\mathcal{O}(1)$ average | $\mathcal{O}(1)$ lookup in the hash map and $\mathcal{O}(1)$ random element selection. |
| **Space Complexity** | $\mathcal{O}(N)$ | We store all $N$ indices of the original array in the hash map. |

---

## Common Follow-Up Questions & How to Answer

### Q1: What if the memory is extremely constrained? (Reservoir Sampling Approach)
*   **Answer**: We can implement `pick` in $\mathcal{O}(1)$ auxiliary space and $\mathcal{O}(N)$ time:
    ```cpp
    class Solution {
    private:
        const std::vector<int>& nums_ref;
        mutable std::mt19937 rng;
    public:
        Solution(const std::vector<int>& nums) : nums_ref(nums), rng(std::random_device{}()) {}
        
        int pick(int target) const {
            int result = -1;
            int count = 0;
            for (int i = 0; i < nums_ref.size(); ++i) {
                if (nums_ref[i] == target) {
                    count++;
                    std::uniform_int_distribution<int> dist(1, count);
                    if (dist(rng) == 1) {
                        result = i;
                    }
                }
            }
            return result;
        }
    };
    ```

### Q2: How do we choose between these two approaches in a real system?
*   **Answer**: Compare the Query-to-Init Ratio.
    *   If the number of queries $Q \ll N$, Reservoir Sampling is superior since precomputing indices is wasteful.
    *   If $Q \approx N$ or $Q \gg N$, precomputation is far superior since it amortizes the $\mathcal{O}(N)$ construction time across all queries, resulting in $\mathcal{O}(1)$ per pick.

---

## Pro-Tip: How to Impress the Interviewer

*   **Mention Thread-Safety of RNGs**: Point out that standard random number engines (`std::mt19937` or Python's `random`) are **not thread-safe**. If `pick` is called by multiple threads concurrently, it can lead to race conditions. In C++, marking the random engine `thread_local` resolves this.
*   **Prevent Reference Lifetime Issues**: When storing a reference to `nums` in the Reservoir Sampling constructor, warn the interviewer that the input vector must outlive the `Solution` class instance. If the caller deletes the array, the reference becomes a dangling pointer, leading to undefined behavior.
