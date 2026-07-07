# Random Point in Non-overlapping Rectangles

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / AI Systems Architect
- **Source**: LeetCode 497, Glassdoor

---

## Question Description

You are given an array of non-overlapping axis-aligned rectangles `rects` where `rects[i] = [ai, bi, xi, yi]` indicates that `(ai, bi)` is the bottom-left corner point of the $i$-th rectangle and `(xi, yi)` is the top-right corner point of the $i$-th rectangle. Design an algorithm to pick a random integer point inside the space covered by one of the given rectangles. A point on the perimeter of a rectangle is included in the space covered by the rectangle.

Any integer point inside the space covered by one of the given rectangles should be **equally likely** to be returned.

Note that an integer point is a point that has integer coordinates.

Implement the `Solution` class:
*   `Solution(int[][] rects)` Initializes the object with the given rectangles `rects`.
*   `int[] pick()` Returns a random integer point `[x, y]` from the space covered by the rectangles.

### Examples

*   **Input**:
    `["Solution", "pick", "pick", "pick", "pick", "pick"]`
    `[[[[-2, -2, 1, 1], [2, 2, 4, 6]]], [], [], [], [], []]`
*   **Output**:
    `[null, [1, -2], [1, -1], [-1, -2], [-2, -2], [0, 0]]`
*   **Explanation**:
    ```python
    solution = Solution([[-2, -2, 1, 1], [2, 2, 4, 6]])
    solution.pick() # return [1, -2]
    solution.pick() # return [1, -1]
    solution.pick() # return [-1, -2]
    solution.pick() # return [-2, -2]
    solution.pick() # return [0, 0]
    ```

### Constraints
*   $1 \le \text{rects.length} \le 100$
*   $\text{rects}[i].\text{length} == 4$
*   $-10^9 \le a_i < x_i \le 10^9$
*   $-10^9 \le b_i < y_i \le 10^9$
*   $x_i - a_i \le 2000$
*   $y_i - b_i \le 2000$
*   All the rectangles do not overlap.
*   At most $10^4$ calls will be made to `pick`.

---

## Detailed Solution (C++)

To ensure that each integer point across all rectangles is equally likely to be chosen:
1.  **Calculate Point Count Per Rectangle**:
    Since coordinates represent integer points, the number of points in rectangle $i$ is:
    $$\text{points}_i = (x_2 - x_1 + 1) \times (y_2 - y_1 + 1)$$
2.  **Generate Prefix Sums**:
    We create a prefix sum array `prefix_` where `prefix_[i]` stores the cumulative number of points in rectangles $0$ through $i$. The total number of points is `total_ = prefix_.back()`.
3.  **Binary Search for Rectangle Selection**:
    When calling `pick()`:
    *   We pick a random integer $t$ in the range $[0, \text{total\_} - 1]$.
    *   We use binary search (`std::upper_bound` or standard binary search template) to locate the rectangle corresponding to $t$.
4.  **Uniform Point Generation within Rectangle**:
    Once the rectangle is selected, we independently pick a random $x$ from $[x_1, x_2]$ and a random $y$ from $[y_1, y_2]$ using a uniform random generator.

### Standard C++ Production Code

```cpp
#include <vector>
#include <random>
#include <algorithm>

class Solution {
private:
    std::vector<std::vector<int>> rects;
    std::vector<int> prefix;
    int total_points;
    
    // Modern C++ Random Engine
    std::mt19937 gen;

public:
    Solution(const std::vector<std::vector<int>>& rects) : rects(rects), total_points(0), gen(std::random_device{}()) {
        prefix.reserve(rects.size());
        for (const auto& r : rects) {
            // Rectangles are axis-aligned, calculating the number of integer points on/in it
            int points = (r[2] - r[0] + 1) * (r[3] - r[1] + 1);
            total_points += points;
            prefix.push_back(total_points);
        }
    }

    std::vector<int> pick() {
        // Uniform distribution over the total point space
        std::uniform_int_distribution<int> dist(0, total_points - 1);
        int t = dist(gen);

        // Binary search to find the rectangle index
        // equivalent to finding first index i where prefix[i] > t
        auto it = std::upper_bound(prefix.begin(), prefix.end(), t);
        int idx = std::distance(prefix.begin(), it);

        const auto& r = rects[idx];
        
        // Pick a uniform random point within the chosen rectangle
        std::uniform_int_distribution<int> dist_x(r[0], r[2]);
        std::uniform_int_distribution<int> dist_y(r[1], r[3]);

        return {dist_x(gen), dist_y(gen)};
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the type-hinted Python implementation using `random.randint` and `bisect` for fast prefix binary searches.

```python
import random
import bisect
from typing import List

