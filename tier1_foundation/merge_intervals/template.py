"""Merge Intervals pattern templates.

Three common variants of the merge intervals technique:

1. Merge overlapping intervals: Sort by start, merge contiguous overlaps.
2. Insert interval: Add a new interval into an already-sorted list.
3. Minimum meeting rooms: Count concurrent events using sorted start/end times.
"""


def merge_intervals(intervals: list[list[int]]) -> list[list[int]]:
    """Variant 1: Merge overlapping intervals.

    Given a collection of intervals, merge all overlapping intervals.
    Two intervals [a, b] and [c, d] overlap if c <= b.

    Time:  O(n log n) -- sorting dominates
    Space: O(n) -- output list (O(1) extra if we modify in-place)

    Args:
        intervals: List of [start, end] intervals.

    Returns:
        List of merged intervals with no overlaps.

    Example:
        >>> merge_intervals([[1,3],[2,6],[8,10],[15,18]])
        [[1, 6], [8, 10], [15, 18]]
    """
    if not intervals:
        return []

    intervals.sort(key=lambda x: x[0])
    merged: list[list[int]] = [intervals[0][:]]  # copy to avoid mutating input

    for start, end in intervals[1:]:
        last = merged[-1]
        if start <= last[1]:
            # Overlap: extend the end of the last merged interval
            last[1] = max(last[1], end)
        else:
            # No overlap: start a new interval
            merged.append([start, end])

    return merged


def insert_interval(intervals: list[list[int]], new_interval: list[int]) -> list[list[int]]:
    """Variant 2: Insert interval into a sorted list.

    Insert new_interval into intervals (already sorted by start time)
    and merge if necessary. Returns a new sorted list of intervals.

    Time:  O(n) -- single pass, no sort needed (already sorted)
    Space: O(n) -- output list

    Args:
        intervals: Sorted list of non-overlapping [start, end] intervals.
        new_interval: The interval to insert [start, end].

    Returns:
        New sorted list of non-overlapping intervals.

    Example:
        >>> insert_interval([[1,3],[6,9]], [2,5])
        [[1, 5], [6, 9]]
    """
    result: list[list[int]] = []
    i = 0
    n = len(intervals)

    # Add all intervals that end before new_interval starts
    while i < n and intervals[i][1] < new_interval[0]:
        result.append(intervals[i][:])
        i += 1

    # Merge all overlapping intervals with new_interval
    while i < n and intervals[i][0] <= new_interval[1]:
        new_interval[0] = min(new_interval[0], intervals[i][0])
        new_interval[1] = max(new_interval[1], intervals[i][1])
        i += 1
    result.append(new_interval[:])

    # Add the remaining intervals
    while i < n:
        result.append(intervals[i][:])
        i += 1

    return result


def min_meeting_rooms(intervals: list[list[int]]) -> int:
    """Variant 3: Minimum meeting rooms (sweep line).

    Given an array of meeting time intervals, find the minimum number
    of conference rooms required.

    Key insight: Instead of a full sweep line with events, we can sort
    start times and end times separately. For each start time, if it is
    before the earliest ending meeting, we need a new room. Otherwise,
    we can reuse a room (the earliest ending one frees up).

    Time:  O(n log n) -- sorting start and end times
    Space: O(n) -- sorted copies of start/end times

    Args:
        intervals: List of [start, end] meeting time intervals.

    Returns:
        Minimum number of conference rooms required.

    Example:
        >>> min_meeting_rooms([[0,30],[5,10],[15,20]])
        2
    """
    if not intervals:
        return 0

    starts = sorted(i[0] for i in intervals)
    ends = sorted(i[1] for i in intervals)

    rooms = 0
    end_ptr = 0

    for start in starts:
        # If the current meeting starts after the earliest ending meeting finishes,
        # we can reuse that room
        if start >= ends[end_ptr]:
            end_ptr += 1
        else:
            rooms += 1

    return rooms


if __name__ == "__main__":
    # Quick smoke tests
    assert merge_intervals([[1, 3], [2, 6], [8, 10], [15, 18]]) == [[1, 6], [8, 10], [15, 18]]
    assert merge_intervals([[1, 4], [4, 5]]) == [[1, 5]]

    assert insert_interval([[1, 3], [6, 9]], [2, 5]) == [[1, 5], [6, 9]]

    assert min_meeting_rooms([[0, 30], [5, 10], [15, 20]]) == 2
    assert min_meeting_rooms([[7, 10], [2, 4]]) == 1
    print("All template smoke tests passed.")
