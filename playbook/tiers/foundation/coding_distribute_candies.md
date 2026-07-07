# Distribute Candies

- **Category**: Coding
- **Difficulty**: Easy
- **Target Role**: Software Engineer
- **Source**: LeetCode 575, Glassdoor
- **Flashcards**: [Hashmap deck](../../flash_cards/coding/hashmap.md)

---

## Question Description

Alice has $n$ candies, where the $i$-th candy is of type `candyType[i]`. Alice noticed that she started to gain weight, so she visited a doctor.

The doctor advised Alice to only eat $n / 2$ of the candies she has ($n$ is always even). Alice likes her candies very much, and she wants to eat the maximum number of different types of candies while still following the doctor's advice.

Given the integer array `candyType` of length $n$, return the **maximum number of different types** of candies she can eat if she only eats $n / 2$ of them.

### Examples

*   **Input**: `candyType = [1,1,2,2,3,3]`
    *   **Output**: `3`
    *   **Explanation**: Alice can only eat $6 / 2 = 3$ candies. Since there are only 3 types ($1$, $2$, and $3$), she can eat one of each type.

*   **Input**: `candyType = [1,1,2,3]`
    *   **Output**: `2`
    *   **Explanation**: Alice can only eat $4 / 2 = 2$ candies. Whether she eats types `[1,2]`, `[1,3]`, or `[2,3]`, the maximum number of different types she can eat is 2.

*   **Input**: `candyType = [6,6,6,6]`
    *   **Output**: `1`
    *   **Explanation**: Alice can only eat $4 / 2 = 2$ candies. Even though she can eat 2 candies, there is only 1 type of candy available.

### Constraints
*   $n == \text{candyType.length}$
*   $2 \le n \le 10^4$
*   $n$ is even.
*   $-10^5 \le \text{candyType}[i] \le 10^5$

---

## Detailed Solution (C++)

To maximize the number of unique candy types Alice can eat:
1.  Find the number of unique candy types available, $U$. We can count this by inserting all elements of `candyType` into a hash set (`std::unordered_set`).
2.  Alice can eat at most $n / 2$ candies in total.
3.  By the **Pigeonhole Principle**, the maximum number of unique types she can eat is bounded by both the number of unique types available ($U$) and the total candy allowance ($n / 2$).
4.  Therefore, the answer is $\min(U, n / 2)$.

### Standard C++ Production Code

```cpp
#include <vector>
#include <unordered_set>
#include <algorithm>

class Solution {
public:
    int distributeCandies(const std::vector<int>& candyType) {
        // Construct unordered_set to find unique candy types
        std::unordered_set<int> unique_types(candyType.begin(), candyType.end());
        
        int total_allowed = static_cast<int>(candyType.size() / 2);
        int unique_count = static_cast<int>(unique_types.size());
        
        return std::min(unique_count, total_allowed);
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

```python
from typing import List

class Solution:
    def distributeCandies(self, candyType: List[int]) -> int:
        """
        Determines the maximum number of unique candy types Alice can eat.
        
        Time Complexity: O(N)
        Space Complexity: O(N)
        """
        # Convert list to set to extract unique types
        unique_count = len(set(candyType))
        total_allowed = len(candyType) // 2
        
        return min(unique_count, total_allowed)
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Hash Set vs. In-Place Sorting Trade-Off
*   **Hash Set approach (as shown above)**: Runs in $\mathcal{O}(N)$ time and $\mathcal{O}(N)$ space.
*   **In-Place Sorting approach**: We can sort the array `candyType.sort()`, and then scan the array to count unique adjacent elements. This runs in $\mathcal{O}(N \log N)$ time and $\mathcal{O}(1)$ auxiliary space.
*   In memory-constrained environments, the sorting approach is preferred because it avoids heap allocations for set nodes.

### 2. CPython Optimization
*   The Python function `set(candyType)` is implemented at the C level in CPython. It is highly optimized and constructs the set much faster than executing an explicit loop in Python bytecode.

---

## Complexity Analysis

### Hash Set Approach (Primary)

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(N)$ | We iterate through the array of size $N$ once to build the hash set. |
| **Space Complexity** | $\mathcal{O}(N)$ | In the worst case (all candies are unique), the hash set stores $N$ elements. |

---

## Common Follow-Up Questions & How to Answer

### Q1: What if the memory is extremely constrained? How do you solve this in $\mathcal{O}(1)$ auxiliary space?
*   **Answer**: Sort the array in-place, then count the transitions where `candyType[i] != candyType[i-1]`.
    ```python
    class Solution:
        def distributeCandies(self, candyType: List[int]) -> int:
            candyType.sort()
            unique_count = 1
            limit = len(candyType) // 2
            
            for i in range(1, len(candyType)):
                if unique_count >= limit:
                    break
                if candyType[i] != candyType[i-1]:
                    unique_count += 1
                    
            return min(unique_count, limit)
    ```

### Q2: How does this problem relate to the greedy LeetCode 135: Candy problem?
*   **Answer**:
    *   **LeetCode 575**: A simple counting/classification problem bounded by set theory.
    *   **LeetCode 135 (Candy)**: A much harder greedy optimization problem. You must distribute candies to children in a row based on neighboring ratings. It requires a two-pass linear scan (left-to-right and right-to-left) to compute the minimum total candies needed.

---

## Pro-Tip: How to Impress the Interviewer

*   **Pigeonhole Principle Formulation**: Proactively explain the mathematical ceiling of the problem:
    $$\text{Result} = \min(\text{Cardinality of Candy Types}, \text{Half of Candy Count})$$
    Formulating the problem using set cardinalities and bounds shows structured mathematical thinking.
*   **Discuss Cache Inefficiency of Sets**: Mention that in C++, `std::unordered_set` is a bucket-based hash table that incurs significant pointer chasing and memory allocation overhead. For small datasets (e.g. $N \le 64$), sorting the vector using `std::sort` is often faster due to hardware cache prefetching and contiguous memory layouts.
