# Koko Eating Bananas

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / Low-Level Developer / AI Systems Architect
- **Source**: LeetCode 875, Glassdoor
- **Flashcards**: [Modified Binary Search deck](../../flash_cards/coding/modified_binary_search.md)

---

## Question Description

Koko loves to eat bananas. There are $n$ piles of bananas, the $i^{\text{th}}$ pile has `piles[i]` bananas. The guards have gone and will come back in $h$ hours.

Koko can decide her bananas-per-hour eating speed of $k$. Each hour, she chooses some pile of bananas and eats $k$ bananas from that pile. If the pile has less than $k$ bananas, she eats all of them instead and will not eat any more bananas during this hour.

Koko likes to eat slowly but still wants to finish eating all the bananas before the guards return.

Return *the minimum integer $k$ such that she can eat all the bananas within $h$ hours*.

### Examples
*   **Input**: `piles = [3,6,7,11]`, `h = 8`
    *   **Output**: `4`
*   **Input**: `piles = [30,11,23,4,20]`, `h = 5`
    *   **Output**: `30`
*   **Input**: `piles = [30,11,23,4,20]`, `h = 6`
    *   **Output**: `23`

---

## Detailed Solution (C++)

This problem can be resolved using **Binary Search on the Answer**.

1.  **Define the Search Space `[left, right]`**:
    *   `left` (minimum possible speed): Koko must eat at least $1$ banana per hour, so `left = 1`.
    *   `right` (maximum possible speed): Koko can eat at most one pile per hour. Therefore, if she eats at a speed equal to the maximum pile size (`max(piles)`), she will finish each pile in exactly $1$ hour. Any speed greater than `max(piles)` is redundant because she cannot eat from multiple piles within the same hour. Thus, `right = max(piles)`.
2.  **Binary Search**:
    *   We search in the range `[1, max(piles)]`.
    *   For a candidate speed `mid`, we calculate the total hours needed to finish all piles:
        $$\text{Hours} = \sum_{i=0}^{n-1} \lceil \text{piles}[i] / \text{mid} \rceil$$
    *   If $\text{Hours} \le h$, then `mid` is a valid speed. We try to find a slower speed by setting `right = mid`.
    *   If $\text{Hours} > h$, Koko cannot finish in time. We must increase the speed by setting `left = mid + 1`.

### Standard C++ Production Code

```cpp
#include <vector>
#include <algorithm>

class Solution {
private:
    // Helper function to calculate total hours needed for eating speed k
    long long hoursNeeded(const std::vector<int>& piles, int k) noexcept {
        long long total = 0;
        for (int v : piles) {
            // Integer ceiling division: ceil(v / k) is equivalent to (v + k - 1) / k
            total += (static_cast<long long>(v) + k - 1) / k;
        }
        return total;
    }

public:
    int minEatingSpeed(const std::vector<int>& piles, int h) {
        int left = 1;
        int right = *std::max_element(piles.begin(), piles.end());

        while (left < right) {
            int mid = left + (right - left) / 2;
            
            if (hoursNeeded(piles, mid) <= h) {
                right = mid;      // mid is feasible, try to find a slower speed
            } else {
                left = mid + 1;   // too slow, must increase speed
            }
        }

        return left;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the type-hinted Python implementation. It utilizes integer division arithmetic to compute the ceiling values without floating-point precision issues.

```python
from typing import List

class Solution:
    def minEatingSpeed(self, piles: List[int], h: int) -> int:
        """
        Finds the minimum speed k to finish all bananas in h hours.
        
        Time Complexity: O(n * log(M)) where M is max(piles).
        Space Complexity: O(1) auxiliary
        """
        left, right = 1, max(piles)

        # Binary search on speed range
        while left < right:
            mid = left + (right - left) // 2
            
            # Integer-based ceiling division: (p + mid - 1) // mid
            # Sum the eating hours required for all piles at speed mid
            hours = sum((p + mid - 1) // mid for p in piles)
            
            if hours <= h:
                right = mid       # mid speed works, try to find a slower speed
            else:
                left = mid + 1    # Koko needs to eat faster
                
        return left
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Integer Ceiling Division vs `math.ceil`
*   In Python, calling `math.ceil(p / mid)` converts the division result into a floating-point number. Floats in Python are double-precision numbers (64-bit IEEE 754) which have $53$ bits of precision. If piles contain elements near the upper limit ($10^9$) and eating speeds are small, floating-point divisions can theoretically run into precision limitations.
*   Using the integer arithmetic trick `(p + mid - 1) // mid` is exact, fast, and does not require importing the `math` library.

### 2. Generator Expression vs List Comprehension
*   The sum expression `sum((p + mid - 1) // mid for p in piles)` uses a generator expression, which does not allocate an intermediate list in memory (constant space).
*   However, generators in CPython carry a small overhead for creating and iterating the generator frame. If $n$ is small (e.g., $n \le 10^4$), writing `sum([(p + mid - 1) // mid for p in piles])` (which creates a temporary list) or a simple linear `for` loop might run slightly faster, though it uses $\mathcal{O}(n)$ memory.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(n \log M)$ | $M$ is $\max(\text{piles})$. The binary search takes $\mathcal{O}(\log M)$ steps. In each step, we iterate through the $n$ piles to calculate the hours needed. |
| **Space Complexity** | $\mathcal{O}(1)$ | Only a few integer boundaries and accumulators are maintained in memory. |

---

## Common Follow-Up Questions & How to Answer

### Q1: What is the minimum possible value of $h$ allowed by the constraints, and how does it affect the bounds?
*   **The Answer**: The constraints state that $\text{piles.length} \le h$. If $h = \text{piles.length}$, then Koko has exactly $1$ hour per pile. Thus, the eating speed $k$ must be at least the maximum pile size $\max(\text{piles})$ to ensure she finishes each pile within its single hour. The loop immediately exits and returns `max(piles)`.

### Q2: How can we optimize this if $h$ is extremely large (e.g., $h \ge \sum \text{piles}$)?
*   **The Answer**: If $h \ge \sum \text{piles}$, Koko can eat at the minimum speed of $1$ banana/hour and still finish. We can add an early-return check:
    ```python
    if h >= sum(piles):
        return 1
    ```
    This avoids running the binary search entirely for large values of $h$.

---

## Pro-Tip: How to Impress the Interviewer

*   **Explain the Strict Upper Bound**: Clearly explain why the upper bound `right` is `max(piles)` rather than $\sum \text{piles}$ or $10^9$. Because Koko cannot eat from two different piles in the same hour, eating at any speed greater than `max(piles)` does not save any hours—it still takes exactly $1$ hour per pile. This constraint bounds the search space naturally to $\max(\text{piles})$.
*   **Avoid CPU Division Delays**: Explain that division `/` and modulo `%` operations are the most expensive arithmetic instructions on modern CPU architectures (often taking 10–40 clock cycles compared to 1 cycle for addition/subtraction). Minimizing divisions or using compiler-friendly integer ceiling tricks showcases low-level system efficiency mindset.
