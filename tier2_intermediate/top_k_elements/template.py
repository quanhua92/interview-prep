"""Top-K Elements — 3 Variants

Variant 1: Kth largest with min-heap
Variant 2: Top K frequent elements
Variant 3: K closest points
"""

from __future__ import annotations

import heapq
from collections import Counter
from typing import Any


# ---------------------------------------------------------------------------
# Variant 1: Kth largest with min-heap
# ---------------------------------------------------------------------------

def kth_largest(nums: list[int], k: int) -> int:
    """Find the *k*-th largest element using a min-heap of size *k*.

    We maintain a min-heap that always holds the *k* largest elements seen so
    far.  The root of this heap (``heap[0]``) is the k-th largest overall.

    Args:
        nums: List of integers.
        k: 1-based ordinal (k=1 returns the maximum).

    Returns:
        The k-th largest element.
    """
    if k < 1 or k > len(nums):
        raise ValueError(f"k={k} is out of bounds for list of length {len(nums)}")

    min_heap: list[int] = []
    for num in nums:
        heapq.heappush(min_heap, num)
        if len(min_heap) > k:
            heapq.heappop(min_heap)  # remove the smallest of the top-k
    return min_heap[0]


def top_k(nums: list[int], k: int) -> int:
    """Alias for :func:`kth_largest`.

    Provided as the default import from ``__init__.py``.
    """
    return kth_largest(nums, k)


# ---------------------------------------------------------------------------
# Variant 2: Top K frequent elements
# ---------------------------------------------------------------------------

def top_k_frequent(nums: list[int], k: int) -> list[int]:
    """Return the *k* most frequent elements.

    Args:
        nums: List of integers (may contain duplicates).
        k: Number of most-frequent elements to return.

    Returns:
        List of the k most frequent elements in any order.
    """
    count: Counter = Counter(nums)
    # ``heapq.nlargest`` is O(n log k) internally.
    return [
        item
        for item, _ in heapq.nlargest(k, count.items(), key=lambda x: x[1])
    ]


# ---------------------------------------------------------------------------
# Variant 3: K closest points to origin
# ---------------------------------------------------------------------------

def k_closest_points(
    points: list[tuple[int, int]],
    k: int,
) -> list[tuple[int, int]]:
    """Return the *k* points closest to the origin (0, 0).

    Uses a max-heap of size *k* so that the farthest point is always evicted
    when the heap exceeds capacity.

    Args:
        points: List of (x, y) integer tuples.
        k: Number of closest points to return.

    Returns:
        List of k closest points.
    """
    # Max-heap via negated distance: (-dist_sq, idx)
    max_heap: list[tuple[int, int]] = []

    for idx, (x, y) in enumerate(points):
        dist_sq = x * x + y * y
        heapq.heappush(max_heap, (-dist_sq, idx))
        if len(max_heap) > k:
            heapq.heappop(max_heap)

    return [points[idx] for _, idx in max_heap]
