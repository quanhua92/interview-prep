# Sliding Window Median

- **Category**: Coding
- **Difficulty**: Hard
- **Target Role**: Software Engineer / Low-Level Developer / AI Systems Architect
- **Source**: LeetCode 480, Glassdoor
- **Flashcards**: [Two Heaps deck](../../flash_cards/coding/two_heaps.md)

---

## Question Description

You are given an integer array `nums` and an integer `k`. There is a sliding window of size `k` which is moving from the very left of the array to the very right. You can only see the `k` numbers in the window. Each time the sliding window moves right by one position.

Return the median array for each window in the original array. Answers within $10^{-5}$ of the actual value will be accepted.

### Examples
*   **Input**: `nums = [1,3,-1,-3,5,3,6,7]`, `k = 3`
    *   **Output**: `[1.00000,-1.00000,-1.00000,3.00000,5.00000,6.00000]`
    *   **Explanation**:
        ```text
        Window position                Median
        ---------------                ------
        [1  3  -1] -3  5  3  6  7       1
         1 [3  -1  -3] 5  3  6  7      -1
         1  3 [-1  -3  5] 3  6  7      -1
         1  3  -1 [-3  5  3] 6  7       3
         1  3  -1  -3 [5  3  6] 7       5
         1  3  -1  -3  5 [3  6  7]      6
        ```
*   **Input**: `nums = [1,2,3,4,2,3,1,4,2]`, `k = 3`
    *   **Output**: `[2.00000,3.00000,3.00000,3.00000,2.00000,3.00000,2.00000]`

---

## Detailed Solution (C++)

To solve this efficiently in $\mathcal{O}(N \log k)$ time, we use a **Two Heaps** approach (a max-heap `small` for the lower half and a min-heap `large` for the upper half) paired with **Lazy Deletion**.

### Lazy Deletion Logic
Unlike standard median finding in a continuous stream, elements in a sliding window expire and must be removed. Since standard binary heaps do not support removing arbitrary elements in $\mathcal{O}(\log k)$ time, we use **lazy deletion**:
1. When an element falls out of the sliding window, we record its index (or value) in a hash map `delayed` representing elements scheduled for deletion.
2. We decrement the active size counters of the respective heap (`small_sz` or `large_sz`).
3. Whenever we access the top element of either heap, we check if it is in `delayed`. If it is, we pop it (prune the heap) and decrement the delayed count until we find a non-deleted top element.
4. We then rebalance the active sizes of the heaps so that $\text{smallSz} \in [\text{largeSz}, \text{largeSz} + 1]$.

### Standard C++ Production Code

```cpp
#include <vector>
#include <queue>
#include <unordered_map>

class Solution {
public:
    std::vector<double> medianSlidingWindow(std::vector<int>& nums, int k) {
        struct Entry {
            long long val;
            int idx;
            bool operator<(const Entry& other) const { return val < other.val; }
        };
        
        struct GreaterEntry {
            bool operator()(const Entry& a, const Entry& b) const { return a.val > b.val; }
        };

        std::priority_queue<Entry> small; // Max-heap
        std::priority_queue<Entry, std::vector<Entry>, GreaterEntry> large; // Min-heap
        
        std::unordered_map<int, int> delayed;
        std::vector<bool> in_small(nums.size(), false);
        int small_sz = 0, large_sz = 0;
        
        auto prune_small = [&]() {
            while (!small.empty() && delayed.count(small.top().idx)) {
                int idx = small.top().idx;
                if (--delayed[idx] == 0) delayed.erase(idx);
                small.pop();
            }
        };

        auto prune_large = [&]() {
            while (!large.empty() && delayed.count(large.top().idx)) {
                int idx = large.top().idx;
                if (--delayed[idx] == 0) delayed.erase(idx);
                large.pop();
            }
        };

        auto make_balanced = [&]() {
            if (small_sz > large_sz + 1) {
                prune_small();
                auto [v, idx] = small.top(); small.pop();
                in_small[idx] = false;
                small_sz--; large_sz++;
                large.push({v, idx});
                prune_small();
            } else if (small_sz < large_sz) {
                prune_large();
                auto [v, idx] = large.top(); large.pop();
                in_small[idx] = true;
                large_sz--; small_sz++;
                small.push({v, idx});
                prune_large();
            }
        };

        std::vector<double> medians;
        int n = static_cast<int>(nums.size());

        for (int i = 0; i < n; i++) {
            prune_small();
            prune_large();

            // Insert new element
            if (small.empty() || nums[i] <= small.top().val) {
                small.push({(long long)nums[i], i});
                in_small[i] = true;
                small_sz++;
            } else {
                large.push({(long long)nums[i], i});
                in_small[i] = false;
                large_sz++;
            }

            make_balanced();

            // Handle element exiting the window
            if (i >= k) {
                int out_idx = i - k;
                delayed[out_idx]++;
                if (in_small[out_idx]) {
                    small_sz--;
                } else {
                    large_sz--;
                }
                make_balanced();
            }

            // Record median
            if (i >= k - 1) {
                prune_small();
                prune_large();
                if (k % 2 == 1) {
                    medians.push_back(static_cast<double>(small.top().val));
                } else {
                    medians.push_back((static_cast<double>(small.top().val) + large.top().val) / 2.0);
                }
            }
        }

        return medians;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

```python
import heapq
from typing import List, Dict

