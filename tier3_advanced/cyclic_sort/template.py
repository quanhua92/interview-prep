"""Cyclic sort template: three core variants.

Variant 1 -- Cyclic sort: place each number at its correct index via swaps.
Variant 2 -- Find all numbers disappeared in an array.
Variant 3 -- Find the duplicate number (negation-marking approach).
"""

from __future__ import annotations


def cyclic_sort(nums: list[int]) -> list[int]:
    """Variant 1: Sort an array of 1..n in place.

    Time:  O(n)
    Space: O(1)
    """
    i = 0
    while i < len(nums):
        correct = nums[i] - 1
        if 0 <= correct < len(nums) and nums[i] != nums[correct]:
            nums[i], nums[correct] = nums[correct], nums[i]
        else:
            i += 1
    return nums


def find_disappeared_numbers(nums: list[int]) -> list[int]:
    """Variant 2: Find all numbers in [1..n] that are missing from *nums*.

    Uses the negation-marking trick: for each number x, mark index x-1 as
    visited by negating the value at that index.

    Time:  O(n)
    Space: O(1) extra (output list not counted)
    """
    for num in nums:
        idx = abs(num) - 1
        if nums[idx] > 0:
            nums[idx] = -nums[idx]

    result: list[int] = []
    for i in range(len(nums)):
        if nums[i] > 0:
            result.append(i + 1)
    return result


def find_duplicate(nums: list[int]) -> int:
    """Variant 3: Find the duplicate number in [1..n] with exactly one duplicate.

    Uses the negation-marking approach: the first index we encounter that is
    already negative reveals the duplicate.

    Time:  O(n)
    Space: O(1)
    """
    for num in nums:
        idx = abs(num) - 1
        if nums[idx] < 0:
            return abs(num)
        nums[idx] = -nums[idx]
    return -1  # should never reach here given problem constraints
