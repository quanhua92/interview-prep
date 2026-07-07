# Gas Station

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / Low-Level Developer
- **Source**: LeetCode 134, Glassdoor

---

## Question Description

There are $n$ gas stations along a circular route, where the amount of gas at the $i$-th station is `gas[i]`.

You have a car with an unlimited gas tank and it costs `cost[i]` of gas to travel from the $i$-th station to its next $(i + 1)$-th station. You begin the journey with an empty tank at one of the gas stations.

Given two integer arrays `gas` and `cost`, return the starting gas station's index if you can travel around the circuit once in the clockwise direction, otherwise return `-1`. If there exists a solution, it is guaranteed to be unique.

### Examples
*   **Input**: `gas = [1,2,3,4,5]`, `cost = [3,4,5,1,2]`
    *   **Output**: `3`
    *   **Explanation**:
        *   Start at station 3 (index 3) and fill up with 4 units of gas. Your tank = 0 + 4 = 4.
        *   Travel to station 4. Your tank = 4 - 1 + 5 = 8.
        *   Travel to station 0. Your tank = 8 - 2 + 1 = 7.
        *   Travel to station 1. Your tank = 7 - 3 + 2 = 6.
        *   Travel to station 2. Your tank = 6 - 4 + 3 = 5.
        *   Travel to station 3. The cost is 5. Your gas is just enough to travel back to station 3.
        *   Therefore, return 3 as the starting index.
*   **Input**: `gas = [2,3,4]`, `cost = [3,4,3]`
    *   **Output**: `-1`
    *   **Explanation**:
        *   You can't start at station 0 or 1, as there is not enough gas to travel to the next station.
        *   Let's start at station 2 and fill up with 4 units of gas. Your tank = 0 + 4 = 4.
        *   Travel to station 0. Your tank = 4 - 3 + 2 = 3.
        *   Travel to station 1. Your tank = 3 - 3 + 3 = 3.
        *   You cannot travel back to station 2, as it requires 4 units of gas but you only have 3.
        *   Therefore, you can't travel around the circuit once no matter where you start.

---

## Detailed Solution (C++)

The problem is solved using a **Greedy Algorithm** in a single pass. 

### Mathematical Proof of Correctness
1. **Total Surplus Condition**: If the sum of all elements in `gas` is greater than or equal to the sum of all elements in `cost` (i.e., $\sum (\text{gas}[i] - \text{cost}[i]) \ge 0$), a valid starting gas station is guaranteed to exist. If the total sum is negative, it is mathematically impossible to complete the circuit, and we immediately return `-1`.
2. **Greedy Start Reset**: Let's say we start at station $A$ and reach station $B$ where we can no longer proceed to $B+1$ because our `current_surplus` becomes negative. This implies that for any station $C$ between $A$ and $B$ ($A \le C < B$), starting at $C$ will also fail to reach $B+1$. 
   * *Proof*: When starting at $A$, our gas tank when we arrived at $C$ was $\ge 0$. If we couldn't make it to $B+1$ starting from $A$ with a boost (or neutral tank) at $C$, then starting at $C$ with $0$ gas will definitely fail. Thus, we can safely reset our candidate starting station to $B+1$ and reset our `current_surplus` to 0.

### Standard C++ Production Code

```cpp
#include <vector>
#include <numeric>

class Solution {
public:
    int canCompleteCircuit(std::vector<int>& gas, std::vector<int>& cost) {
        int total_surplus = 0;
        int current_surplus = 0;
        int start = 0;
        const int n = static_cast<int>(gas.size());

        for (int i = 0; i < n; ++i) {
            int diff = gas[i] - cost[i];
            total_surplus += diff;
            current_surplus += diff;

            // If the tank goes negative, we cannot start at 'start' or any station up to 'i'.
            if (current_surplus < 0) {
                start = i + 1;       // Next candidate starting station
                current_surplus = 0;  // Reset tank for the new candidate
            }
        }

        // If the total gas accumulated is less than total cost, no solution exists.
        return total_surplus >= 0 ? start : -1;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the optimized, type-hinted Python implementation using `zip` to avoid indexing overhead.

```python
from typing import List

