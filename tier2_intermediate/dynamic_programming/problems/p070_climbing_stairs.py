"""
P70: Climbing Stairs (Easy)
https://leetcode.com/problems/climbing-stairs/
Topics: Math, Dynamic Programming, Memoization

You are climbing a staircase. It takes n steps to reach the top.
Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?

Example 1:
    Input: n = 2
    Output: 2
    Explanation: There are two ways to climb to the top.
    1. 1 step + 1 step
    2. 2 steps

Example 2:
    Input: n = 3
    Output: 3
    Explanation: There are three ways to climb to the top.
    1. 1 step + 1 step + 1 step
    2. 1 step + 2 steps
    3. 2 steps + 1 step

Constraints:
    - 1 <= n <= 45

Hints:
    - To reach nth step, what could have been your previous steps? (Think about the step sizes)

Template (python3):
    class Solution:
        def climbStairs(self, n: int) -> int:

Hint: This is essentially Fibonacci -- each step depends on the two before it.
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "70. Climbing Stairs"
    test_cases = [
        TestCase(input=2, expected=2, label="example 1"),
        TestCase(input=3, expected=3, label="example 2"),
        TestCase(input=1, expected=1, label="base case"),
        TestCase(input=10, expected=89, label="larger"),
        TestCase(input=45, expected=1836311903, label="max constraint"),
        TestCase(input=4, expected=5, label="n=4"),
        TestCase(input=5, expected=8, label="n=5"),
        TestCase(input=6, expected=13, label="n=6"),
        TestCase(input=20, expected=10946, label="n=20"),
        TestCase(input=44, expected=1134903170, label="near max constraint"),
    ]

    def solve(self, n: int) -> int:
        raise NotImplementedError("TODO: Implement solve(self, n: int) -> int")


if __name__ == "__main__":
    Solution().run()
