# Heaters

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / Algorithm Engineer
- **Source**: LeetCode 475, Glassdoor
- **Flashcards**: [Two Pointers deck](../../flash_cards/coding/two_pointers.md)

---

## Question Description

Winter is coming! During the contest, your first job is to design a standard heater with a fixed warm radius to warm all the houses.

Every house can be warmed, as long as the house is within the heater's warm radius range.

Given the positions of `houses` and `heaters` on a horizontal line, return *the minimum radius standard of heaters so that those heaters could cover all houses*.

**Notice** that all the heaters follow your radius standard, and the warm radius will be the same.

### Examples

*   **Input**: `houses = [1,2,3]`, `heaters = [2]`
    *   **Output**: `1`
    *   **Explanation**: The only heater is at position 2. If we use a warm radius of 1, all houses ([1, 2, 3]) will be covered.
*   **Input**: `houses = [1,2,3,4]`, `heaters = [1,4]`
    *   **Output**: `1`
    *   **Explanation**: The two heaters are at positions 1 and 4. A radius of 1 is sufficient to cover house 2 (via heater 1) and house 3 (via heater 4).
*   **Input**: `houses = [1,5]`, `heaters = [2]`
    *   **Output**: `3`
    *   **Explanation**: The heater is at position 2. The furthest house is at position 5. The minimum radius needed is $|5 - 2| = 3$.

### Constraints
*   $1 \le \text{houses.length}, \text{heaters.length} \le 3 \times 10^4$
*   $1 \le \text{houses}[i], \text{heaters}[i] \le 10^9$

---

## Detailed Solution (C++)

To solve this problem efficiently:
1. **Sort both arrays**: First, sort both `houses` and `heaters` in non-decreasing order. Sorting enables a linear-time two-pointer sweep.
2. **Two-Pointer Scan**: Use index `i` to iterate through the houses, and index `j` to track the heaters.
3. For each house at `houses[i]`, we find the closest heater by advancing `j` to `j + 1` if:
   $$|houses[i] - heaters[j]| \ge |houses[i] - heaters[j + 1]|$$
   This condition checks if moving to the next heater gives a distance that is smaller than or equal to the current one.
4. Calculate the distance between the house and its closest heater: `abs(houses[i] - heaters[j])`.
5. The required warm radius is the maximum of these minimum distances over all houses.

### Standard C++ Production Code

```cpp
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstddef>

class Solution {
public:
    int findRadius(std::vector<int>& houses, std::vector<int>& heaters) {
        // Sort both collections to enable sequential two-pointer scan
        std::sort(houses.begin(), houses.end());
        std::sort(heaters.begin(), heaters.end());

        int min_radius = 0;
        size_t j = 0;
        const size_t num_heaters = heaters.size();

        for (int house : houses) {
            // Advance the heater pointer if the next heater is closer to (or equally close to) the house
            while (j + 1 < num_heaters && 
                   std::abs(house - heaters[j]) >= std::abs(house - heaters[j + 1])) {
                j++;
            }
            // The required radius is the maximum of the minimum distance for each house
            min_radius = std::max(min_radius, std::abs(house - heaters[j]));
        }

        return min_radius;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the type-hinted Python implementation, optimizing pointer movement to achieve linear scan performance after sorting.

```python
from typing import List

class Solution:
    def findRadius(self, houses: List[int], heaters: List[int]) -> int:
        """
        Calculates the minimum warm radius of heaters to cover all houses.
        
        Time Complexity: O(M log M + N log N) where M = len(houses), N = len(heaters)
        Space Complexity: O(1) auxiliary space (excluding sorting memory)
        """
        houses.sort()
        heaters.sort()

        min_radius = 0
        j = 0
        num_heaters = len(heaters)

        for house in houses:
            # Slide heater index forward if the next heater is closer to the current house
            while j + 1 < num_heaters and abs(house - heaters[j]) >= abs(house - heaters[j + 1]):
                j += 1
            
            # Record the distance to the closest heater and update min_radius
            distance = abs(house - heaters[j])
            if distance > min_radius:
                min_radius = distance

        return min_radius
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. In-place Sorting vs. Copying
* We perform `houses.sort()` and `heaters.sort()` in-place to avoid the allocation overhead of creating new list objects.
* If modifying the inputs is not allowed by the API design, we would have to copy them first, which increases space complexity to $\mathcal{O}(m + n)$.

### 2. Tight Loop Optimization
* Inside the `while` loop, Python evaluates `abs(house - heaters[j])` and `abs(house - heaters[j + 1])`. In Python, arithmetic operations and function calls have high relative overhead.
* If optimization is critical, we can cache values or pre-calculate differences, but the two-pointer approach keeps the overall loop count bounded by $m + n$, ensuring high efficiency.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(m \log m + n \log n)$ | Sorting `houses` takes $\mathcal{O}(m \log m)$ and sorting `heaters` takes $\mathcal{O}(n \log n)$. The two-pointer sweep takes $\mathcal{O}(m + n)$ time. |
| **Space Complexity** | $\mathcal{O}(1)$ auxiliary | The algorithm uses a few index variables. Sorting space depends on the language (up to $\mathcal{O}(n)$ in Python's Timsort). |

---

## Common Follow-Up Questions & How to Answer

### Q1: Can we solve this problem using Binary Search?
* **Answer**: Yes. Instead of sorting `houses`, we only sort `heaters` ($\mathcal{O}(n \log n)$).
* For each house, we binary search (using `std::lower_bound` in C++ or `bisect_left` in Python) in `heaters` to find the heater closest to it. Specifically:
  1. Find the first heater index `idx` where `heaters[idx] >= house`.
  2. The closest heater will be either `heaters[idx]` (if valid) or `heaters[idx - 1]` (if valid).
  3. Update `min_radius` with the minimum of these two distances.
* **Time Complexity**: $\mathcal{O}(n \log n + m \log n)$.
* **Comparison**: This is better if $m$ is very small compared to $n$ (so sorting houses is avoided), or if the houses array cannot be sorted.

### Q2: What if we can place a limited number of heaters anywhere to minimize the radius?
* **Answer**: This is a different problem (related to LeetCode 410 / Split Array Largest Sum). We would binary search over the *radius* itself. 
* The search space for radius ranges from $0$ to $\text{maxPos} - \text{minPos}$. For a mid radius, we use a greedy pass to see if we can cover all houses with at most $k$ heaters.

---

## Pro-Tip: How to Impress the Interviewer

* **Propose the Hybrid Decision Boundary**:
  * Explain the trade-off: The two-pointer approach has a time complexity of $\mathcal{O}(m \log m + n \log n)$, whereas the binary search approach has $\mathcal{O}(n \log n + m \log n)$.
  * If $m \ll n$, binary search is clearly superior. If both are large, the two-pointer approach is superior due to sequential CPU cache access (cache locality).
* **Discuss Cache Line Prefetching**:
  * Two pointers traverse memory sequentially. This allows CPU prefetch units to load the next lines of the array into the cache hierarchy before the program requests them, minimizing pipeline stalls.
* **Safeguard Integer subtraction in C++**:
  * Remind the interviewer that if coordinates could be arbitrary unsigned integers, subtraction `house - heaters[j]` could underflow. Using signed types or careful checks prevents wrapping errors.
