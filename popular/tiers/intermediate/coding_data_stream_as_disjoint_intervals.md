# Data Stream as Disjoint Intervals

- **Category**: Coding
- **Difficulty**: Hard
- **Target Role**: Software Engineer / AI Systems Architect
- **Source**: LeetCode 352, Glassdoor
- **Flashcards**: [Binary Search deck](../../flash_cards/coding/binary_search.md)

---

## Question Description

Given a data stream input of non-negative integers $a_1, a_2, \dots, a_n$, summarize the numbers seen so far as a list of disjoint intervals.

Implement the `SummaryRanges` class:

*   `SummaryRanges()` Initializes the object with an empty stream.
*   `void addNum(int value)` Adds the integer `value` to the stream.
*   `int[][] getIntervals()` Returns a summary of the integers in the stream currently as a list of disjoint intervals $[start_i, end_i]$. The answer should be sorted by $start_i$.

### Examples

*   **Input**:
    `["SummaryRanges", "addNum", "getIntervals", "addNum", "getIntervals", "addNum", "getIntervals", "addNum", "getIntervals", "addNum", "getIntervals"]`
    `[[], [1], [], [3], [], [7], [], [2], [], [6], []]`
*   **Output**:
    `[null, null, [[1, 1]], null, [[1, 1], [3, 3]], null, [[1, 1], [3, 3], [7, 7]], null, [[1, 3], [7, 7]], null, [[1, 3], [6, 7]]]`
*   **Explanation**:
    ```python
    summaryRanges = SummaryRanges()
    summaryRanges.addNum(1)      # Stream: [1]
    summaryRanges.getIntervals() # Returns [[1, 1]]
    summaryRanges.addNum(3)      # Stream: [1, 3]
    summaryRanges.getIntervals() # Returns [[1, 1], [3, 3]]
    summaryRanges.addNum(7)      # Stream: [1, 3, 7]
    summaryRanges.getIntervals() # Returns [[1, 1], [3, 3], [7, 7]]
    summaryRanges.addNum(2)      # Stream: [1, 2, 3, 7]
    summaryRanges.getIntervals() # Returns [[1, 3], [7, 7]]
    summaryRanges.addNum(6)      # Stream: [1, 2, 3, 6, 7]
    summaryRanges.getIntervals() # Returns [[1, 3], [6, 7]]
    ```

### Constraints
*   $0 \le \text{value} \le 10^4$
*   At most $3 \times 10^4$ calls will be made to `addNum` and `getIntervals`.
*   At most $10^2$ calls will be made to `getIntervals`.

---

## Detailed Solution (C++)

In C++, we can use `std::map<int, int>` to store intervals as mapping of `start -> end`. Since `std::map` keeps keys sorted in a Red-Black Tree, we can efficiently find the correct position to insert/merge the new value using binary search: `upper_bound(value)`.

### Insertion Logic for `addNum(value)`:
1. Find the first interval starting strictly after `value` using `upper_bound`.
2. Check the predecessor interval. If it overlaps or is contiguous with `value` (i.e. `prev->second >= value - 1`), merge `value` into `prev`, updating `start` to `prev->first` and `end` to `max(value, prev->second)`. Delete the predecessor interval as it is now represented by the new boundaries.
3. Check subsequent intervals. If a successor interval starts within `end + 1`, it must be merged as well. Update `end = max(end, it->second)` and erase `it` from the map.
4. Finally, insert the new merged interval `intervals[start] = end`.

### Standard C++ Production Code

```cpp
#include <vector>
#include <map>
#include <algorithm>
#include <iterator>

class SummaryRanges {
private:
    // Sorted map mapping interval start to interval end
    std::map<int, int> intervals;

public:
    SummaryRanges() = default;

    void addNum(int value) {
        int start = value;
        int end = value;

        // Find the first interval starting strictly after 'value'
        auto it = intervals.upper_bound(value);

        // Check if the predecessor interval can be merged with 'value'
        if (it != intervals.begin()) {
            auto prev = std::prev(it);
            if (prev->second >= value - 1) {
                start = prev->first;
                end = std::max(end, prev->second);
                intervals.erase(prev);
            }
        }

        // Check and merge any successor intervals that overlap or touch
        while (it != intervals.end() && it->first <= end + 1) {
            end = std::max(end, it->second);
            it = intervals.erase(it); // Returns iterator to the next element
        }

        // Insert the merged interval
        intervals[start] = end;
    }

    std::vector<std::vector<int>> getIntervals() {
        std::vector<std::vector<int>> res;
        res.reserve(intervals.size());
        for (const auto& [start, end] : intervals) {
            res.push_back({start, end});
        }
        return res;
    }
};
```

