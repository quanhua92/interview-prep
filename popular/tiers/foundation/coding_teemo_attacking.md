# Teemo Attacking

- **Category**: Coding
- **Difficulty**: Easy
- **Target Role**: Software Engineer / Low-Level Developer
- **Source**: LeetCode 495, Glassdoor

---

## Question Description

Our hero Teemo is attacking an enemy Ashe with poison attacks! When Teemo attacks Ashe, Ashe gets poisoned for exactly `duration` seconds. More formally, an attack at second `t` will mean Ashe is poisoned during the inclusive time interval `[t, t + duration - 1]`. If Teemo attacks again before the poison effect ends, the timer for it is reset, and the poison effect will end `duration` seconds after the new attack.

You are given a non-decreasing integer array `timeSeries`, where `timeSeries[i]` denotes that Teemo attacks Ashe at second `timeSeries[i]`, and an integer `duration`.

Return *the total number of seconds that Ashe is poisoned*.

### Examples
*   **Input**: `timeSeries = [1,4]`, `duration = 2`
    *   **Output**: `4`
    *   **Explanation**: Teemo's attacks on Ashe go as follows:
        *   At second 1, Teemo attacks, and Ashe is poisoned for seconds 1 and 2.
        *   At second 4, Teemo attacks, and Ashe is poisoned for seconds 4 and 5.
        *   Ashe is poisoned for seconds 1, 2, 4, and 5, which is 4 seconds in total.
*   **Input**: `timeSeries = [1,2]`, `duration = 2`
    *   **Output**: `3`
    *   **Explanation**: Teemo's attacks on Ashe go as follows:
        *   At second 1, Teemo attacks, and Ashe is poisoned for seconds 1 and 2.
        *   At second 2, Teemo attacks again and resets the poison timer. Ashe is poisoned for seconds 2 and 3.
        *   Ashe is poisoned for seconds 1, 2, and 3, which is 3 seconds in total.

---

## Detailed Solution (C++)

This problem can be modeled as a simplified interval-merging simulation.
1.  Because `timeSeries` is already sorted in non-decreasing order, we can compare adjacent elements.
2.  For any attack $i$ at `timeSeries[i]`, the poison lasts until `timeSeries[i] + duration`.
3.  If the next attack at `timeSeries[i+1]` occurs before the current poison expires, the actual poisoned duration for attack $i$ is capped at `timeSeries[i+1] - timeSeries[i]`.
4.  Otherwise, the poison runs its full course of `duration` seconds.
5.  Thus, the poison duration contributed by attack $i$ is:
    $$\min(\text{duration}, \text{timeSeries}[i+1] - \text{timeSeries}[i])$$
6.  The last attack (at index $n-1$) always runs for the full `duration` because there are no subsequent attacks.

### Standard C++ Production Code

```cpp
#include <vector>
#include <algorithm>

class Solution {
public:
    int findPoisonedDuration(const std::vector<int>& timeSeries, int duration) noexcept {
        // Edge Case: No attacks
        if (timeSeries.empty()) {
            return 0;
        }

        int totalDuration = 0;
        const size_t n = timeSeries.size();

        // Calculate the poisoned time contributed by each attack up to the second-to-last
        for (size_t i = 0; i < n - 1; ++i) {
            totalDuration += std::min(duration, timeSeries[i + 1] - timeSeries[i]);
        }

        // The final attack is guaranteed to run for the full duration
        return totalDuration + duration;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the type-hinted Python implementation. It avoids indexing errors by iterating through the array up to the second-to-last element.

```python
from typing import List

class Solution:
    def findPoisonedDuration(self, timeSeries: List[int], duration: int) -> int:
        """
        Calculates the total duration of the poison effect.
        
        Time Complexity: O(N)
        Space Complexity: O(1)
        """
        if not timeSeries:
            return 0

        total_duration = 0
        n = len(timeSeries)

        # Iterate over consecutive attack timestamps
        for i in range(n - 1):
            total_duration += min(duration, timeSeries[i + 1] - timeSeries[i])

        # Add the full duration for the last attack
        return total_duration + duration
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Large Integers and Precision
*   The constraints mention that `timeSeries[i]` and `duration` can be up to $10^7$, and the length of the array can be up to $10^4$.
*   The maximum potential answer is $10^4 \times 10^7 = 10^{11}$, which fits easily within a standard 64-bit integer. Python handles arbitrarily large integers automatically, so overflow is not a concern. In C++, a standard 32-bit signed `int` goes up to $\approx 2 \times 10^9$, so $10^{11}$ would overflow a 32-bit signed integer. However, since the LeetCode return type is `int` (implying tests fit in 32-bit), standard `int` is used, but pointing this out to the interviewer shows excellent low-level engineering foresight.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(n)$ | We scan the `timeSeries` array of size $n$ in a single pass. |
| **Space Complexity** | $\mathcal{O}(1)$ | No extra memory structures are allocated; only a few scalar variables are maintained. |

---

## Common Follow-Up Questions & How to Answer

### Q1: How does this problem relate to the Merge Intervals pattern?
*   **The Answer**: Each attack represents an interval `[timeSeries[i], timeSeries[i] + duration - 1]`.
    *   If we used the standard **Merge Intervals** algorithm, we would sort the intervals and merge overlaps, which takes $\mathcal{O}(n \log n)$ or $\mathcal{O}(n)$ time and $\mathcal{O}(n)$ space.
    *   However, since the intervals are already sorted by start time and have a fixed length, we can calculate the union size on the fly. This optimization reduces the auxiliary space complexity from $\mathcal{O}(n)$ to $\mathcal{O}(1)$.

### Q2: What if we have variable durations for each attack (e.g. `durationSeries[i]`)?
*   **The Answer**: If durations vary, a simple pairwise comparison is no longer sufficient. An earlier attack with a very long duration could overlap and fully cover subsequent attacks.
    *   To solve this, we can maintain the end time of the active poison: `current_poison_end`.
    *   For each attack at `t = timeSeries[i]` with duration `d = durationSeries[i]`:
        *   If `t > current_poison_end` (no overlap), we add `d` to our total, and update `current_poison_end = t + d`.
        *   If `t <= current_poison_end` (overlap), we only add the incremental portion: if `t + d > current_poison_end`, we add `(t + d) - current_poison_end` to our total, and update `current_poison_end = t + d`.
    *   This sweep-line logic still takes $\mathcal{O}(n)$ time and $\mathcal{O}(1)$ space.

---

## Pro-Tip: How to Impress the Interviewer

*   **Mention 32-bit Integer Overflow**: Point out that if the cumulative poison duration exceeds $2^{31} - 1$, a standard 32-bit signed integer in C++ will overflow. Suggesting the use of `long long` for the accumulator variable (`totalDuration`) demonstrates a production-first mindset regarding mathematical overflow.
*   **Discuss Compiler Vectorization**: Note that the loop only performs basic arithmetic (`min` and subtraction) on contiguous elements of `timeSeries`. Because there are no data dependencies between iterations (each step relies solely on $i$ and $i+1$), modern compilers can auto-vectorize this loop using SIMD instructions (AVX/SSE) to process multiple attacks per CPU cycle.
