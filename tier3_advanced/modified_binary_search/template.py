"""Modified binary search template: three core variants.

Variant 1 -- Search in rotated sorted array.
Variant 2 -- Find peak element.
Variant 3 -- Binary search on answer (monotonic predicate).
"""

from __future__ import annotations
from typing import Callable


def search_rotated(nums: list[int], target: int) -> int:
    """Variant 1: Find *target* in a rotated sorted array.

    Time:  O(log n)
    Space: O(1)

    The array is sorted but rotated at some unknown pivot.  Determine which
    half is properly sorted and whether the target lies inside it.
    """
    left, right = 0, len(nums) - 1
    while left <= right:
        mid = left + (right - left) // 2
        if nums[mid] == target:
            return mid
        # Left half is sorted
        if nums[left] <= nums[mid]:
            if nums[left] <= target < nums[mid]:
                right = mid - 1
            else:
                left = mid + 1
        # Right half is sorted
        else:
            if nums[mid] < target <= nums[right]:
                left = mid + 1
            else:
                right = mid - 1
    return -1


def find_peak(nums: list[int]) -> int:
    """Variant 2: Find a peak element (any peak is fine).

    A peak element is an element that is strictly greater than its neighbors.
    For edge elements, only compare with the single neighbor.

    Time:  O(log n)
    Space: O(1)
    """
    left, right = 0, len(nums) - 1
    while left < right:
        mid = left + (right - left) // 2
        if nums[mid] > nums[mid + 1]:
            # We are on the descending slope; peak is to the left (or at mid).
            right = mid
        else:
            # We are on the ascending slope; peak is to the right.
            left = mid + 1
    return left


def binary_search_on_answer(
    low: int,
    high: int,
    feasible: Callable[[int], bool],
) -> int:
    """Variant 3: Binary search on the answer space.

    *feasible(k)* must be a monotonic predicate: if k works, then any
    larger value also works (or the reverse).  This template assumes the
    "find minimum feasible" pattern.

    Time:  O(log(high - low) * cost_of_feasible)
    Space: O(1)
    """
    while low < high:
        mid = low + (high - low) // 2
        if feasible(mid):
            high = mid
        else:
            low = mid + 1
    return low
