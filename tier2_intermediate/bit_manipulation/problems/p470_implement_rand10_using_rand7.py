"""
P470: Implement Rand10() Using Rand7() [PREMIUM] (Medium)
https://leetcode.com/problems/implement-rand10-using-rand7/
Topics: Math, Rejection Sampling, Randomized, Probability and Statistics

Given the API rand7() that generates a uniform random integer in the range [1, 7], write a function rand10() that generates a uniform random integer in the range [1, 10]. You can only call the API rand7(), and you shouldn't call any other API. Please do not use a language's built-in random API.
Each test case will have one internal argument n, the number of times that your implemented function rand10() will be called while testing. Note that this is not an argument passed to rand10().
Follow up:
Example 1:
    Input: n = 1
    Output: [2]

Example 2:
    Input: n = 2
    Output: [2,8]

Example 3:
    Input: n = 3
    Output: [3,8,10]

Constraints:
    - 1 <= n <= 105

Template (python3):
    # The rand7() API is already defined for you.
    # def rand7():
    # @return a random integer in the range 1 to 7

    class Solution:
        def rand10(self):
            '''
            :rtype: int
            '''
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase
from typing import Any


class Solution(Problem):
    name = "470. Implement Rand10() Using Rand7()"
    test_cases = [
        TestCase(input=1, expected=[2], label="example 1"),
        TestCase(input=2, expected=[2, 8], label="example 2"),
        TestCase(input=3, expected=[3, 8, 10], label="example 3"),
    ]

    def solve(self) -> Any:
        raise NotImplementedError("TODO: Implement solve(self) -> Any")


if __name__ == "__main__":
    Solution().run()
