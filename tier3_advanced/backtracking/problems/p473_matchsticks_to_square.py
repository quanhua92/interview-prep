"""
P473: Matchsticks to Square [PREMIUM] (Medium)
https://leetcode.com/problems/matchsticks-to-square/
Topics: Array, Dynamic Programming, Backtracking, Bit Manipulation, Bitmask

You are given an integer array matchsticks where matchsticks[i] is the length of the ith matchstick. You want to use all the matchsticks to make one square. You should not break any stick, but you can link them up, and each matchstick must be used exactly one time.
Return true if you can make this square and false otherwise.
Example 1:
    Input: matchsticks = [1,1,2,2,2]
    Output: true
    Explanation: You can form a square with length 2, one side of the square came two sticks with length 1.

Example 2:
    Input: matchsticks = [3,3,3,3,4]
    Output: false
    Explanation: You cannot find a way to form a square with all the matchsticks.

Constraints:
    - 1 <= matchsticks.length <= 15
    - 1 <= matchsticks[i] <= 108

Hint: Treat the matchsticks as an array. Can we split the array into 4 equal parts?
Hint: Every matchstick can belong to either of the 4 sides. We don't know which one. Maybe try out all options!
Hint: For every matchstick, we have to try out each of the 4 options i.e. which side it can belong to. We can make use of recursion for this.
Hint: We don't really need to keep track of which matchsticks belong to a particular side during recursion. We just need to keep track of the <b>length</b> of each of the 4 sides.
Hint: When all matchsticks have been used we simply need to see the length of all 4 sides. If they're equal, we have a square on our hands!

Template (python3):
    class Solution:
        def makesquare(self, matchsticks: List[int]) -> bool:
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "473. Matchsticks to Square"
    test_cases = [
        TestCase(input=[1, 1, 2, 2, 2], expected=True, label="example 1"),
        TestCase(input=[3, 3, 3, 3, 4], expected=False, label="example 2"),
        TestCase(input=[5, 5, 5, 5], expected=True, label="four equal sticks"),
        TestCase(input=[2, 2, 2, 2, 2, 2], expected=False, label="all twos cannot form square"),
        TestCase(input=[1, 1, 1, 1], expected=True, label="minimal square"),
        TestCase(input=[3, 3, 3, 3], expected=True, label="each stick one side"),
    ]

    def solve(self, matchsticks: list[int]) -> bool:
        raise NotImplementedError("TODO: Implement solve(self, matchsticks) -> bool")


if __name__ == "__main__":
    Solution().run()
