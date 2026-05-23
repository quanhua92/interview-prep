"""
P135: Candy (Hard)
https://leetcode.com/problems/candy/
Topics: Array, Greedy

There are n children standing in a line. Each child is assigned a rating value given in the integer array ratings.
You are giving candies to these children subjected to the following requirements:
Return the minimum number of candies you need to have to distribute the candies to the children.

Example 1:
    Input: ratings = [1,0,2]
    Output: 5
    Explanation: You can allocate to the first, second and third child with 2, 1, 2 candies respectively.

Example 2:
    Input: ratings = [1,2,2]
    Output: 4
    Explanation: You can allocate to the first, second and third child with 1, 2, 1 candies respectively.
    The third child gets 1 candy because it satisfies the above two conditions.

Constraints:
    - n == ratings.length
    - 1 <= n <= 2 * 104
    - 0 <= ratings[i] <= 2 * 104

Template (python3):
    class Solution:
        def candy(self, ratings: List[int]) -> int:

Hint: Two-pass greedy: left-to-right then right-to-left, taking the max of both passes.
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "135. Candy"
    test_cases = [
        TestCase(input=[1, 0, 2], expected=5, label="example 1"),
        TestCase(input=[1, 2, 2], expected=4, label="example 2"),
        TestCase(input=[1, 3, 2, 2, 1], expected=7, label="decreasing then flat"),
        TestCase(input=[1], expected=1, label="single child"),
        TestCase(input=[2, 2, 2, 2], expected=4, label="all same ratings"),
        TestCase(input=[1, 2, 3, 4], expected=10, label="strictly increasing"),
        TestCase(input=[4, 3, 2, 1], expected=10, label="strictly decreasing"),
        TestCase(input=[1, 3, 4, 5, 2], expected=11, label="increase then drop"),
    ]

    def solve(self, ratings: list[int]) -> int:
        raise NotImplementedError(
            "TODO: Implement solve(self, ratings: list[int]) -> int"
        )


if __name__ == "__main__":
    Solution().run()
