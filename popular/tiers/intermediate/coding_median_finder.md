# Find Median from Data Stream

- **Category**: Coding
- **Difficulty**: Hard
- **Target Role**: Software Engineer / Low-Level Developer / AI Systems Architect
- **Source**: LeetCode 295, Glassdoor
- **Flashcards**: [Two Heaps deck](../../flash_cards/coding/two_heaps.md)

---

## Question Description

The median is the middle value in an ordered integer list. If the size of the list is even, there is no middle value, and the median is the mean of the two middle values.
*   For example, if `arr = [2, 3, 4]`, the median is `3`.
*   If `arr = [2, 3]`, the median is `(2 + 3) / 2 = 2.5`.

Implement the `MedianFinder` class:
*   `MedianFinder()` initializes the `MedianFinder` object.
*   `void addNum(int num)` adds the integer `num` from the data stream to the data structure.
*   `double findMedian()` returns the median of all elements so far. Answers within $10^{-5}$ of the actual answer will be accepted.

### Examples
*   **Input**:
    ```text
    ["MedianFinder", "addNum", "addNum", "findMedian", "addNum", "findMedian"]
    [[], [1], [2], [], [3], []]
    ```
*   **Output**: `[null, null, null, 1.5, null, 2.0]`
*   **Explanation**:
    ```cpp
    MedianFinder mf;
    mf.addNum(1);    // arr = [1]
    mf.addNum(2);    // arr = [1, 2]
    mf.findMedian(); // returns 1.5 (i.e., (1 + 2) / 2)
    mf.addNum(3);    // arr = [1, 2, 3]
    mf.findMedian(); // returns 2.0
    ```

---

## Detailed Solution (C++)

The most efficient approach uses **Two Heaps**:
1. **A Max-Heap** (`small`): stores the smaller half of the numbers.
2. **A Min-Heap** (`large`): stores the larger half of the numbers.

### Rebalancing Invariant
*   The max-heap `small` can contain at most **one more** element than the min-heap `large`.
*   Thus: $\text{len}(small) \ge \text{len}(large)$ and $\text{len}(small) - \text{len}(large) \le 1$.

### Algorithm
*   **Add Num**: 
    1. First push `num` to the max-heap `small`.
    2. Pop the top of `small` and push it to the min-heap `large` (ensuring all elements in `large` are greater than or equal to elements in `small`).
    3. If `large.size() > small.size()`, pop the top of `large` and push it back to `small` to restore the size balance.
*   **Find Median**:
    1. If `small.size() > large.size()`, the median is the top of `small`.
    2. Otherwise, the median is the average of the tops of both heaps.

### Standard C++ Production Code

```cpp
#include <queue>
#include <vector>

class MedianFinder {
private:
    std::priority_queue<int> small; // Max-heap for lower half
    std::priority_queue<int, std::vector<int>, std::greater<int>> large; // Min-heap for upper half

public:
    MedianFinder() = default;

    void addNum(int num) {
        small.push(num);
        large.push(small.top());
        small.pop();
        
        // Maintain the size invariant: small.size() >= large.size()
        if (large.size() > small.size()) {
            small.push(large.top());
            large.pop();
        }
    }

    double findMedian() {
        if (small.size() > large.size()) {
            return static_cast<double>(small.top());
        }
        return (static_cast<double>(small.top()) + large.top()) / 2.0;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

```python
import heapq

class MedianFinder:
    def __init__(self):
        """
        Initializes the Max-Heap (small) and Min-Heap (large).
        We store negative values in small to simulate a Max-Heap.
        """
        self.small = []  # Max-Heap (stores negative numbers)
        self.large = []  # Min-Heap (stores positive numbers)

    def addNum(self, num: int) -> None:
        """
        Adds a number to the data stream.
        
        Time Complexity: O(log n)
        """
        # Push to small (max-heap)
        heapq.heappush(self.small, -num)
        
        # Pop from small, push to large (min-heap)
        heapq.heappush(self.large, -heapq.heappop(self.small))
        
        # Balance sizes
        if len(self.large) > len(self.small):
            heapq.heappush(self.small, -heapq.heappop(self.large))

    def findMedian(self) -> float:
        """
        Returns the median of the data stream.
        
        Time Complexity: O(1)
        """
        if len(self.small) > len(self.large):
            return float(-self.small[0])
        return (-self.small[0] + self.large[0]) / 2.0
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Max-Heap Implementation in Python
*   Python's `heapq` module only implements Min-Heaps. To implement a Max-Heap, we must negate all numbers before inserting them (`-num`). 
*   When retrieving elements from the max-heap, remember to negate them again to get the original values (e.g. `-self.small[0]`).
*   **Integer Overflow Check**: Negating numbers in Python is safe because Python integers have arbitrary precision and cannot overflow.

### 2. Float Division `/` vs Floor Division `//`
*   When calculating the average of the two middle elements, always use float division `/` (e.g., `(-self.small[0] + self.large[0]) / 2.0`) to ensure a floating-point result is returned. Using integer division `//` will truncate fractional values.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity (addNum)** | $\mathcal{O}(\log n)$ | Each insert involves heap push and pop operations, taking logarithmic time. |
| **Time Complexity (findMedian)** | $\mathcal{O}(1)$ | The median is computed directly from the top elements of both heaps. |
| **Space Complexity** | $\mathcal{O}(n)$ | To store all elements in the data stream inside the two heaps. |

---

## Common Follow-Up Questions & How to Answer

### Q1: What if all integer numbers from the stream are between $0$ and $100$?
*   **Answer**: We can replace the heaps with a **Frequency Array** of size 101. We maintain a count of elements in each bucket, plus a total element counter. 
    *   To find the median, we scan the frequency array to find the middle indices.
    *   Time Complexity: `addNum` becomes $\mathcal{O}(1)$, and `findMedian` takes $\mathcal{O}(1)$ because the bucket count is constant (101).
    *   Space Complexity: $\mathcal{O}(1)$ auxiliary space.

### Q2: What if 99% of all integer numbers from the stream are between $0$ and $100$?
*   **Answer**: We can keep a frequency array of size 101 for the range $[0, 100]$, and two heaps for elements $<0$ and $>100$. Since 99% of elements fall inside $[0, 100]$, the median will almost certainly lie in the range $[0, 100]$, which we can find by index scanning, taking $\mathcal{O}(1)$ average time.

---

## Pro-Tip: How to Impress the Interviewer

*   **Avoid Redundant Heap Checks**: When writing C++, show that you can insert and balance in just 4 lines of code without using complex conditional branching. Pushing to one, shifting to the next, and rebalancing by size eliminates unnecessary comparisons and keeps code compact.
*   **Cache Locality and Heap Implementations**: Mention that while heaps are theoretically fast, they are laid out in memory as arrays where children are at indices `2*i + 1` and `2*i + 2`. As the heap grows, traversing it causes random memory jumps, which can result in cache misses. For extremely latency-sensitive trading platforms, flat array structures or B-trees might be preferred.