class Solution:
    def canCompleteCircuit(self, gas: List[int], cost: List[int]) -> int:
        """
        Finds the unique starting gas station's index to complete the circular route.
        
        Time Complexity: O(N)
        Space Complexity: O(1)
        """
        total_surplus = 0
        current_surplus = 0
        start = 0

        # zip() allows us to loop through both lists concurrently and is faster in Python
        # than indexing gas[i] and cost[i] directly because it minimizes indexing overhead.
        for i, (g, c) in enumerate(zip(gas, cost)):
            diff = g - c
            total_surplus += diff
            current_surplus += diff
            
            if current_surplus < 0:
                start = i + 1
                current_surplus = 0

        return start if total_surplus >= 0 else -1
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Loop Optimization via `zip()`
*   In Python, accessing lists using index lookup (e.g., `gas[i]`) within a loop requires pointer indirection and bounds checking.
*   Using `zip(gas, cost)` creates an iterator in C that yields pairs of values directly. Combined with `enumerate()`, it provides both the index and values at maximum performance.

### 2. Large Sum Integer Overflow Safety
*   In languages like C or C++, accumulating `total_surplus` can theoretically overflow fixed-width integers if $n = 10^5$ and gas/cost values are extremely large (though not possible under LeetCode constraints where values $\le 10^4$).
*   In Python, integers have arbitrary precision, so accumulator overflow is never an issue. However, in C++, using `int` is safe here since the maximum possible total surplus is $10^5 \times 10^4 = 10^9$, which fits comfortably inside a standard 32-bit signed integer (limit $\approx 2.14 \times 10^9$).

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(n)$ | Single pass over the gas and cost arrays. |
| **Space Complexity** | $\mathcal{O}(1)$ | Auxiliary space is constant since we only store a few scalar variables. |

---

## Common Follow-Up Questions & How to Answer

### Q1: What if the solution is not unique? How do we find the starting index that maximizes the remaining gas at the end?
*   **Answer**: The greedy logic works because if a solution exists, any starting point that completes the circuit must accumulate positive surplus throughout the journey. To find the starting index that maximizes the final remaining gas (or the minimum gas dip during the trip), we can look at the cumulative prefix sum of `gas[i] - cost[i]`. The starting index that minimizes the minimum cumulative valley of our prefix sum will leave us with the highest gas cushion. In fact, the station immediately *after* the global minimum of the prefix sum is always the optimal start.

### Q2: Can we solve this problem using Kadane's algorithm?
*   **Answer**: Yes, conceptually. The problem is equivalent to finding a contiguous subarray of size $n$ in a doubled array (representing circularity) that has no negative prefix sums. Our greedy restart mechanism mirrors Kadane's reset step (`if current_surplus < 0: current_surplus = 0`).

---

## Pro-Tip: How to Impress the Interviewer

*   **Explain the Prefix Sum Minimum Interpretation**: Impress the interviewer by mentioning that this problem is equivalent to finding the minimum value in the cumulative prefix sums of `diff = gas[i] - cost[i]`. If we plot the prefix sum of `diff` as a curve, the starting station must be the index right after the global minimum. This is because starting there shifts the curve upward, ensuring that the cumulative sum never drops below zero.
*   **Explicit Loop Bounds and Casts**: In C++, casting `gas.size()` to a signed `int` via `static_cast<int>` or using a `std::size_t` loop index prevents compiler warnings regarding signed/unsigned comparisons.
*   **Single-Pass Guarantee**: Emphasize that because we check `total_surplus >= 0` at the very end, we do not need to perform a second pass to simulate the circular trip. This mathematical guarantee saves $50\%$ of instruction cycles.
