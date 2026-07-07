# Perfect Rectangle

- **Category**: Coding
- **Difficulty**: Hard
- **Target Role**: Software Engineer / AI Systems Architect
- **Source**: LeetCode 391, Glassdoor

---

## Question Description

Given an array `rectangles` where `rectangles[i] = [xi, yi, ai, bi]` represents an axis-aligned rectangle. The bottom-left point of the rectangle is `(xi, yi)` and the top-right point of it is `(ai, bi)`.

Return `true` if all the rectangles together form an **exact cover** of a rectangular region (i.e., no gaps, no overlaps).

### Examples

*   **Input**: `rectangles = [[1,1,3,3],[3,1,4,2],[3,2,4,4],[1,3,2,4],[2,3,3,4]]`
    *   **Output**: `true`
    *   **Explanation**: All 5 rectangles together form an exact cover of a rectangular region.

*   **Input**: `rectangles = [[1,1,2,3],[1,3,2,4],[3,1,4,2],[3,2,4,4]]`
    *   **Output**: `false`
    *   **Explanation**: Because there is a gap between the two rectangular regions.

*   **Input**: `rectangles = [[1,1,3,3],[3,1,4,2],[1,3,2,4],[2,2,4,4]]`
    *   **Output**: `false`
    *   **Explanation**: Because two of the rectangles overlap with each other.

---

## Detailed Solution (C++)

To verify if the set of sub-rectangles forms a perfect cover:
1.  **Area Invariant**: The sum of the areas of all sub-rectangles must equal the area of the overall bounding box.
    $$\text{Total Area} = (x_{\max} - x_{\min}) \times (y_{\max} - y_{\min})$$
2.  **Corner Invariant**: In an exact cover, any internal corner must be shared by exactly 2 or 4 sub-rectangles. Any boundary corner (excluding the 4 main bounding box corners) must be shared by exactly 2 sub-rectangles.
    *   If we track the corners and toggle their presence in a set (insert if absent, remove if present), all even-occurring corners will cancel out.
    *   At the end of processing all rectangles, the set must contain **exactly** the four corners of the overall bounding box:
        $$\{(x_{\min}, y_{\min}), (x_{\min}, y_{\max}), (x_{\max}, y_{\min}), (x_{\max}, y_{\max})\}$$

### Standard C++ Production Code

```cpp
#include <vector>
#include <set>
#include <algorithm>
#include <utility>
#include <limits>

class Solution {
public:
    bool isRectangleCover(const std::vector<std::vector<int>>& rectangles) {
        std::set<std::pair<long long, long long>> corners;
        long long total_area = 0;
        
        long long min_x = std::numeric_limits<long long>::max();
        long long min_y = std::numeric_limits<long long>::max();
        long long max_x = std::numeric_limits<long long>::min();
        long long max_y = std::numeric_limits<long long>::min();

        for (const auto& rect : rectangles) {
            long long x1 = rect[0], y1 = rect[1];
            long long x2 = rect[2], y2 = rect[3];

            // Update bounding box boundaries
            min_x = std::min(min_x, x1);
            min_y = std::min(min_y, y1);
            max_x = std::max(max_x, x2);
            max_y = std::max(max_y, y2);

            // Accumulate areas safely using 64-bit integers to prevent overflow
            total_area += (x2 - x1) * (y2 - y1);

            // The 4 corners of the current rectangle
            std::pair<long long, long long> rect_corners[] = {
                {x1, y1}, {x1, y2}, {x2, y1}, {x2, y2}
            };

            // Toggle corner presence in the set
            for (const auto& point : rect_corners) {
                auto it = corners.find(point);
                if (it != corners.end()) {
                    corners.erase(it);
                } else {
                    corners.insert(point);
                }
            }
        }

        // Exact cover requires exactly the 4 outermost corners remaining
        if (corners.size() != 4) {
            return false;
        }

        std::set<std::pair<long long, long long>> expected_corners = {
            {min_x, min_y}, {min_x, max_y}, {max_x, min_y}, {max_x, max_y}
        };

        if (corners != expected_corners) {
            return false;
        }

        // Verify the sum of parts matches the whole area
        return total_area == (max_x - min_x) * (max_y - min_y);
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

```python
from typing import List

