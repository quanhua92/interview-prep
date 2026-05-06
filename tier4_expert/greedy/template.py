"""Greedy algorithm template with three variants.

Variant 1: Jump game — can we reach the end?
Variant 2: Activity selection / interval scheduling
Variant 3: Gas station — find the starting station
"""


# ── Variant 1: Jump game (can we reach the end?) ─────────────────────────────


def jump_game(nums: list[int]) -> bool:
    """Determine if you can reach the last index.

    Greedy: track the farthest index reachable at each position.
    If the current index exceeds the farthest reachable, return False.

    Time: O(n), Space: O(1)
    """
    max_reach: int = 0
    for i, jump in enumerate(nums):
        if i > max_reach:
            return False
        max_reach = max(max_reach, i + jump)
    return True


# ── Variant 2: Activity selection / interval scheduling ──────────────────────


def activity_selection(intervals: list[tuple[int, int]]) -> int:
    """Find the maximum number of non-overlapping intervals.

    Greedy: sort by end time, always pick the interval that ends earliest.
    This leaves the most room for remaining intervals.

    Time: O(n log n), Space: O(1)
    """
    if not intervals:
        return 0
    intervals.sort(key=lambda x: x[1])
    count: int = 1
    last_end: int = intervals[0][1]
    for start, end in intervals[1:]:
        if start >= last_end:
            count += 1
            last_end = end
    return count


# ── Variant 3: Gas station ──────────────────────────────────────────────────


def gas_station(gas: list[int], cost: list[int]) -> int:
    """Find the starting gas station index to complete the circuit.

    Greedy: if total gas < total cost, no solution exists.
    Otherwise, track the running deficit. When deficit exceeds current surplus,
    reset the starting station. The first valid start is guaranteed to work.

    Time: O(n), Space: O(1)
    """
    total_surplus: int = 0
    current_surplus: int = 0
    start: int = 0

    for i in range(len(gas)):
        total_surplus += gas[i] - cost[i]
        current_surplus += gas[i] - cost[i]
        if current_surplus < 0:
            start = i + 1
            current_surplus = 0

    return start if total_surplus >= 0 else -1
