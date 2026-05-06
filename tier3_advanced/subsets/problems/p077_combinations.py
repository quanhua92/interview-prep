"""
P77: Combinations (Medium)
https://leetcode.com/problems/combinations/
Topics: Backtracking

Given two integers n and k, return all possible combinations of k numbers chosen from the range [1, n].
You may return the answer in any order.

Example 1:
    Input: n = 4, k = 2
    Output: [[1,2],[1,3],[1,4],[2,3],[2,4],[3,4]]
    Explanation: There are 4 choose 2 = 6 total combinations.
    Note that combinations are unordered, i.e., [1,2] and [2,1] are considered to be the same combination.

Example 2:
    Input: n = 1, k = 1
    Output: [[1]]
    Explanation: There is 1 choose 1 = 1 total combination.

Constraints:
    - 1 <= n <= 20
    - 1 <= k <= n

Template (python3):
    class Solution:
        def combine(self, n: int, k: int) -> List[List[int]]:

Hint: Use backtracking with a start index to generate all k-length combinations from 1..n.
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "77. Combinations"
    test_cases = [
        TestCase(
            input=(4, 2),
            expected=[[1, 2], [1, 3], [1, 4], [2, 3], [2, 4], [3, 4]],
            label="example 1",
        ),
        TestCase(input=(1, 1), expected=[[1]], label="example 2"),
        TestCase(input=(3, 1), expected=[[1], [2], [3]], label="example 3"),
    ]

    def solve(self, n: int, k: int) -> list[list[int]]:
        raise NotImplementedError(
            "TODO: Implement solve(self, n: int, k: int) -> list[list[int]]"
        )


if __name__ == "__main__":
    Solution().run()
