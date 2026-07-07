# Meeting Rooms II

- **Category**: Coding
- **Difficulty**: Medium
- **Target Role**: Software Engineer / Low-Level Developer
- **Source**: LeetCode 253, Glassdoor

---

## Question Description

Given an array of meeting time intervals `intervals` where `intervals[i] = [start_i, end_i]`, return *the minimum number of conference rooms required*.

### Examples
*   **Input**: `intervals = [[0,30],[5,10],[15,20]]`
    *   **Output**: `2`
    *   **Explanation**: 
        *   Meeting 1 starts at 0 and ends at 30. We need Room 1.
        *   Meeting 2 starts at 5 and ends at 10. Room 1 is occupied. We need Room 2.
        *   Meeting 3 starts at 15 and ends at 20. Room 2 is free (since Meeting 2 finished at 10), so we reuse Room 2.
        *   Maximum concurrent rooms needed is 2.
*   **Input**: `intervals = [[7,10],[2,4]]`
    *   **Output**: `1`
    *   **Explanation**: The meetings do not overlap, so only 1 room is needed.

---

## Detailed Solution (C++)

A standard chronological sweep-line approach operates by separating the start and end times:
1.  **Extract and Sort**: Store all start times in one array `starts` and all end times in another array `ends`. Sort both arrays independently.
2.  **Two Pointers**: Maintain a pointer for `starts` and a pointer for `ends`.
    *   If a meeting starts at `starts[startPtr]` before the oldest meeting ends at `ends[endPtr]`, it means we must allocate a new room (`rooms++`).
    *   If `starts[startPtr] >= ends[endPtr]`, the oldest meeting has finished. We can reuse its room. We increment `endPtr` to point to the next meeting ending time.
3.  **Result**: The number of rooms counted at the end is the peak overlap of active meetings.

This approach is highly efficient as it eliminates the overhead of maintaining a heap/priority queue.

### Standard C++ Production Code

```cpp
#include <vector>
#include <algorithm>

class Solution {
public:
    int minMeetingRooms(const std::vector<std::vector<int>>& intervals) {
        if (intervals.empty()) {
            return 0;
        }

        const size_t n = intervals.size();
        std::vector<int> starts;
        std::vector<int> ends;
        starts.reserve(n);
        ends.reserve(n);

        // Separate start and end times
        for (const auto& interval : intervals) {
            starts.push_back(interval[0]);
            ends.push_back(interval[1]);
        }

        // Sort both arrays independently
        std::sort(starts.begin(), starts.end());
        std::sort(ends.begin(), ends.end());

        int rooms = 0;
        size_t endPtr = 0;

        // Traverse all start times
        for (size_t startPtr = 0; startPtr < n; ++startPtr) {
            // If the meeting starts at or after the earliest ending meeting
            if (starts[startPtr] >= ends[endPtr]) {
                // Reuse the room, so advance the end pointer
                endPtr++;
            } else {
                // Overlap occurs, allocate a new room
                rooms++;
            }
        }

        return rooms;
    }
};
```

---

## Detailed Solution (Python)

### Standard Python Production Code

Below is the type-hinted Python implementation using the two-pointer separate-sorting algorithm.

```python
from typing import List

class Solution:
    def minMeetingRooms(self, intervals: List[List[int]]) -> int:
        """
        Calculates the minimum conference rooms required using two-pointer sorting.
        
        Time Complexity: O(N log N)
        Space Complexity: O(N)
        """
        if not intervals:
            return 0

        # Extract and sort start/end times independently
        starts = sorted(interval[0] for interval in intervals)
        ends = sorted(interval[1] for interval in intervals)

        rooms = 0
        end_ptr = 0

        for start in starts:
            # If the next meeting starts after the earliest active meeting ends
            if start >= ends[end_ptr]:
                # Reuse the room (advance the end pointer)
                end_ptr += 1
            else:
                # No room is free, allocate a new room
                rooms += 1

        return rooms
```

---

## Python-Specific Complexities & Implementation Considerations

### 1. Generator Expressions in `sorted`
*   In Python, `sorted(interval[0] for interval in intervals)` uses a generator expression to feed elements into the sorting algorithm.
*   This avoids creating an intermediate list of start times in memory before sorting, reducing memory allocation overhead.

### 2. Timsort Optimizations
*   Because Timsort runs in $\mathcal{O}(n \log n)$ time, sorting `starts` and `ends` separately is highly efficient. In cases where the input meetings are already chronological, `starts` will sort in $\mathcal{O}(n)$ time due to Timsort detecting pre-sorted segments.

---

## Complexity Analysis

| Metric | Complexity | Description |
| :--- | :--- | :--- |
| **Time Complexity** | $\mathcal{O}(n \log n)$ | Sorting the `starts` and `ends` arrays takes $\mathcal{O}(n \log n)$ time. The subsequent two-pointer scan takes linear $\mathcal{O}(n)$ time. |
| **Space Complexity** | $\mathcal{O}(n)$ | We allocate two arrays of size $n$ to hold the start and end times. |

---

## Common Follow-Up Questions & How to Answer

### Q1: How does this Two-Pointer approach compare to a Heap-based solution?
*   **The Answer**:
    *   **Min-Heap Approach**: We sort the intervals by start time, and push the end times of active meetings into a min-heap. For each new meeting, we pop from the heap if its start time $\ge$ the top of the heap, then push its end time. The maximum size of the heap is the answer.
    *   **Comparison**: 
        *   *Time Complexity*: Both are $\mathcal{O}(n \log n)$. However, the heap approach does $\mathcal{O}(n \log k)$ heap operations (where $k$ is the room count).
        *   *Memory/Cache*: The two-pointer approach sorted array scan has superior cache locality because it traverses contiguous arrays sequentially. Heap operations, on the other hand, require pointer hopping across nodes, resulting in cache misses.
        *   *Streaming Advantage*: If intervals arrive as a stream in real-time, the Min-Heap is superior because we do not need to re-sort arrays; we just insert/extract from the heap in $\mathcal{O}(\log k)$ time per event.

### Q2: How would you solve this using a Prefix Sum / Event-Based Sweep Line?
*   **The Answer**: We can represent each start as a `+1` event and each end as a `-1` event.
    *   Create a list of pairs `(time, event_type)` where `event_type = 1` for start and `-1` for end.
    *   Sort the list. **Crucial rule**: If two times are equal, sort the end event (`-1`) *before* the start event (`+1`) so we don't count an extra room for contiguous meetings.
    *   Traverse the sorted events and maintain a running prefix sum of active rooms. The maximum value of this sum is the answer.

---

## Pro-Tip: How to Impress the Interviewer

*   **Reserve Vector Capacity**: In C++, always write `starts.reserve(n)` and `ends.reserve(n)`. This signals to the interviewer that you understand vector growth mechanics and want to avoid the performance cost of multiple dynamic reallocations.
*   **Cache Locality and Memory Alignment**: Highlight that separating intervals into two primitive `std::vector<int>` arrays (`starts` and `ends`) is far more cache-friendly than sorting `std::vector<std::vector<int>>` or `std::vector<std::pair<int, int>>` because it keeps primitive integers aligned contiguously in the CPU cache lines.
