# Minimum Number of Arrows to Burst Balloons

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / Low-Level Developer
- **Source**: LeetCode 452, Glassdoor
- **Flashcards**: [Greedy deck](../../flash_cards/coding/greedy.md)

---

## Question Description

There are some spherical balloons taped onto a flat wall that represents the XY-plane. The balloons are represented as a 2D integer array `points` where `points[i] = [xstart, xend]` denotes a balloon whose horizontal diameter stretches between `xstart` and `xend`. You do not know the exact y-coordinates of the balloons.

Arrows can be shot up directly vertically (in the positive y-direction) from different points along the x-axis. A balloon with `xstart` and `xend` is burst by an arrow shot at $x$ if $x_{start} \le x \le x_{end}$. There is no limit to the number of arrows that can be shot. A shot arrow keeps traveling up infinitely, bursting any balloons in its path.

Given the array `points`, return the *minimum number of arrows* that must be shot to burst all balloons.

### Examples
*   **Input**: `points = [[10,16],[2,8],[1,6],[7,12]]`
    *   **Output**: `2`
    *   **Explanation**: The balloons can be burst by 2 arrows:
        *   Shoot an arrow at $x = 6$, bursting the balloons `[2,8]` and `[1,6]`.
        *   Shoot an arrow at $x = 11$, bursting the balloons `[10,16]` and `[7,12]`.
*   **Input**: `points = [[1,2],[3,4],[5,6],[7,8]]`
    *   **Output**: `4`
    *   **Explanation**: One arrow needs to be shot for each balloon for a total of 4 arrows.
*   **Input**: `points = [[1,2],[2,3],[3,4],[4,5]]`
    *   **Output**: `2`
    *   **Explanation**: The balloons can be burst by 2 arrows:
        *   Shoot an arrow at $x = 2$, bursting the balloons `[1,2]` and `[2,3]`.
        *   Shoot an arrow at $x = 4$, bursting the balloons `[3,4]` and `[4,5]`.

---

## Detailed Solution (C++)

This is a classic **Interval Scheduling / Greedy Algorithm** problem:
1. If we sort the intervals (balloons) by their **end coordinates**, we can always greedily place an arrow at the end coordinate of the first balloon.
2. Placing the arrow at the end coordinate $E$ of the balloon maximizes the chance of hitting subsequent balloons because any balloon starting at or before $E$ must overlap with this arrow's path.
3. For each subsequent balloon, if its start coordinate is greater than our current arrow's position, we need a new arrow. We update the arrow's position to the end coordinate of this new balloon.
4. Otherwise, the balloon is burst by the existing arrow, and we continue.

### Standard C++ Production Code

```cpp
#include <vector>
#include <algorithm>

class Solution {
public:
    int findMinArrowShots(std::vector<std::vector<int>>& points) {
        if (points.empty()) {
            return 0;
        }

        // Sort balloons by their end coordinate (points[i][1])
        std::sort(points.begin(), points.end(), [](const std::vector<int>& a, const std::vector<int>& b) noexcept {
            return a[1] < b[1];
        });

        int arrows = 1;
        // Using coordinate value directly as the position of the arrow
        int current_end = points[0][1];

        const size_t n = points.size();
        for (size_t i = 1; i < n; ++i) {
            // If the start of the current balloon is greater than the current arrow position,
            // we must shoot a new arrow.
            if (points[i][0] > current_end) {
                arrows++;
                current_end = points[i][1];
            }
        }

        return arrows;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the type-hinted, memory-optimized Python implementation.

```python
from typing import List

class Solution:
    def findMinArrowShots(self, points: List[List[int]]) -> int:
        """
        Calculates the minimum number of arrows to burst all balloons.
        
        Time Complexity: O(N log N)
        Space Complexity: O(1) auxiliary (sorting in Python takes O(N) space for Timsort)
        """
        if not points:
            return 0

        # Sort in-place by the end coordinate to avoid O(N) list copy
        points.sort(key=lambda x: x[1])

        arrows = 1
        current_end = points[0][1]

        # Use an iterator to avoid list slicing points[1:] which allocates O(N) memory
        points_iter = iter(points)
        next(points_iter)  # Skip the first element

        for start, end in points_iter:
            if start > current_end:
                arrows += 1
                current_end = end

        return arrows
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Avoiding Slice Allocation Overhead
*   Using `points[1:]` inside the loop creates a shallow copy of the list, which consumes $\mathcal{O}(N)$ additional memory.
*   By converting the list to an iterator with `iter(points)` and skipping the first element using `next()`, we can iterate through the remaining elements with zero auxiliary memory allocations.

### 2. Timsort Space Complexity
*   Python's built-in `sort()` (and `sorted()`) uses Timsort, which has a worst-case space complexity of $\mathcal{O}(N)$ because it keeps track of runs in temporary arrays. In C++, `std::sort` uses Introsort, which runs in $\mathcal{O}(\log N)$ auxiliary space.

### 3. Comparator Subtraction Overflow Gotcha
*   In some languages, developers write custom sorting comparators using subtraction (e.g., `(a, b) -> a[1] - b[1]`). 
*   This is highly dangerous because coordinates range between $-2^{31}$ and $2^{31}-1$. Subtracting a large positive number from a large negative number will cause **integer overflow**, leading to incorrect sorting or crashes. Always use standard less-than comparisons (`a[1] < b[1]`).

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(n \log n)$ | Dominated by the sorting step. The linear scan takes $\mathcal{O}(n)$ time. |
| **Space Complexity** | $\mathcal{O}(\log n)$ or $\mathcal{O}(n)$ | $\mathcal{O}(\log n)$ auxiliary space in C++ (Introsort stack), $\mathcal{O}(n)$ in Python (Timsort). |

---

## Common Follow-Up Questions & How to Answer

### Q1: What is the difference between this problem and Non-overlapping Intervals (LeetCode 435)?
*   **Answer**: The core logic is identical—both are variants of the **Interval Scheduling Problem**. However, the boundary overlap conditions differ:
    *   In LeetCode 452 (Burst Balloons), intervals that touch at a single point (e.g., `[1, 2]` and `[2, 3]`) are considered **overlapping** (an arrow at $x=2$ bursts both).
    *   In LeetCode 435 (Non-overlapping Intervals), intervals touching at a single point (e.g., `[1, 2]` and `[2, 3]`) are **not** considered overlapping.

### Q2: What if the coordinates are in a 2D plane and we shoot arrows diagonally?
*   **Answer**: If we can shoot arrows along any line $y = mx + c$, the problem becomes equivalent to finding the minimum number of lines that intersect a set of geometric shapes. This is a much harder geometric optimization problem (typically NP-hard depending on constraints).

---

## Pro-Tip: How to Impress the Interviewer

*   **Highlight the Comparator Integer Overflow Risk**: Proactively warn the interviewer about comparator subtraction bugs (`a[1] - b[1]`). Mentioning how to safely sort intervals containing large negative and positive integers demonstrates high attention to code correctness and system safety.
*   **Avoid Slicing in Python**: Pointing out that `points[1:]` allocates a new list and replacing it with an iterator demonstrates a strong grasp of Python's memory management.
*   **In-Place Modification Communication**: Clarify with the interviewer if you are allowed to sort the input array `points` in-place. If modifying the input is forbidden, you must make a copy, which increases the space complexity to $\mathcal{O}(N)$.
