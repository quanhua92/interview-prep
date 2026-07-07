# Candy

- **Category**: Coding
- **Difficulty**: Hard
- **Target Role**: Software Engineer / Low-Level Developer
- **Source**: LeetCode 135, Glassdoor
- **Flashcards**: [Greedy deck](../../flash_cards/coding/greedy.md)

---

## Question Description

There are $n$ children standing in a line. Each child is assigned a rating value given in the integer array `ratings`.

You are giving candies to these children subjected to the following requirements:
1. Each child must have at least one candy.
2. Children with a higher rating get more candies than their neighbors.

Return the *minimum number of candies* you need to have to distribute the candies to the children.

### Examples
*   **Input**: `ratings = [1,0,2]`
    *   **Output**: `5`
    *   **Explanation**: You can allocate to the first, second, and third child with 2, 1, and 2 candies respectively.
*   **Input**: `ratings = [1,2,2]`
    *   **Output**: `4`
    *   **Explanation**: You can allocate to the first, second, and third child with 1, 2, and 1 candies respectively. The third child gets 1 candy because it satisfies the above two conditions (it has rating 2, which is equal to its left neighbor's rating, not higher).

---

## Detailed Solution (C++)

The problem can be solved efficiently using a **Two-Pass Greedy Algorithm**:
1. **Initialize**: Create a list/array `candies` of size $n$, filled with `1` (since every child must get at least one candy).
2. **Left-to-Right Pass**: Iterate from index $1$ to $n-1$. If `ratings[i] > ratings[i-1]`, we must give child `i` more candies than child `i-1`. Thus, we update `candies[i] = candies[i-1] + 1`. This satisfies the condition for left neighbors.
3. **Right-to-Left Pass**: Iterate from index $n-2$ down to $0$. If `ratings[i] > ratings[i+1]`, child `i` must have more candies than child `i+1`. We update `candies[i] = std::max(candies[i], candies[i+1] + 1)`. This satisfies the condition for right neighbors while preserving the correctness of the left neighbor conditions.
4. **Sum**: The sum of all elements in `candies` is the final answer.

### Standard C++ Production Code

```cpp
#include <vector>
#include <numeric>
#include <algorithm>

class Solution {
public:
    int candy(std::vector<int>& ratings) {
        const int n = static_cast<int>(ratings.size());
        if (n <= 1) {
            return n;
        }

        std::vector<int> candies(n, 1);

        // First pass: satisfy left neighbors
        for (int i = 1; i < n; ++i) {
            if (ratings[i] > ratings[i - 1]) {
                candies[i] = candies[i - 1] + 1;
            }
        }

        // Second pass: satisfy right neighbors
        // Iterate backwards and take the max of current and candies[i+1] + 1
        for (int i = n - 2; i >= 0; --i) {
            if (ratings[i] > ratings[i + 1]) {
                candies[i] = std::max(candies[i], candies[i + 1] + 1);
            }
        }

        // Return the sum of all candies
        return std::accumulate(candies.begin(), candies.end(), 0);
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the type-hinted Python implementation using the two-pass greedy strategy.

```python
from typing import List

class Solution:
    def candy(self, ratings: List[int]) -> int:
        """
        Calculates the minimum number of candies required to satisfy neighbor rating conditions.
        
        Time Complexity: O(N)
        Space Complexity: O(N)
        """
        n = len(ratings)
        if n <= 1:
            return n

        candies = [1] * n

        # Left-to-right pass
        for i in range(1, n):
            if ratings[i] > ratings[i - 1]:
                candies[i] = candies[i - 1] + 1

        # Right-to-left pass
        for i in range(n - 2, -1, -1):
            if ratings[i] > ratings[i + 1]:
                # Inline comparison is faster than max() function in Python
                r_candies = candies[i + 1] + 1
                if r_candies > candies[i]:
                    candies[i] = r_candies

        return sum(candies)
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Built-in `sum()` Utility
*   Summing values in a Python list can be done in-loop or via `sum(candies)`. The built-in `sum()` function is implemented in optimized C and iterates over the list elements without PyObject type checking overhead at each step, making it much faster than an explicit `for x in candies: total += x` loop.

### 2. Avoiding `max()` Function Overhead
*   As with the Jump Game problem, the Python VM incurs frame-allocation overhead when calling the built-in `max()` function. Replacing `candies[i] = max(candies[i], candies[i+1] + 1)` with a simple `if` condition speeds up execution, which is crucial when $N = 2 \times 10^4$.

### 3. Space Allocation Overhead
*   Initializing `candies = [1] * n` is the standard way to allocate a list of size $n$ in Python. This creates $n$ references to the integer object `1`. If memory consumption is a bottleneck, a single-pass $\mathcal{O}(1)$ space slope-tracking method can be implemented instead.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(n)$ | Two linear scans over the array of size $n$. |
| **Space Complexity** | $\mathcal{O}(n)$ | We allocate a dynamic array of size $n$ to track candy distributions. |

---

## Common Follow-Up Questions & How to Answer

### Q1: Can we solve the Candy problem in $\mathcal{O}(1)$ auxiliary space?
*   **Answer**: Yes. We can track slopes (peak and valley patterns) as we walk from left to right:
    *   An increasing ratings sequence forms an **up-slope**.
    *   A decreasing ratings sequence forms a **down-slope**.
    *   When ratings are equal, the slope resets to 0.
    *   We maintain the length of the up-slope and down-slope. When we descend, the height of the valley increases by 1 for each child in the down-slope. If the down-slope length exceeds the peak height, we must retroactively add candies to the peak.
*   **Python Code**:
    ```python
    def candy_constant_space(ratings: List[int]) -> int:
        n = len(ratings)
        if n <= 1:
            return n
        
        candies = 1
        up = 0
        down = 0
        peak = 0
        
        for i in range(1, n):
            if ratings[i] > ratings[i - 1]:
                up += 1
                down = 0
                peak = up
                candies += 1 + up
            elif ratings[i] == ratings[i - 1]:
                up = 0
                down = 0
                peak = 0
                candies += 1
            else:
                down += 1
                up = 0
                # If down-slope matches or exceeds the peak, the peak needs to be taller.
                candies += down + (1 if down > peak else 0)
                
        return candies
    ```

### Q2: What if the children are arranged in a circular formation?
*   **Answer**: In a circular arrangement, index $0$ and index $n-1$ are neighbors. To solve this:
    1. First, find a child whose rating is less than or equal to both of their neighbors. Such a child is a local minimum (valley) and must receive exactly $1$ candy.
    2. Unroll the circular array starting from this child.
    3. Run the standard two-pass greedy algorithm on the unrolled linear array.
    4. Reconnect the circular boundary checks to verify consistency at the endpoints.

---

## Pro-Tip: How to Impress the Interviewer

*   **Proactively Discuss the $O(1)$ Space Optimization**: Before diving straight into coding, explain both the two-pass $\mathcal{O}(n)$ space solution and the single-pass $\mathcal{O}(1)$ space slope-tracking solution. This demonstrates a deep mastery of array parsing algorithms.
*   **Explain Cache Locality**: In C++, accessing `candies` in the backward pass (`i = n-2` down to `0`) works against the hardware prefetcher's forward expectations, but since the array fits entirely in the L1 cache ($2 \times 10^4$ integers $\approx 80 \text{ KB}$), cache miss latency is negligible. 
*   **Use `std::accumulate`**: In C++, rather than writing a manual summing loop, use `<numeric>`'s `std::accumulate`. It is highly expressive, and modern compilers can vectorize it using SIMD (Single Instruction, Multiple Data) instructions automatically.
