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

Template (python3):
    class Solution:
        def makesquare(self, matchsticks: List[int]) -> bool:
"""

from src.wasm_libs.py.io import *


def solve(matchsticks: list[int]) -> bool:
    raise NotImplementedError


if __name__ == "__main__":
    matchsticks = read_ints()
    result = solve(matchsticks)
    write_bool(result)
