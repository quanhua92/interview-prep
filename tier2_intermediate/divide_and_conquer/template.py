"""Divide & Conquer — 3 Variants

Variant 1: Merge sort (divide, sort halves, merge)
Variant 2: Majority element via Boyer-Moore voting
Variant 3: Merge k sorted lists via divide & conquer
"""

from __future__ import annotations

from typing import Any


# ---------------------------------------------------------------------------
# Variant 1: Merge sort
# ---------------------------------------------------------------------------

def merge_sort(nums: list[int]) -> list[int]:
    """Sort an array using merge sort (divide & conquer).

    Time: O(n log n), Space: O(n)

    Args:
        nums: Input list of integers.

    Returns:
        Sorted list of integers.
    """
    if len(nums) <= 1:
        return nums[:]

    mid = len(nums) // 2
    left = merge_sort(nums[:mid])
    right = merge_sort(nums[mid:])

    # Merge
    result: list[int] = []
    i = j = 0
    while i < len(left) and j < len(right):
        if left[i] <= right[j]:
            result.append(left[i])
            i += 1
        else:
            result.append(right[j])
            j += 1
    result.extend(left[i:])
    result.extend(right[j:])
    return result


# ---------------------------------------------------------------------------
# Variant 2: Majority element (Boyer-Moore voting)
# ---------------------------------------------------------------------------

def majority_element(nums: list[int]) -> int:
    """Find the majority element (appears more than n/2 times).

    Uses Boyer-Moore voting algorithm: O(n) time, O(1) space.

    Args:
        nums: Non-empty list of integers with a guaranteed majority element.

    Returns:
        The majority element.
    """
    candidate: int = nums[0]
    count: int = 1
    for num in nums[1:]:
        if count == 0:
            candidate = num
            count = 1
        elif num == candidate:
            count += 1
        else:
            count -= 1
    return candidate


# ---------------------------------------------------------------------------
# Variant 3: Merge k sorted lists (simplified with lists)
# ---------------------------------------------------------------------------

def merge_k_sorted_lists(lists: list[list[int]]) -> list[int]:
    """Merge k sorted lists into one sorted list using divide & conquer.

    Time: O(n log k) where n is total elements, k is number of lists.
    Space: O(n) for the result.

    Args:
        lists: List of sorted integer lists.

    Returns:
        Single sorted list containing all elements.
    """
    if not lists:
        return []
    if len(lists) == 1:
        return lists[0][:]

    mid = len(lists) // 2
    left = merge_k_sorted_lists(lists[:mid])
    right = merge_k_sorted_lists(lists[mid:])

    # Merge two sorted lists
    result: list[int] = []
    i = j = 0
    while i < len(left) and j < len(right):
        if left[i] <= right[j]:
            result.append(left[i])
            i += 1
        else:
            result.append(right[j])
            j += 1
    result.extend(left[i:])
    result.extend(right[j:])
    return result
