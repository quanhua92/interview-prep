# Kth Largest Element in an Array

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / Low-Level Developer / AI Systems Architect
- **Source**: LeetCode 215, Glassdoor

---

## Question Description

Given an integer array `nums` and an integer `k`, return the $k^{\text{th}}$ largest element in the array.

Note that it is the $k^{\text{th}}$ largest element in the sorted order, not the $k^{\text{th}}$ distinct element.

Can you solve it without sorting in $\mathcal{O}(n)$ average time complexity?

### Examples
*   **Input**: `nums = [3,2,1,5,6,4]`, `k = 2`
    *   **Output**: `5`
*   **Input**: `nums = [3,2,3,1,2,4,5,5,6]`, `k = 4`
    *   **Output**: `4`

---

## Detailed Solution (C++)

There are two primary ways to solve this problem:

1. **Min-Heap Approach ($\mathcal{O}(n \log k)$)**: Maintain a min-heap of size $k$. As we scan the array, we push elements into the heap. If the heap size exceeds $k$, we pop the minimum element. At the end, the top of the heap is the $k^{\text{th}}$ largest element.
2. **Quickselect Approach ($\mathcal{O}(n)$ average)**: A divide-and-conquer algorithm based on Quicksort. We select a pivot, partition the array, and only recurse into the side containing the $k^{\text{th}}$ largest position.

In C++, `std::nth_element` uses **Introselect**, a hybrid of Quickselect and Heapsort. It guarantees $\mathcal{O}(n)$ worst-case time by switching to Heapsort if the recursion depth exceeds a threshold.

### Standard C++ Production Code

#### Optimal Approach: Introselect ($\mathcal{O}(n)$ Time, $\mathcal{O}(1)$ Space)
```cpp
#include <vector>
#include <algorithm>

class Solution {
public:
    int findKthLargest(std::vector<int>& nums, int k) {
        // Rearranges elements such that the (k-1)-th element is in its sorted position
        // std::greater<int>() sorts in descending order
        std::nth_element(nums.begin(), nums.begin() + k - 1, nums.end(), std::greater<int>());
        return nums[k - 1];
    }
};
```

#### Alternative Approach: Min-Heap ($\mathcal{O}(n \log k)$ Time, $\mathcal{O}(k)$ Space)
```cpp
#include <vector>
#include <queue>

class SolutionHeap {
public:
    int findKthLargest(std::vector<int>& nums, int k) {
        std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;
        for (int num : nums) {
            minHeap.push(num);
            if (minHeap.size() > k) {
                minHeap.pop();
            }
        }
        return minHeap.top();
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code (Min-Heap)

```python
import heapq
from typing import List

class Solution:
    def findKthLargest(self, nums: List[int], k: int) -> int:
        """
        Finds the kth largest element using a min-heap of size k.
        
        Time Complexity: O(n log k)
        Space Complexity: O(k)
        """
        # Initialize a min-heap with the first k elements
        heap = nums[:k]
        heapq.heapify(heap)
        
        # Iterate over the rest of the elements
        for num in nums[k:]:
            if num > heap[0]:
                heapq.heappushpop(heap, num)
                
        return heap[0]
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. `heapq.nlargest` Performance
*   Python has a built-in helper `heapq.nlargest(k, nums)`. Under the hood, this uses a min-heap of size $k$ and is implemented in C. While writing `heapq.nlargest(k, nums)[-1]` is clean, manually writing the loop with `heappushpop` shows standard algorithm fluency to an interviewer.

### 2. Quickselect Stack Overflow Risk
*   If you implement Quickselect recursively in Python, a poor pivot choice (e.g. on already sorted arrays) can degrade the complexity to $\mathcal{O}(n^2)$ and cause a `RecursionError` due to the stack depth. An iterative implementation of Quickselect is safer in Python.

---

## Complexity Analysis

### Min-Heap:
| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(n \log k)$ | We iterate through all $n$ elements. Each heap insertion/extraction takes $\mathcal{O}(\log k)$. |
| **Space Complexity** | $\mathcal{O}(k)$ | The size of the min-heap. |

### Quickselect / Introselect:
| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(n)$ average | The partitioning step is $\mathcal{O}(n)$, and we recurse on average into a partition of size $n/2$, yielding $T(n) = T(n/2) + \mathcal{O}(n) = \mathcal{O}(n)$. |
| **Space Complexity** | $\mathcal{O}(1)$ | Done in-place. Stack depth is $\mathcal{O}(\log n)$ or $\mathcal{O}(1)$ if implemented iteratively. |

---

## Common Follow-Up Questions & How to Answer

### Q1: When is the Min-Heap approach preferred over Quickselect?
*   **Answer**: The heap approach is preferred for **Data Streams** (online algorithms). If the data is too large to fit in memory or arrives incrementally, we cannot partition the array in-place. A min-heap only needs to store $k$ elements in memory at any point.

### Q2: What if the range of elements is small? (e.g., values in $[-10000, 10000]$)
*   **Answer**: We can use **Counting Sort**. Create a frequency array (bucket array) representing the count of each number. Scan from right to left (largest to smallest) and decrement $k$ by the count of each bucket. The bucket where $k$ becomes $\le 0$ contains the $k^{\text{th}}$ largest element. This runs in $\mathcal{O}(n + R)$ time and $\mathcal{O}(R)$ space, where $R$ is the range.

---

## Pro-Tip: How to Impress the Interviewer

*   **Mention Introselect vs. Quickselect**: Explain that naive Quickselect has a worst-case time complexity of $\mathcal{O}(n^2)$ (e.g. if the array is already sorted and we choose the first element as pivot). Point out that C++'s `std::nth_element` uses **Introselect**, which detects if recursion is degrading and automatically falls back to Heapsort, guaranteeing $\mathcal{O}(n)$ worst-case.
*   **Median of Medians**: Mention the **Median of Medians** (BFPRT) algorithm, which chooses a pivot in $\mathcal{O}(n)$ time such that Quickselect is guaranteed to run in $\mathcal{O}(n)$ worst-case. Note that in practice, the constant factors of BFPRT are too high, so randomized pivots or Introselect are preferred.