---

## Detailed Solution (Python)

In Python, we maintain a sorted list of intervals. We use the `bisect` module to binary search the correct insertion index. 

### Standard Python Production Code

```python
import bisect
from typing import List

class SummaryRanges:
    def __init__(self):
        # Stores intervals as [start, end], maintained in sorted order
        self.intervals: List[List[int]] = []

    def addNum(self, value: int) -> None:
        lo, hi = value, value
        
        # Binary search the correct insertion position
        pos = bisect.bisect_left(self.intervals, [lo, hi])
        
        # Check if the predecessor interval overlaps or touches the value
        if pos > 0 and self.intervals[pos - 1][1] >= lo - 1:
            pos -= 1
            lo = self.intervals[pos][0]
            
        # Check and merge any overlapping or contiguous successor intervals
        while pos < len(self.intervals) and self.intervals[pos][0] <= hi + 1:
            hi = max(hi, self.intervals[pos][1])
            del self.intervals[pos]
            
        # Insert the newly merged interval
        self.intervals.insert(pos, [lo, hi])

    def getIntervals(self) -> List[List[int]]:
        return self.intervals
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Python List Shift Overhead
* Using `list.insert(pos, ...)` and `del list[pos]` in Python requires shifting subsequent elements in memory. This introduces an $\mathcal{O}(k)$ time complexity (where $k$ is the number of intervals, up to $N$). 
* For the given constraints ($3 \times 10^4$ calls), this array-backed list is extremely fast due to cache locality and low constant overhead of PyObject arrays, passing easily on LeetCode. 
* In a production Python environment with massive datasets, using a tree-based structure like `SortedDict` or `SortedList` from the `sortedcontainers` library provides true $\mathcal{O}(\log k)$ insertions.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity (addNum)** | $\mathcal{O}(\log k)$ in C++, $\mathcal{O}(k)$ in Python | C++ uses a balanced BST (`std::map`), so search, merge, and insertions take logarithmic time in terms of the number of intervals $k$. Python performs $\mathcal{O}(\log k)$ search but $\mathcal{O}(k)$ list shifts. |
| **Time Complexity (getIntervals)** | $\mathcal{O}(k)$ | Iterates and copies all $k$ disjoint intervals into a result list. |
| **Space Complexity** | $\mathcal{O}(k)$ | Stores up to $k$ disjoint intervals in the underlying data structure. |

---

## Common Follow-Up Questions & How to Answer

### Q1: What if there are lots of merges and the number of disjoint intervals is small compared to the size of the data stream?
* **Answer**: If we have many duplicate inputs or dense sequences, the number of intervals $k$ will remain small.
  * Our lookup time $\mathcal{O}(\log k)$ becomes effectively $\mathcal{O}(1)$.
  * To optimize further, we can keep a fast lookup hash set (`std::unordered_set`) of values we have already seen. If `value` is already in the set, we can return immediately from `addNum` in $\mathcal{O}(1)$ time without searching or modifying the tree.

### Q2: How can we implement this if memory is extremely constrained?
* **Answer**: We can compress intervals using a **segment tree** with dynamic node allocation (lazy propagation), or run-length encoding. Alternatively, if we only need to query intervals occasionally, we could buffer the raw input numbers and run a sorting-based merge interval algorithm only when `getIntervals()` is called.

---

## Pro-Tip: How to Impress the Interviewer

* **Use of standard library iterators**: In C++, demonstrating proper handling of `std::prev` and receiving the next valid iterator returned by `intervals.erase(it)` displays deep knowledge of C++ iterator invalidation rules.
* **Suggest `unordered_set` optimization**: Explain that in real-world data streams, duplicates are very frequent. Propose filtering incoming values with a `HashSet` filter at the front to bypass the logarithmic tree search completely for duplicate inputs.
