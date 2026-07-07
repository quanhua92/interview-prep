# Number of Boomerangs

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / Low-Level Developer
- **Source**: LeetCode 447, Glassdoor

---

## Question Description

You are given $n$ points in the plane that are all **distinct**, where `points[i] = [xi, yi]`. A **boomerang** is a tuple of points `(i, j, k)` such that the distance between `i` and `j` equals the distance between `i` and `k` (the **order of the tuple matters**).

Return the number of boomerangs.

### Examples

*   **Input**: `points = [[0,0],[1,0],[2,0]]`
    *   **Output**: `2`
    *   **Explanation**: The two boomerangs are `[[1,0],[0,0],[2,0]]` and `[[1,0],[2,0],[0,0]]`. (Point `[1,0]` is the pivot).

*   **Input**: `points = [[1,1],[2,2],[3,3]]`
    *   **Output**: `2`

*   **Input**: `points = [[1,1]]`
    *   **Output**: `0`

### Constraints
*   $n == \text{points.length}$
*   $1 \le n \le 500$
*   $\text{points}[i].length == 2$
*   $-10^4 \le x_i, y_i \le 10^4$
*   All the points are **unique**.

---

## Detailed Solution (C++)

A boomerang is determined by a **pivot** point `i` and two other points `j` and `k` that are equidistant from `i`.
1.  For each point `i` in the dataset, treat it as the pivot.
2.  Calculate the squared distance from `i` to all other points `j`.
3.  Store the frequency of each squared distance in a hash map: `std::unordered_map<int, int>`.
4.  For any squared distance $d$ that appears $c$ times, the number of ways to pick two distinct points $j$ and $k$ is the permutation of 2 items chosen from $c$, which is $c \times (c - 1)$.
5.  Sum these values across all distances and all pivots.

### Standard C++ Production Code

```cpp
#include <vector>
#include <unordered_map>

class Solution {
public:
    int numberOfBoomerangs(const std::vector<std::vector<int>>& points) {
        int total_boomerangs = 0;
        int n = points.size();
        
        // We reuse the hash map to avoid repeated allocations in the outer loop
        std::unordered_map<int, int> dist_count;
        
        for (int i = 0; i < n; ++i) {
            dist_count.clear();
            // Pre-reserve capacity to minimize rehashing overhead
            dist_count.reserve(n);
            
            for (int j = 0; j < n; ++j) {
                if (i == j) continue;
                
                int dx = points[i][0] - points[j][0];
                int dy = points[i][1] - points[j][1];
                int dist_sq = dx * dx + dy * dy;
                
                dist_count[dist_sq]++;
            }
            
            for (const auto& pair : dist_count) {
                int count = pair.second;
                if (count > 1) {
                    total_boomerangs += count * (count - 1);
                }
            }
        }
        
        return total_boomerangs;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

```python
from collections import defaultdict
from typing import List

class Solution:
    def numberOfBoomerangs(self, points: List[List[int]]) -> int:
        """
        Calculates the number of boomerangs in O(N^2) time.
        """
        total_boomerangs = 0
        
        for p1 in points:
            # Hash map to count occurrences of each squared distance from pivot p1
            dist_count = defaultdict(int)
            
            for p2 in points:
                # Square distance formula (no square root to preserve integer precision)
                dx = p1[0] - p2[0]
                dy = p1[1] - p2[1]
                dist_sq = dx * dx + dy * dy
                dist_count[dist_sq] += 1
                
            for count in dist_count.values():
                total_boomerangs += count * (count - 1)
                
        return total_boomerangs
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Hash Map vs. Sorting-based Grouping
*   **Hash Map approach (as shown above)**: Runs in $\mathcal{O}(N^2)$ time and uses $\mathcal{O}(N)$ memory. Since $N \le 500$, this is highly efficient.
*   **Sorting-based approach**: We can compute all squared distances for a pivot, sort them, and count consecutive equal values. This takes $\mathcal{O}(N^2 \log N)$ time and $\mathcal{O}(N)$ memory. While mathematically slower, sorting is implemented in C (Timsort) and can sometimes outperform hash map insertion overhead in Python for very small inputs.

### 2. Hash Collision Overhead
*   Python's dictionary uses open addressing. When collision rates are high, lookup performance degrades. However, because our keys are unique squared distances, hash collision rates remain low.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(N^2)$ | We iterate through all $N$ points, and for each point, we compute the distance to the other $N - 1$ points. |
| **Space Complexity** | $\mathcal{O}(N)$ | The hash map stores at most $N$ distinct distances for each pivot. |

---

## Common Follow-Up Questions & How to Answer

### Q1: Why do we use squared Euclidean distance instead of the actual Euclidean distance?
*   **Answer**: Using actual Euclidean distance requires calculating the square root ($\sqrt{dx^2 + dy^2}$). 
    1.  **Precision**: Floating-point numbers have limited precision, which can cause points at mathematically equal distances to have slightly different floating-point values (e.g. `2.0000000000000004` vs `1.9999999999999998`), leading to hash map key mismatches.
    2.  **Performance**: Square root (`std::sqrt` or `math.sqrt`) is a computationally expensive CPU operation. Skipping it yields a significant speedup.

### Q2: What if the order of the points in the boomerang did not matter?
*   **Answer**: A boomerang is defined as an ordered tuple `(i, j, k)`. If the order of the outer endpoints `j` and `k` did not matter (i.e. `(i, j, k)` is equivalent to `(i, k, j)`), we would choose 2 elements from $c$ combinations without order.
    *   Instead of $c \times (c - 1)$, the contribution of each distance cluster would be $\frac{c \times (c - 1)}{2}$.

---

## Pro-Tip: How to Impress the Interviewer

*   **Demonstrate Integer Overflow Safety**: Walk the interviewer through the maximum possible value of `dx * dx + dy * dy`. Given that coordinates are between $-10^4$ and $10^4$, the maximum delta is $2 \cdot 10^4$. The maximum squared distance is:
    $$(2 \cdot 10^4)^2 + (2 \cdot 10^4)^2 = 8 \cdot 10^8$$
    Since standard 32-bit signed integers in C++ go up to $2.14 \times 10^9$, this calculation is guaranteed to be safe from integer overflow. Highlighting this analysis proves that you write system-safe code.
*   **Optimize Map Re-allocations**: Mention that clearing and reserving capacity in the C++ `std::unordered_map` (e.g., `dist_count.clear()` and `dist_count.reserve(n)`) avoids allocating new nodes on every iteration of the outer loop, which saves critical CPU cycles in hot loops.
