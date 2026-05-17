# Merge Intervals Pattern — Discussion

Source: [Interval Patterns: Merge Intervals, Meeting Rooms & Sweep Line (CalibreOS)](https://www.calibreos.com/learn/dsa-intervals)

## One-Liner
Sort intervals by start time, then scan left to right making greedy merge decisions — the universal setup for all interval problems.

## Recognition Signals
- "intervals", "overlapping", "meeting rooms", "schedule"
- "merge", "insert and merge", "minimum resources"
- "free slots", "calendar", "conflict"

## The Universal Setup
1. Sort intervals by start time (almost always step 1)
2. Scan left to right and make locally optimal decisions (compare current interval's end with the next interval's start) that are globally optimal
3. After sorting, you only need to compare each interval with the last merged one — never look back further

## Why Sorting Works (Key Insight)
If interval A does not overlap with interval B, and B does not overlap with interval C, then A cannot overlap with C (given sorted start times). This transitivity property is what makes the single-scan greedy approach correct.

## Core Templates

### 1. Merge Overlapping Intervals
```python
def merge(intervals: list[list[int]]) -> list[list[int]]:
    intervals.sort(key=lambda x: x[0])   # sort by start
    merged = [intervals[0]]
    for start, end in intervals[1:]:
        if start <= merged[-1][1]:         # overlaps with last merged
            merged[-1][1] = max(merged[-1][1], end)
        else:
            merged.append([start, end])
    return merged
# O(n log n) time, O(n) space (for output)
```

### 2. Minimum Meeting Rooms (Sweep Line)
```python
def min_meeting_rooms(intervals: list[list[int]]) -> int:
    events = []
    for start, end in intervals:
        events.append((start, 1))    # meeting starts: +1
        events.append((end, -1))     # meeting ends: -1
    events.sort(key=lambda x: (x[0], x[1]))  # sort by time; -1 before +1 at same time
    rooms = max_rooms = 0
    for _, delta in events:
        rooms += delta
        max_rooms = max(max_rooms, rooms)
    return max_rooms
# O(n log n) time, O(n) space
```

### 3. Insert Interval (into sorted non-overlapping list)
```python
def insert(intervals: list[list[int]], new: list[int]) -> list[list[int]]:
    result = []
    i, n = 0, len(intervals)
    # 1. Add all intervals ending before new starts
    while i < n and intervals[i][1] < new[0]:
        result.append(intervals[i]); i += 1
    # 2. Merge all overlapping intervals into new
    while i < n and intervals[i][0] <= new[1]:
        new[0] = min(new[0], intervals[i][0])
        new[1] = max(new[1], intervals[i][1])
        i += 1
    result.append(new)
    # 3. Add remaining
    result.extend(intervals[i:])
    return result
# O(n) time (no sort needed, already sorted)
```

### 4. Minimum Meeting Rooms (Heap Approach)
```python
import heapq
def min_meeting_rooms_heap(intervals: list[list[int]]) -> int:
    intervals.sort(key=lambda x: x[0])
    heap = []  # stores end times of active meetings
    for start, end in intervals:
        if heap and heap[0] <= start:   # earliest-ending room is free
            heapq.heapreplace(heap, end)
        else:
            heapq.heappush(heap, end)   # need a new room
    return len(heap)
# O(n log n), n heap operations each O(log n)
```

## Two Template Types
- **Type 1 (Merge/Count overlaps):** Sort by start, scan with running merge state.
- **Type 2 (Minimum resources / Meeting Rooms):** Sweep line with event points — convert each [s,e] into two events: (s, +1) and (e, -1). Sort all events; scan to find peak simultaneous count.

## Open vs Closed Interval Boundaries
- Critical: are intervals [s,e] closed (both endpoints inclusive) or half-open [s,e)?
- [1,2] and [2,3]: closed = overlap (share point 2), half-open = no overlap
- Closed intervals: `next.start <= current.end`
- Half-open intervals: `next.start < current.end`
- Problem statement dictates which convention to use

## Interval Problem Variants and Approach

| Problem | Key technique | Sort by | Complexity |
|---------|--------------|---------|------------|
| Merge overlapping intervals | Sort + scan with running merge | Start time | O(n log n) |
| Minimum meeting rooms | Sweep line (event points) or heap | Start time / event time | O(n log n) |
| Insert interval into sorted list | 3-phase scan (before / overlap / after) | Already sorted | O(n) |
| Find all free time slots | Merge all intervals, find gaps between merged | Start time | O(n log n) |
| Maximum overlap count at any point | Sweep line, track peak | Event time | O(n log n) |
| Interval scheduling maximization (max non-overlapping) | Greedy: sort by end time, greedily pick | End time | O(n log n) |
| Non-overlapping intervals to remove (min removals) | Greedy: same as scheduling max, remove the rest | End time | O(n log n) |

## Common Mistakes
1. **Forgetting to sort:** The sort step is mandatory. Even if the input looks sorted, sort defensively.
2. **Using current.end instead of max(current.end, next.end) for merging:** Nested intervals like [1,10] containing [2,9] need `max()` — otherwise the result gets truncated.
3. **Wrong tie-breaking in sweep line at same timestamp:** If a meeting ends at time 5 and another starts at time 5, sort events as `(time, delta)` with `-1` (end) before `+1` (start) for open endpoints.
4. **Interval scheduling: sorting by end (not start):** The "maximum number of non-overlapping intervals" problem sorts by END time (earliest deadline first), not start time. Sorting by start gives wrong answers for this variant.
5. **Off-by-one in overlap check:** Closed: `<=`, half-open: `<`. Always check the problem's definition of "touching" intervals.

## Edge Cases
- Empty input → `[]`
- Single interval → unchanged
- All intervals identical → one merged interval
- Completely non-overlapping → unchanged list
- Fully nested interval [1,10] contains [2,5] → result is [1,10] (max of ends handles nesting)

## Interview Communication Tips
- State the sort step immediately: "Interval problems almost always start with sorting by start time — this lets me scan left to right and make greedy decisions about merging."
- For meeting rooms: "Instead of comparing all pairs, I'll use a sweep line: convert each interval into a start (+1) and end (-1) event, sort all events by time, and track the running count. The peak is the answer."
- Draw the timeline for the interviewer — it makes the sweep line visible and shows spatial thinking.