class Solution:
    def medianSlidingWindow(self, nums: List[int], k: int) -> List[float]:
        """
        Computes the median of each sliding window of size k using two heaps and lazy deletion.
        
        Time Complexity: O(N log k)
        Space Complexity: O(N)
        """
        small: List[tuple[int, int]] = []  # Max-heap (negative values)
        large: List[tuple[int, int]] = []  # Min-heap (positive values)
        
        delayed: Dict[int, int] = {}
        in_small: Dict[int, bool] = {}
        small_size = 0
        large_size = 0
        
        def prune(heap: List[tuple[int, int]]) -> None:
            while heap:
                _, idx = heap[0]
                if idx in delayed:
                    delayed[idx] -= 1
                    if delayed[idx] == 0:
                        del delayed[idx]
                    heapq.heappop(heap)
                else:
                    break

        def make_balanced() -> None:
            nonlocal small_size, large_size
            if small_size > large_size + 1:
                prune(small)
                val, idx = heapq.heappop(small)
                heapq.heappush(large, (-val, idx))
                in_small[idx] = False
                small_size -= 1
                large_size += 1
                prune(small)
            elif small_size < large_size:
                prune(large)
                val, idx = heapq.heappop(large)
                heapq.heappush(small, (-val, idx))
                in_small[idx] = True
                large_size -= 1
                small_size += 1
                prune(large)

        def get_median() -> float:
            if k % 2 == 1:
                return float(-small[0][0])
            else:
                return (-small[0][0] + large[0][0]) / 2.0

        medians = []
        for i, val in enumerate(nums):
            prune(small)
            prune(large)
            
            # Insert element
            if not small or val <= -small[0][0]:
                heapq.heappush(small, (-val, i))
                in_small[i] = True
                small_size += 1
            else:
                heapq.heappush(large, (val, i))
                in_small[i] = False
                large_size += 1
                
            make_balanced()
            
            # Remove element leaving window
            if i >= k:
                out_idx = i - k
                delayed[out_idx] = delayed.get(out_idx, 0) + 1
                if in_small.get(out_idx, True):
                    small_size -= 1
                else:
                    large_size -= 1
                make_balanced()
                
            # Collect result
            if i >= k - 1:
                prune(small)
                prune(large)
                medians.append(get_median())
                
        return medians
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Simulating Deletion in Heap
*   Since `heapq` does not support random element removal, lazy deletion is the only way to retain $\mathcal{O}(\log k)$ average updates. Direct lookup and deletion via `list.remove()` takes $\mathcal{O}(k)$ time, which degrades the overall complexity of the sliding window to $\mathcal{O}(N \cdot k)$ and causes Time Limit Exceeded (TLE).

### 2. Float Underflow/Overflow
*   In Python, dividing large integers by $2.0$ automatically yields high-precision floats without risking overflow. In languages with fixed width types like C++, computing `(small.top().val + large.top().val) / 2.0` can overflow if both values are near $2^{31} - 1$, so casting to `long long` is necessary.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(n \log n)$ | Each of the $n$ elements is pushed and popped from the heaps at most once. The heaps are kept balanced using $O(\log n)$ operations. |
| **Space Complexity** | $\mathcal{O}(n)$ | To store the `delayed` deletion map and `in_small` map, up to size $n$. |

---

## Common Follow-Up Questions & How to Answer

### Q1: Can we use standard Binary Search Tree (BST) structures?
*   **Answer**: Yes. In C++, `std::multiset` is implemented as a Red-Black Tree. We can insert and delete elements in $\mathcal{O}(\log k)$ time and keep track of the median iterator. During insertions/deletions, we update the median iterator by shifting it left or right. This avoids lazy deletion completely and achieves $\mathcal{O}(N \log k)$ time and $\mathcal{O}(k)$ space.

### Q2: How would you parallelize this for huge data streams?
*   **Answer**: Since the sliding window has a dependency on the previous state, parallelizing the window updates directly is difficult. However, we can shard the array into overlapping chunks of size $M$ (where chunks overlap by $k-1$ elements), process each chunk on different threads/cores, and combine the results.

---

## Pro-Tip: How to Impress the Interviewer

*   **Implement with std::multiset in C++**: Show that you know how to use `std::multiset` to build a clean solution. The iterator updates can be tricky:
    ```cpp
    // Insert element, if it's less than *mid, decrement mid iterator
    // Delete element, if it's less than or equal to *mid, increment mid iterator
    ```
    This demonstrates solid understanding of C++ STL container internals and iterator stability.
*   **Warp Memory Accesses**: Highlight that when running this on resource-constrained systems, lazy deletion causes heap size to grow up to $N$. If $N \gg k$, this wastes memory. Rebuilding the heaps or pruning aggressively when `delayed.size()` exceeds a threshold (e.g. $> 2k$) keeps memory consumption bounded to $\mathcal{O}(k)$.
