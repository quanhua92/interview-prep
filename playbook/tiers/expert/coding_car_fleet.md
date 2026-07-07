# Car Fleet

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / Low-Level Developer / AI Systems Architect
- **Source**: LeetCode 853, Glassdoor
- **Flashcards**: [Monotonic Stack deck](../../flash_cards/coding/monotonic_stack.md)

---

## Question Description

There are `n` cars at given miles away from the starting mile `0`, traveling to reach the mile `target`.

You are given two integer arrays `position` and `speed`, both of length `n`, where `position[i]` is the starting mile of the $i$-th car and `speed[i]` is the speed of the $i$-th car in miles per hour.

A car cannot pass another car, but it can catch up and then travel next to it at the speed of the slower car. A **car fleet** is a car or cars driving next to each other. The speed of the car fleet is the minimum speed of any car in the fleet.

If a car catches up to a car fleet at the mile target, it will still be considered as part of the car fleet.

Return *the number of car fleets that will arrive at the destination*.

### Examples

*   **Input**: `target = 12`, `position = [10,8,0,5,3]`, `speed = [2,4,1,1,3]`
    *   **Output**: `3`
    *   **Explanation**:
        *   The cars starting at `10` (speed `2`) and `8` (speed `4`) become a fleet, meeting at mile `12`. Arrival time: `(12 - 10) / 2 = 1` hour and `(12 - 8) / 4 = 1` hour.
        *   The car starting at `0` (speed `1`) travels alone. Arrival time: `(12 - 0) / 1 = 12` hours.
        *   The cars starting at `5` (speed `1`) and `3` (speed `3`) become a fleet, meeting at mile `6`. They travel together at speed `1` and arrive at `12` in `7` hours.
        *   In total, we have `3` fleets.
*   **Input**: `target = 10`, `position = [3]`, `speed = [3]`
    *   **Output**: `1`
*   **Input**: `target = 100`, `position = [0,2,4]`, `speed = [4,2,1]`
    *   **Output**: `1`

---

## Detailed Solution (C++)

The core algorithm is based on **sorting** and **greedy state tracking** (which conceptually simplifies a Monotonic Stack):
1. First, we compute the time it takes for each car to reach the destination: `time = (target - position) / speed`.
2. We sort the cars by their starting position in **descending order** (from closest to the target to farthest).
3. We iterate through the sorted list of cars:
   * The first car (closest to the target) will always arrive first or lead the first fleet. Its calculated time is the initial `slowest_time`.
   * For each subsequent car, if its calculated time is **less than or equal to** `slowest_time`, it means this car starts further back but would arrive earlier or at the same time if unobstructed. Since it cannot pass the cars ahead of it, it will collide/join with the fleet ahead. It does not form a new fleet.
   * If its calculated time is **greater than** `slowest_time`, it cannot catch up to the fleet ahead. It must form its own new fleet, and we update `slowest_time` to its calculated time.
4. We increment our fleet count every time a new fleet is formed.

### Standard C++ Production Code

```cpp
#include <vector>
#include <algorithm>
#include <numeric>
#include <cstddef>

class Solution {
public:
    int carFleet(int target, std::vector<int>& position, std::vector<int>& speed) {
        const int n = static_cast<int>(position.size());
        if (n <= 1) {
            return n;
        }

        // Create an index array and sort indices based on position in descending order
        std::vector<int> indices(n);
        std::iota(indices.begin(), indices.end(), 0);
        std::sort(indices.begin(), indices.end(), [&](int a, int b) {
            return position[a] > position[b];
        });

        int fleets = 0;
        double slowest_time = -1.0;

        for (int i = 0; i < n; ++i) {
            int idx = indices[i];
            // Calculate time using double to prevent division truncation
            double time = static_cast<double>(target - position[idx]) / speed[idx];

            // If this car takes longer than the fleet in front of it, it forms a new fleet
            if (time > slowest_time) {
                fleets++;
                slowest_time = time;
            }
        }

        return fleets;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the type-hinted Python implementation. It pairs positions and speeds, sorts them, and iterates to count the fleets.

```python
from typing import List

class Solution:
    def carFleet(self, target: int, position: List[int], speed: List[int]) -> int:
        """
        Calculates the number of car fleets that arrive at the target.
        
        Time Complexity: O(N log N)
        Space Complexity: O(N)
        """
        if not position:
            return 0

        # Pair position and speed, then sort by position in descending order
        cars = sorted(zip(position, speed), key=lambda x: x[0], reverse=True)
        
        fleets = 0
        slowest_time = -1.0

        for pos, spd in cars:
            time = (target - pos) / spd
            
            # If current car takes more time than the slowest car in the fleet ahead,
            # it cannot catch up and forms a new fleet.
            if time > slowest_time:
                fleets += 1
                slowest_time = time

        return fleets
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Float Precision and Division
* Python 3's `/` operator performs float division naturally. However, floating-point numbers can suffer from precision limits. Since target and speed are up to $10^6$, standard floats are more than sufficient.
* Sorting via `zip` is highly optimized in Python as it executes via compiled C routines under the hood.

### 2. Space Optimization
* Sorting `zip(position, speed)` creates a list of tuples, occupying $\mathcal{O}(n)$ auxiliary memory. To conserve memory on massive inputs, sorting indices or using in-place sort on custom objects is preferred.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(n \log n)$ | The time complexity is dominated by sorting the cars by their starting position. The subsequent linear scan takes $\mathcal{O}(n)$ time. |
| **Space Complexity** | $\mathcal{O}(n)$ | Sorting indices or zipping positions and speeds requires $\mathcal{O}(n)$ extra space. |

---

## Common Follow-Up Questions & How to Answer

### Q1: What if we want to know the size of each fleet?
* **Answer**: We can track this by keeping a stack of fleet leaders or sizes. When a car starts a new fleet (i.e. `time > slowest_time`), we push a new fleet with size `1`. If a car joins the existing fleet (`time <= slowest_time`), we increment the size of the top fleet on the stack.

### Q2: What is the relationship between this problem and LeetCode 1776 (Car Fleet II)?
* **Answer**: In Car Fleet II, cars travel infinitely, and we need to output the exact time each car collides with the car ahead of it. This requires a full **Monotonic Stack** to keep track of collision times.
* As we iterate from right to left, we compare the current car's collision time with the car in front of it. If the current car is faster than the one ahead, it will collide. If the collision happens after the car ahead has already collided with its front car, we must pop the stack and evaluate collisions with the next car in front.

---

## Pro-Tip: How to Impress the Interviewer

* **Use Float Division Safely**: Show your awareness of truncation bugs in C++. Doing `(target - position[idx]) / speed[idx]` without casting to `double` performs integer division, which truncates fractional parts and leads to incorrect fleet merges.
* **Demonstrate Stack Reduction**: Point out that although the problem is labeled "stack", we can reduce space complexity by only tracking the `slowest_time` variable because we only care about the front car of the current fleet. This avoids stack allocation.
