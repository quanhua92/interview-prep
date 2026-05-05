"""Binary Search — 3 Variants

Variant 1: Standard binary search
Variant 2: Leftmost binary search (lower bound)
Variant 3: Binary search on rotated sorted array
"""

from __future__ import annotations

from typing import Any


# ---------------------------------------------------------------------------
# Variant 1: Standard binary search
# ---------------------------------------------------------------------------

def binary_search(nums: list[int], target: int) -> int:
    """Find *target* in a sorted list using standard binary search.

    Args:
        nums: Sorted list of integers (ascending, no duplicates assumed).
        target: Value to locate.

    Returns:
        Index of *target* if found, otherwise ``-1``.
    """
    left: int = 0
    right: int = len(nums) - 1

    while left <= right:
        mid = left + (right - left) // 2
        if nums[mid] == target:
            return mid
        elif nums[mid] < target:
            left = mid + 1
        else:
            right = mid - 1

    return -1


# ---------------------------------------------------------------------------
# Variant 2: Leftmost binary search (lower bound)
# ---------------------------------------------------------------------------

def binary_search_leftmost(nums: list[int], target: int) -> int:
    """Return the **leftmost** index at which *target* appears.

    If *target* is not present, returns the index where it would be inserted
    to maintain sorted order (i.e. the lower bound).

    Args:
        nums: Sorted list of integers (ascending, may contain duplicates).
        target: Value to locate.

    Returns:
        The leftmost index of *target*, or the insertion point if absent.
    """
    left: int = 0
    right: int = len(nums)

    while left < right:
        mid = left + (right - left) // 2
        if nums[mid] < target:
            left = mid + 1
        else:
            right = mid

    return left


# ---------------------------------------------------------------------------
# Variant 3: Binary search on rotated sorted array
# ---------------------------------------------------------------------------

def binary_search_rotated_min(nums: list[int]) -> int:
    """Find the minimum element in a rotated sorted array.

    The array was originally sorted in ascending order, then rotated an
    unknown number of positions.  All elements are unique.

    Args:
        nums: Rotated sorted list of unique integers.

    Returns:
        The minimum element value.
    """
    left: int = 0
    right: int = len(nums) - 1

    while left < right:
        mid = left + (right - left) // 2
        if nums[mid] > nums[right]:
            # The pivot (minimum) is to the right of mid.
            left = mid + 1
        else:
            # The pivot is at mid or to the left.
            right = mid

    return nums[left]


def binary_search_rotated(nums: list[int], target: int) -> int:
    """Search *target* in a rotated sorted array.

    Args:
        nums: Rotated sorted list of unique integers.
        target: Value to locate.

    Returns:
        Index of *target* if found, otherwise ``-1``.
    """
    left: int = 0
    right: int = len(nums) - 1

    while left <= right:
        mid = left + (right - left) // 2
        if nums[mid] == target:
            return mid

        # Determine which half is properly sorted.
        if nums[left] <= nums[mid]:
            # Left half is sorted.
            if nums[left] <= target < nums[mid]:
                right = mid - 1
            else:
                left = mid + 1
        else:
            # Right half is sorted.
            if nums[mid] < target <= nums[right]:
                left = mid + 1
            else:
                right = mid - 1

    return -1
