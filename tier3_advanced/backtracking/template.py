"""Backtracking template: three core variants.

Variant 1 -- Permutations: generate all orderings of a list.
Variant 2 -- Combinations: choose k items from n (no repeats, order doesn't matter).
Variant 3 -- Subsets: generate the power set (all possible subsets).
"""

from __future__ import annotations


def permute(nums: list[int]) -> list[list[int]]:
    """Variant 1: Generate all permutations of *nums* (swapping approach).

    Time:  O(n * n!)
    Space: O(n) recursion depth
    """
    result: list[list[int]] = []

    def backtrack(first: int = 0) -> None:
        if first == len(nums):
            result.append(nums[:])
            return
        for i in range(first, len(nums)):
            nums[first], nums[i] = nums[i], nums[first]
            backtrack(first + 1)
            nums[first], nums[i] = nums[i], nums[first]

    backtrack()
    return result


def combine(n: int, k: int) -> list[list[int]]:
    """Variant 2: Choose k numbers from [1..n] (combinations).

    Time:  O(C(n, k) * k)
    Space: O(k) recursion depth
    """
    result: list[list[int]] = []

    def backtrack(start: int, current: list[int]) -> None:
        if len(current) == k:
            result.append(current[:])
            return
        # Optimization: stop early when not enough remaining numbers
        for i in range(start, n + 1):
            current.append(i)
            backtrack(i + 1, current)
            current.pop()

    backtrack(1, [])
    return result


def subsets(nums: list[int]) -> list[list[int]]:
    """Variant 3: Generate all subsets of *nums* (the power set).

    Time:  O(n * 2^n)
    Space: O(n) recursion depth
    """
    result: list[list[int]] = []

    def backtrack(start: int, current: list[int]) -> None:
        result.append(current[:])
        for i in range(start, len(nums)):
            current.append(nums[i])
            backtrack(i + 1, current)
            current.pop()

    backtrack(0, [])
    return result
