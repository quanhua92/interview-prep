# Random Pick with Weight

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / AI Systems Architect
- **Source**: LeetCode 528, Glassdoor
- **Flashcards**: [Prefix Sum deck](../../flash_cards/coding/prefix_sum.md)

---

## Question Description

You are given a **0-indexed** array of positive integers `w` where `w[i]` describes the weight of the $i$-th index.

You need to implement the class `Solution` with the following methods:
*   `Solution(w)` Initializes the object with the weights `w`.
*   `pickIndex()` Returns a randomly picked index in the range `[0, w.length - 1]` (inclusive). The probability of picking an index `i` must be `w[i] / sum(w)`.

### Examples
*   **Input**:
    `["Solution", "pickIndex"]`
    `[[[1]], []]`
    *   **Output**: `[null, 0]`
    *   **Explanation**: `Solution solution = new Solution([1]); solution.pickIndex();` returns 0. The only option is to return 0 since there is only one element in `w`.
*   **Input**:
    `["Solution", "pickIndex", "pickIndex", "pickIndex", "pickIndex", "pickIndex"]`
    `[[[1, 3]], [], [], [], [], []]`
    *   **Output**: `[null, 1, 1, 1, 1, 0]`
    *   **Explanation**: `Solution solution = new Solution([1, 3]);`
        `pickIndex()` has a $75\%$ chance of returning `1` and $25\%$ chance of returning `0`.

---

## Detailed Solution (C++)

To implement weighted random selection efficiently:
1. **Prefix Sum Construction**: Compute the running prefix sums of weights. For example, if weights are `[1, 3]`, prefix sums are `[1, 4]`.
2. The total sum of weights is `prefix.back()`.
3. **Random Selection**: Generate a random integer `t` in the range $[1, \text{totalSum}]$.
4. **Binary Search**: Since the prefix sums are strictly increasing (weights are positive integers), we can perform binary search to find the first index `i` where `prefix[i] >= t`. This can be done in $\mathcal{O}(\log n)$ time using `std::lower_bound`.

### Standard C++ Production Code

To write production-grade C++, we use `<random>` (Mersenne Twister `std::mt19937`) instead of `rand()`, since `rand()` suffers from bias and poor distribution.

```cpp
#include <vector>
#include <random>
#include <algorithm>

class Solution {
private:
    std::vector<int> prefix;
    std::mt19937 gen;
    std::uniform_int_distribution<int> dis;

public:
    Solution(const std::vector<int>& w) : gen(std::random_device{}()) {
        int total = 0;
        prefix.reserve(w.size());
        for (int x : w) {
            total += x;
            prefix.push_back(total);
        }
        // Set the uniform distribution range [1, total]
        dis = std::uniform_int_distribution<int>(1, total);
    }
    
    int pickIndex() {
        int target = dis(gen);
        // Find the first prefix sum >= target
        auto it = std::lower_bound(prefix.begin(), prefix.end(), target);
        return static_cast<int>(std::distance(prefix.begin(), it));
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the Python implementation using `random.randint` and the built-in `bisect` library for binary search.

```python
import random
import bisect
from typing import List

class Solution:

    def __init__(self, w: List[int]):
        """
        Initializes the prefix sum array from weights.
        """
        self.prefix = []
        total = 0
        for x in w:
            total += x
            self.prefix.append(total)
        self.total = total

    def pickIndex(self) -> int:
        """
        Picks a random index with probability proportional to its weight.
        
        Time Complexity: O(log N)
        Space Complexity: O(1) auxiliary
        """
        # Generate a random integer between 1 and the sum of weights (inclusive)
        target = random.randint(1, self.total)
        
        # Binary search for the first prefix sum >= target
        # bisect_left returns the insertion point where prefix[i] >= target
        return bisect.bisect_left(self.prefix, target)
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. `random.randint` vs `random.random`
*   `random.randint(1, self.total)` generates a random integer in the closed interval $[1, \text{total}]$, which aligns cleanly with discrete weights.
*   Alternatively, you can generate a float $u \in [0.0, 1.0)$ using `random.random()` and multiply by `self.total`. However, floating-point precision limits can theoretically cause boundary issues (e.g., $u \cdot \text{total}$ rounding up incorrectly). Discrete integer random selection is preferred.

### 2. Built-in `bisect` Module
*   In Python, you should always prefer the built-in `bisect` module over a manually written binary search loop. The `bisect` module is written in C under the hood, making it significantly faster than equivalent Python code.

---

## Complexity Analysis

| Operation | Time Complexity | Space Complexity | Description |
| :--- | :--- | :--- | :--- |
| **Constructor** | $\mathcal{O}(n)$ | $\mathcal{O}(n)$ | To store the prefix sum array of size $n$. |
| **pickIndex** | $\mathcal{O}(\log n)$ | $\mathcal{O}(1)$ | Binary search over the prefix sum array. |

---

## Common Follow-Up Questions & How to Answer

### Q1: What if weights can be modified dynamically (e.g., `updateWeight(index, val)`)?
*   **Answer**: If weights are dynamic, using a prefix sum array would require $\mathcal{O}(n)$ to update. To support both update and random selection efficiently, we can use a **Segment Tree** or a **Fenwick Tree (Binary Indexed Tree)**:
    *   **Updates**: Can be done in $\mathcal{O}(\log n)$ time.
    *   **Queries/Binary Search**: We can search the tree in $\mathcal{O}(\log n)$ time.
    *   This provides a balanced solution where both methods run in logarithmic time.

### Q2: Can we achieve O(1) query time for pickIndex?
*   **Answer**: Yes, by using the **Alias Method (Walker's Alias Method)**:
    *   The Alias Method is a family of algorithms for efficient sampling from a discrete probability distribution.
    *   It requires $\mathcal{O}(n)$ preprocessing time to construct two tables: a probability table and an alias table.
    *   Once constructed, `pickIndex` can be performed in **$\mathcal{O}(1)$ time** and $\mathcal{O}(1)$ space by choosing a random index $i$ and then flipping a biased coin to decide whether to return $i$ or its alias table entry.

---

## Pro-Tip: How to Impress the Interviewer

*   **Mention Walker's Alias Method**: Proactively mentioning Walker's Alias Method for $\mathcal{O}(1)$ query time shows a deep, production-level expertise in randomized algorithms and sampling, which is highly relevant in fields like graphics, machine learning, and game design.
*   **Show PRNG Hygiene**: In C++, explain why you avoided `rand() % total`. `rand()` typically has a low max value (`RAND_MAX` is only $32767$ on some compilers), causing significant bias when the total weight exceeds it. Using the modern C++ `<random>` library shows you write safe, enterprise-grade code.
