"""Two Heaps — 3 Variants

Variant 1: Running median with two heaps
Variant 2: Max of sliding window (heap approach)
Variant 3: K closest elements
"""

from __future__ import annotations

import heapq
from typing import Any


# ---------------------------------------------------------------------------
# Variant 1: Running median with two heaps
# ---------------------------------------------------------------------------

class MedianStream:
    """Maintain a running median over a stream of numbers using two heaps.

    - ``small`` is a **max-heap** (simulated via negated values) holding the
      smaller half of the numbers.
    - ``large`` is a **min-heap** holding the larger half.

    Invariant: ``len(small) >= len(large)`` and ``len(small) - len(large) <= 1``.
    """

    def __init__(self) -> None:
        self.small: list[int] = []  # max-heap (negated)
        self.large: list[int] = []  # min-heap

    def add_num(self, num: int) -> None:
        """Insert *num* while maintaining the size invariant."""
        heapq.heappush(self.small, -num)
        # Move the largest of small to large
        heapq.heappush(self.large, -heapq.heappop(self.small))
        # Rebalance: large must never exceed small in size
        if len(self.large) > len(self.small):
            heapq.heappush(self.small, -heapq.heappop(self.large))

    def median(self) -> float:
        """Return the current median.

        Returns:
            The median value.  If the total count is odd the median is the
            middle element; if even it is the average of the two middle
            elements.
        """
        if len(self.small) > len(self.large):
            return float(-self.small[0])
        return (-self.small[0] + self.large[0]) / 2.0


def median_stream(values: list[int]) -> list[float]:
    """Compute the running median for a sequence of numbers.

    Args:
        values: Stream of numeric values.

    Returns:
        List of medians after each insertion.
    """
    ms = MedianStream()
    medians: list[float] = []
    for v in values:
        ms.add_num(v)
        medians.append(ms.median())
    return medians


# ---------------------------------------------------------------------------
# Variant 2: Max of sliding window (heap approach)
# ---------------------------------------------------------------------------

def sliding_window_max(nums: list[int], k: int) -> list[int]:
    """Return the max of each sliding window of size *k* using a max-heap.

    Note: A monotonic deque gives O(n), but this variant demonstrates the
    heap-based approach for educational purposes (O(n log n)).

    Args:
        nums: Input list of integers.
        k: Size of the sliding window.

    Returns:
        List of maximum values for each window position.
    """
    if k <= 0 or not nums:
        return []

    # Max-heap entries: (-value, index)
    heap: list[tuple[int, int]] = []
    result: list[int] = []

    for i, num in enumerate(nums):
        heapq.heappush(heap, (-num, i))

        # Remove elements that are outside the current window
        while heap and heap[0][1] <= i - k:
            heapq.heappop(heap)

        if i >= k - 1:
            result.append(-heap[0][0])

    return result


# ---------------------------------------------------------------------------
# Variant 3: K closest elements
# ---------------------------------------------------------------------------

def k_closest_elements(
    arr: list[int],
    k: int,
    x: int,
) -> list[int]:
    """Find the *k* closest integers to *x* in *arr* using a max-heap.

    The heap keeps the k closest elements seen so far; when it exceeds size k
    the farthest element is removed.

    Args:
        arr: Sorted list of integers.
        k: Number of closest elements to return.
        x: Target value.

    Returns:
        The k closest elements, sorted in ascending order.
    """
    # Max-heap of (distance, -value) so that ties favour the smaller value
    # and the farthest element can be popped efficiently.
    heap: list[tuple[int, int]] = []

    for val in arr:
        dist = abs(val - x)
        heapq.heappush(heap, (-dist, -val))
        if len(heap) > k:
            heapq.heappop(heap)

    return sorted(-v for _, v in heap)
