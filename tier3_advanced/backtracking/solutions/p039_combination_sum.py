"""
P39: Combination Sum (Medium)
https://leetcode.com/problems/combination-sum/
Topics: Array, Backtracking

Given an array of distinct integers candidates and a target integer target, return a list of all unique combinations of candidates where the chosen numbers sum to target. You may return the combinations in any order.
The same number may be chosen from candidates an unlimited number of times. Two combinations are unique if the frequency of at least one of the chosen numbers is different.
The test cases are generated such that the number of unique combinations that sum up to target is less than 150 combinations for the given input.

Example 1:
    Input: candidates = [2,3,6,7], target = 7
    Output: [[2,2,3],[7]]
    Explanation:
    2 and 3 are candidates, and 2 + 2 + 3 = 7. Note that 2 can be used multiple times.
    7 is a candidate, and 7 = 7.
    These are the only two combinations.

Example 2:
    Input: candidates = [2,3,5], target = 8
    Output: [[2,2,2,2],[2,3,3],[3,5]]

Example 3:
    Input: candidates = [2], target = 1
    Output: []

Constraints:
    - 1 <= candidates.length <= 30
    - 2 <= candidates[i] <= 40
    - All elements of candidates are distinct.
    - 1 <= target <= 40

Template (python3):
    class Solution:
        def combinationSum(self, candidates: List[int], target: int) -> List[List[int]]:

Hint: Use backtracking with early pruning when the remaining sum goes negative.
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "39. Combination Sum"
    test_cases = [
        TestCase(input=([2, 3, 6, 7], 7), expected=[[2, 2, 3], [7]], label="example 1"),
        TestCase(
            input=([2, 3, 5], 8),
            expected=[[2, 2, 2, 2], [2, 3, 3], [3, 5]],
            label="example 2",
        ),
        TestCase(input=([2], 1), expected=[], label="no solution"),
        TestCase(input=([5], 5), expected=[[5]], label="single candidate equals target"),
        TestCase(input=([2], 4), expected=[[2, 2]], label="reuse single candidate"),
        TestCase(
            input=([8, 7, 4, 3], 11),
            expected=[[3, 4, 4], [3, 8], [4, 7]],
            label="unsorted candidates multiple combos",
        ),
        TestCase(input=([3, 5], 7), expected=[], label="no valid combination"),
        TestCase(input=([3], 9), expected=[[3, 3, 3]], label="triple reuse"),
    ]

    def solve(self, candidates: list[int], target: int) -> list[list[int]]:
        result: list[list[int]] = []
        candidates.sort()

        def backtrack(start: int, remaining: int, current: list[int]):
            if remaining == 0:
                result.append(current[:])
                return
            for i in range(start, len(candidates)):
                if candidates[i] > remaining:
                    break
                current.append(candidates[i])
                backtrack(i, remaining - candidates[i], current)
                current.pop()

        backtrack(0, target, [])
        return result


if __name__ == "__main__":
    Solution().run()