class Solution:
    def isRectangleCover(self, rectangles: List[List[int]]) -> bool:
        """
        Determines if all rectangles together form an exact cover of a rectangular region.
        
        Time Complexity: O(N)
        Space Complexity: O(N)
        """
        corners: set[tuple[int, int]] = set()
        total_area = 0
        
        min_x = min_y = float('inf')
        max_x = max_y = float('-inf')

        for x1, y1, x2, y2 in rectangles:
            min_x = min(min_x, x1)
            min_y = min(min_y, y1)
            max_x = max(max_x, x2)
            max_y = max(max_y, y2)
            
            # Accumulate sub-rectangle area
            total_area += (x2 - x1) * (y2 - y1)
            
            # Toggle corners
            for corner in [(x1, y1), (x1, y2), (x2, y1), (x2, y2)]:
                if corner in corners:
                    corners.remove(corner)
                else:
                    corners.add(corner)

        # There must be exactly 4 odd-count corners in the set
        if len(corners) != 4:
            return False

        # They must match the bounding box corners
        expected_corners = {
            (min_x, min_y),
            (min_x, max_y),
            (max_x, min_y),
            (max_x, max_y)
        }

        if corners != expected_corners:
            return False

        # Area validation
        return total_area == (max_x - min_x) * (max_y - min_y)
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Hashability of Tuples vs Lists
*   In Python, lists are mutable and therefore **unhashable**, so they cannot be stored in a `set`.
*   We represent each corner coordinate as a 2-tuple (e.g., `(x1, y1)`), which is immutable and hashable, allowing $\mathcal{O}(1)$ average-time checks and insertions into the `corners` set.

### 2. Floating-Point Infinities for Min/Max Initialization
*   Python's `float('inf')` and `float('-inf')` provide a clean way to initialize boundaries without relying on hardcoded constants like $2^{31}-1$.
*   Since comparisons between floats and integers work seamlessly in Python (`min(float('inf'), integer)` correctly returns the integer), this is a safe, readable pattern.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(n)$ | Standard set operations (addition/deletion) run in $\mathcal{O}(1)$ average time per corner. (In C++, `std::set` takes $\mathcal{O}(n \log n)$; `std::unordered_set` can achieve $\mathcal{O}(n)$). |
| **Space Complexity** | $\mathcal{O}(n)$ | In the worst case, the set stores all $4n$ corners of the input rectangles. |

---

## Common Follow-Up Questions & How to Answer

### Q1: Can you solve this using a Sweep-Line algorithm?
*   **Answer**: Yes. Sweep-line is the standard geometric way to solve overlaps. 
    1.  Create events for the vertical boundaries of each rectangle (e.g., entering at $x_1$, leaving at $x_2$).
    2.  Sort these events by $x$.
    3.  Iterate through $x$ and maintain the active $y$-intervals in a Segment Tree or interval tree.
    4.  Verify that entering intervals do not overlap with existing active intervals, and that the union of intervals is contiguous.
    *   **Pros**: Generalizes to finding the union of overlapping shapes.
    *   **Cons**: Higher complexity ($\mathcal{O}(n \log n)$ time and complex implementation).

### Q2: How does this generalize to 3D box covers?
*   **Answer**: In 3D, the area constraint becomes a volume constraint: $\text{Total Volume} = \sum \text{Volumes}$.
    *   The corners constraint extends to the vertices of 3D boxes. A perfect cover in 3D would result in exactly 8 outermost corners remaining in our vertex set after parity cancellation.

---

## Pro-Tip: How to Impress the Interviewer

*   **Proactively Avoid Integer Overflow**: Explicitly mention that multiplying coordinates like $(x_2 - x_1) \times (y_2 - y_1)$ can easily overflow a 32-bit integer in C++ if coordinates are large (e.g. $10^5$). Show production hygiene by casting to `long long` before computing area.
*   **Explain the Topological Parity Invariant**: Rather than just reciting the code, explain *why* the corner parity cancellation works: internal corners are shared by an even number of rectangles ($2$ or $4$), which cancel out, while outermost corners are shared by exactly $1$ rectangle, surviving the parity check.
