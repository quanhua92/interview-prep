"""Subsets / Permutations / Combinations template: three core variants.

Variant 1 -- Subsets via BFS: iteratively extend existing subsets.
Variant 2 -- Permutations via swapping: generate all orderings.
Variant 3 -- Letter combinations of a phone number: digit-to-letter mapping + backtracking.
"""

from __future__ import annotations


def subsets_bfs(nums: list[int]) -> list[list[int]]:
    """Variant 1: Generate all subsets using BFS (iterative duplication).

    Start with [[]]. For each number, duplicate every existing subset and
    append the number to the copy.

    Time:  O(n * 2^n)
    Space: O(n * 2^n) for the output
    """
    result: list[list[int]] = [[]]
    for num in nums:
        result += [curr + [num] for curr in result]
    return result


def permutations_swap(nums: list[int]) -> list[list[int]]:
    """Variant 2: Generate all permutations using the swapping approach.

    Place each element at position `first` by swapping, then recurse.

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


def letter_combinations(digits: str) -> list[str]:
    """Variant 3: Letter combinations of a phone number.

    Map each digit to its letters, then build all combinations via backtracking.

    Time:  O(4^n * n) where n = len(digits) (worst case: all 7 or 9)
    Space: O(n) recursion depth
    """
    if not digits:
        return []

    mapping: dict[str, str] = {
        "2": "abc",
        "3": "def",
        "4": "ghi",
        "5": "jkl",
        "6": "mno",
        "7": "pqrs",
        "8": "tuv",
        "9": "wxyz",
    }
    result: list[str] = []

    def backtrack(index: int, current: list[str]) -> None:
        if index == len(digits):
            result.append("".join(current))
            return
        for ch in mapping[digits[index]]:
            current.append(ch)
            backtrack(index + 1, current)
            current.pop()

    backtrack(0, [])
    return result


def subsets_with_dup(nums: list[int]) -> list[list[int]]:
    """Bonus: Subsets with duplicate elements (sorted, skip duplicates).

    Time:  O(n * 2^n)
    Space: O(n) recursion depth
    """
    result: list[list[int]] = []
    nums.sort()

    def backtrack(start: int, current: list[int]) -> None:
        result.append(current[:])
        for i in range(start, len(nums)):
            if i > start and nums[i] == nums[i - 1]:
                continue
            current.append(nums[i])
            backtrack(i + 1, current)
            current.pop()

    backtrack(0, [])
    return result