class Solution:
    def __init__(self, rects: List[List[int]]):
        """
        Initializes prefix sum of point counts for each rectangle.
        """
        self.rects = rects
        self.prefix = []
        total = 0
        for x1, y1, x2, y2 in rects:
            points = (x2 - x1 + 1) * (y2 - y1 + 1)
            total += points
            self.prefix.append(total)
        self.total = total

    def pick(self) -> List[int]:
        """
        Selects a random rectangle based on point weight, then chooses a point within.
        """
        # Generate a random integer in [1, total]
        t = random.randint(1, self.total)
        
        # Binary search the selected rectangle index
        idx = bisect.bisect_left(self.prefix, t)
        
        x1, y1, x2, y2 = self.rects[idx]
        
        # Pick uniformly from the chosen grid
        return [random.randint(x1, x2), random.randint(y1, y2)]
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Choice of Randomness Function: `randint` vs `randrange`
* `random.randint(a, b)` returns a random integer $N$ such that $a \le N \le b$ (both endpoints inclusive). This matches our integer coordinate requirements.
* `random.randrange(a, b)` is exclusive of the upper limit $b$. Make sure you use `randint` or set `randrange(a, b + 1)` correctly to include the boundaries.

### 2. Prefix Search using `bisect_left` vs `bisect_right`
* Since `t` is generated in range `[1, total]`, we want to find the first index where `prefix[idx] >= t`. This is perfectly handled by `bisect_left`. If `t` was in `[0, total - 1]`, we would use `bisect_right(prefix, t)`.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity (Constructor)** | $\mathcal{O}(n)$ | Computes the area and prefix sum for all $n$ rectangles. |
| **Time Complexity (pick)** | $\mathcal{O}(\log n)$ | Binary searches the rectangle index, and runs two constant-time random coordinate generation calls. |
| **Space Complexity** | $\mathcal{O}(n)$ | Stores the prefix sums and coordinates of $n$ rectangles. |

---

## Common Follow-Up Questions & How to Answer

### Q1: What if the rectangles overlap?
* **Answer**: If rectangles overlap, simple prefix sum weights would count the overlapping areas multiple times, leading to non-uniform selection probabilities.
  * **Solution**: We can use **disjoint set / segment tree** to segment the rectangles into non-overlapping smaller rectangles first, then apply the same algorithm. Alternatively, we can use **Rejection Sampling**: pick a point from the bounding box of all rectangles, and check if it lies in any rectangle; if not, retry. However, this could have high retry rates if the density of rectangles is low.

### Q2: What if we can't store the rectangles in memory (Streaming / Reservoir Sampling)?
* **Answer**: If we receive rectangles in a data stream, we can use **Reservoir Sampling** to select the rectangle:
  * Maintain the current `total_points` seen so far.
  * For each new rectangle with $A$ points, we select it as our candidate with probability $\frac{A}{\text{total\_points}}$.
  * Once the stream ends, we sample a point from the selected candidate rectangle.

---

## Pro-Tip: How to Impress the Interviewer

* **Use Modern C++ Random Library**: Avoid using `rand() % total_` in C++ as it suffers from **modulo bias** (non-uniform distribution) and limited range (typically $32767$ in `RAND_MAX`). Instead, use `std::mt19937` with `std::uniform_int_distribution` which executes faster and provides high-quality pseudorandomness suitable for simulations.
* **Point out Coordinate Boundary Logic**: Highlight the $+1$ offset in `(x2 - x1 + 1)`. Emphasize that coordinate points are discrete (1D grid size is inclusive of both boundary lines), unlike standard geometric area calculations.
