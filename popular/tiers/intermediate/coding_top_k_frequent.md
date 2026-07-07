# Top K Frequent Elements

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / Low-Level Developer / AI Systems Architect
- **Source**: LeetCode 347, Glassdoor
- **Flashcards**: [Top K Elements deck](../../flash_cards/coding/top_k_elements.md)

---

## Question Description

Given an integer array `nums` and an integer `k`, return the `k` most frequent elements. You may return the answer in **any order**.

### Follow up:
*   Your algorithm's time complexity must be better than $\mathcal{O}(n \log n)$, where $n$ is the array's size.

### Examples
*   **Input**: `nums = [1,1,1,2,2,3]`, `k = 2`
    *   **Output**: `[1,2]`
*   **Input**: `nums = [1]`, `k = 1`
    *   **Output**: `[1]`

---

## Detailed Solution (C++)

To solve this problem better than $\mathcal{O}(n \log n)$ time, we can use two distinct strategies:

1. **Min-Heap Approach ($\mathcal{O}(n \log k)$ time)**:
   - Build a frequency map of elements in $\mathcal{O}(n)$ time.
   - Keep a min-heap of size $k$. For each unique element, push it onto the heap. If the heap size exceeds $k$, pop the least frequent element.
   - Pop the remaining elements from the heap into our result.

2. **Bucket Sort Approach ($\mathcal{O}(n)$ time & space)**:
   - Build a frequency map.
   - Create an array of lists/vectors called `buckets`, where the index represents the frequency of elements (size $n + 1$).
   - Place each unique element into the bucket corresponding to its frequency.
   - Traverse the buckets from right to left (highest frequency to lowest) and collect elements until we have $k$ elements.

We present the optimal **Bucket Sort** solution as it guarantees linear time complexity.

### Standard C++ Production Code (Bucket Sort)

```cpp
#include <vector>
#include <unordered_map>

class Solution {
public:
    std::vector<int> topKFrequent(std::vector<int>& nums, int k) {
        // Step 1: Count frequency of each element
        std::unordered_map<int, int> freqMap;
        for (int num : nums) {
            freqMap[num]++;
        }

        int n = static_cast<int>(nums.size());
        // Step 2: Create buckets. Index represents frequency.
        // Elements with frequency 'f' will be in buckets[f]
        std::vector<std::vector<int>> buckets(n + 1);
        for (const auto& [num, count] : freqMap) {
            buckets[count].push_back(num);
        }

        // Step 3: Gather the top k frequent elements
        std::vector<int> result;
        result.reserve(k);
        for (int i = n; i >= 0 && result.size() < k; --i) {
            if (!buckets[i].empty()) {
                for (int num : buckets[i]) {
                    result.push_back(num);
                    if (result.size() == k) {
                        break;
                    }
                }
            }
        }

        return result;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code (Bucket Sort)

```python
from collections import Counter
from typing import List

class Solution:
    def topKFrequent(self, nums: List[int], k: int) -> List[int]:
        """
        Finds the k most frequent elements using Bucket Sort.
        
        Time Complexity: O(n)
        Space Complexity: O(n)
        """
        # Step 1: Count frequencies
        freq_map = Counter(nums)
        n = len(nums)
        
        # Step 2: Initialize buckets (index represents frequency)
        buckets = [[] for _ in range(n + 1)]
        for val, count in freq_map.items():
            buckets[count].append(val)
            
        # Step 3: Collect top k frequent elements
        result = []
        for i in range(n, 0, -1):
            for val in buckets[i]:
                result.append(val)
                if len(result) == k:
                    return result
                    
        return result
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Built-in `Counter.most_common`
*   Python's `Counter` class has a method `.most_common(k)`. Under the hood, this method uses `heapq.nlargest` if $k$ is small, or sorts if $k$ is close to the number of unique elements. 
*   While `Counter(nums).most_common(k)` is acceptable for simple applications, implementing the bucket sort shows structural depth in system design interviews since it achieves true $\mathcal{O}(n)$ complexity.

### 2. Space Overhead of Hash Maps and Buckets
*   Python lists are dynamic arrays. Storing $n+1$ lists in the `buckets` array consumes a moderate amount of memory because empty lists still reserve pointers. 
*   If memory is highly constrained, a Min-Heap approach with a size boundary of $k$ is more space-efficient than Bucket Sort, as it limits auxiliary storage to $\mathcal{O}(u + k)$ instead of $\mathcal{O}(n)$.

---

## Complexity Analysis

### Bucket Sort:
| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(n)$ | Counting frequencies takes $\mathcal{O}(n)$. Generating buckets takes $\mathcal{O}(u)$ where $u \le n$. Retrieving the top $k$ items takes $\mathcal{O}(n)$ in the worst case. |
| **Space Complexity** | $\mathcal{O}(n)$ | To store the frequency map and buckets. |

### Min-Heap:
| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(n \log k)$ | Counting frequencies is $\mathcal{O}(n)$. Maintaining a heap of size $k$ for $u$ unique elements takes $\mathcal{O}(u \log k)$. |
| **Space Complexity** | $\mathcal{O}(u + k)$ | To store the frequency map and the heap. |

---

## Common Follow-Up Questions & How to Answer

### Q1: What if the elements are streaming?
*   **Answer**: In a streaming environment, Bucket Sort is impractical because the total size $n$ keeps growing, meaning we would constantly need to resize our bucket array and re-place items. Instead, we use the **Min-Heap** approach coupled with a hash map. The hash map tracks running frequencies, and the min-heap tracks the top $k$ elements dynamically.

### Q2: Can we solve this using Quickselect?
*   **Answer**: Yes. We count the frequencies and convert the map to a list of pairs `(element, frequency)`. We then run Quickselect (similar to partitioning in Quicksort) targeting the $(N-k)^{\text{th}}$ index based on frequency. This averages $\mathcal{O}(n)$ time and uses $\mathcal{O}(u)$ space.

---

## Pro-Tip: How to Impress the Interviewer

*   **Explain Cache Locality of Buckets**: Point out that the C++ Bucket Sort uses a `std::vector<std::vector<int>>`. This vector of vectors causes **pointer chasing** because each sub-vector is allocated on different parts of the heap. To optimize cache locality, we can instead use a single flat vector for the values, along with an array of offsets to mark the start of each bucket.
*   **Discuss Space-Time Trade-offs**: Emphasize that Bucket Sort is faster than Min-Heap ($\mathcal{O}(n)$ vs $\mathcal{O}(n \log k)$), but it trades off memory. If $n$ is very large (e.g. $10^9$) but there are only a few unique elements, the heap solution is vastly superior.
