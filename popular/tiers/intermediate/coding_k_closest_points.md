# K Closest Points to Origin

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / Low-Level Developer / AI Systems Architect
- **Source**: LeetCode 973, Glassdoor
- **Flashcards**: [Top K Elements deck](../../flash_cards/coding/top_k_elements.md)

---

## Question Description

Given an array of `points` where `points[i] = [xi, yi]` represents a point on the **X-Y** plane and an integer `k`, return the `k` closest points to the origin `(0, 0)`.

The distance between two points on the X-Y plane is the Euclidean distance:
$$\sqrt{(x_1 - x_2)^2 + (y_1 - y_2)^2}$$

You may return the answer in **any order**. The answer is guaranteed to be unique (except for the order of the points).

### Examples
*   **Input**: `points = [[1,3],[-2,2]]`, `k = 1`
    *   **Output**: `[[-2,2]]`
    *   **Explanation**:
        *   The distance between $(1, 3)$ and the origin is $\sqrt{1^2 + 3^2} = \sqrt{10}$.
        *   The distance between $(-2, 2)$ and the origin is $\sqrt{(-2)^2 + 2^2} = \sqrt{8}$.
        *   Since $\sqrt{8} < \sqrt{10}$, $(-2, 2)$ is closer to the origin.
        *   We want the closest $k=1$ points, so we return `[[-2,2]]`.
*   **Input**: `points = [[3,3],[5,-1],[-2,4]]`, `k = 2`
    *   **Output**: `[[3,3],[-2,4]]` (or `[[-2,4],[3,3]]`)

---

## Detailed Solution (C++)

To find the $k$ closest points, we can use two primary approaches:
1. **Max-Heap of size $k$ ($\mathcal{O}(n \log k)$)**: Push elements into a max-heap of size $k$. Once size exceeds $k$, pop the furthest element. The remaining elements are the $k$ closest.
2. **Quickselect / Introselect ($\mathcal{O}(n)$ average)**: Since we do not need to sort the output, we can partition the array of points using Quickselect. In C++, `std::nth_element` partitions the vector in-place such that the first $k$ elements are the closest to the origin. This runs in $\mathcal{O}(n)$ time.

To avoid slow floating-point square root operations, we compare the **squared distance** $x^2 + y^2$.

### Standard C++ Production Code

#### Optimal Approach: Introselect ($\mathcal{O}(n)$ Time, $\mathcal{O}(1)$ Space)
```cpp
#include <vector>
#include <algorithm>

class Solution {
public:
    std::vector<std::vector<int>> kClosest(std::vector<std::vector<int>>& points, int k) {
        // Use std::nth_element to partition the top k closest elements to the front
        std::nth_element(points.begin(), points.begin() + k - 1, points.end(), 
            [](const std::vector<int>& a, const std::vector<int>& b) {
                return (a[0] * a[0] + a[1] * a[1]) < (b[0] * b[0] + b[1] * b[1]);
            }
        );
        
        // Resize points vector to only return the first k elements
        points.resize(k);
        return points;
    }
};
```

#### Alternative Approach: Max-Heap ($\mathcal{O}(n \log k)$ Time, $\mathcal{O}(k)$ Space)
```cpp
#include <vector>
#include <queue>
#include <utility>

class SolutionHeap {
public:
    std::vector<std::vector<int>> kClosest(std::vector<std::vector<int>>& points, int k) {
        // Max-heap stores pair of <squared_distance, point_index>
        std::priority_queue<std::pair<int, int>> maxHeap;
        for (size_t i = 0; i < points.size(); ++i) {
            int dist = points[i][0] * points[i][0] + points[i][1] * points[i][1];
            maxHeap.push({dist, static_cast<int>(i)});
            if (maxHeap.size() > static_cast<size_t>(k)) {
                maxHeap.pop();
            }
        }
        
        std::vector<std::vector<int>> result;
        result.reserve(k);
        while (!maxHeap.empty()) {
            result.push_back(points[maxHeap.top().second]);
            maxHeap.pop();
        }
        return result;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code (Max-Heap)

```python
import heapq
from typing import List

class Solution:
    def kClosest(self, points: List[List[int]], k: int) -> List[List[int]]:
        """
        Finds the k closest points using a Max-Heap of size k.
        
        Time Complexity: O(n log k)
        Space Complexity: O(k)
        """
        heap = []
        
        for p in points:
            # We negate the distance to turn heapq (Min-Heap) into a Max-Heap
            dist = -(p[0]*p[0] + p[1]*p[1])
            heapq.heappush(heap, (dist, p))
            
            # If heap size exceeds k, pop the largest (furthest) distance
            if len(heap) > k:
                heapq.heappop(heap)
                
        # Return only the points from the heap
        return [point for (_, point) in heap]
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Simulating Max-Heap with Negation
*   Because Python's `heapq` is a Min-Heap, we negate the squared distance (`-dist`) so that the furthest point (largest absolute distance) has the smallest value in the heap. Popping from the heap thus removes the furthest point, keeping the closest points.

### 2. Built-in `heapq.nsmallest`
*   Python offers a `heapq.nsmallest(k, points, key=lambda p: p[0]**2 + p[1]**2)` utility. It is implemented in C and runs very efficiently. However, in an interview, implementing the heap boundary check manually demonstrates an understanding of heap invariants.

---

## Complexity Analysis

### Quickselect (C++):
| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(n)$ average | Partitioning takes $\mathcal{O}(n)$ at each step, and we recurse into a partition of size $n/2$ on average, giving $\mathcal{O}(n)$ average time. |
| **Space Complexity** | $\mathcal{O}(1)$ | Done in-place without auxiliary containers. |

### Max-Heap (Python):
| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(n \log k)$ | Scanning all $n$ points and performing heap push/pop operations of size $k$ takes $\mathcal{O}(n \log k)$ time. |
| **Space Complexity** | $\mathcal{O}(k)$ | Auxiliary space required to store $k$ elements in the heap. |

---

## Common Follow-Up Questions & How to Answer

### Q1: Why do we avoid the `sqrt` function?
*   **Answer**: The square root function is monotonic, meaning if $a < b$, then $\sqrt{a} < \sqrt{b}$. Thus, comparing $x^2 + y^2$ preserves the relative distance ordering. Computing `sqrt` requires floating-point operations which are slower, susceptible to precision/rounding issues, and unnecessary since coordinates are integers.

### Q2: What if we have a constant stream of new points?
*   **Answer**: If new points are generated continuously, Quickselect is unusable because it is an offline algorithm requiring all data in memory. In this scenario, we must use the **Max-Heap** approach, storing the current $k$ closest points in a heap and comparing new points against the heap's top.

---

## Pro-Tip: How to Impress the Interviewer

*   **Spatial Indexing (K-D Tree)**: Mention that if we need to query the $k$ closest points multiple times on a static or slowly changing set of points, we should pre-process the points into a **k-d tree** (a space-partitioning BST for points in $K$ dimensions). This allows nearest-neighbor queries to run in $\mathcal{O}(\log n)$ time.
*   **Cache Friendliness of Flat Layouts**: Point out that points stored as a `std::vector<std::vector<int>>` involve two levels of pointers, which reduces cache efficiency due to memory indirection. Storing coordinates in a flat array `std::vector<int>` where point $i$ is at indices `2*i` and `2*i+1` keeps coordinates contiguous in RAM, maximizing CPU cache lines.
