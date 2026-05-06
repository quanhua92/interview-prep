"""
P990: Satisfiability of Equality Equations (Medium)
https://leetcode.com/problems/satisfiability-of-equality-equations/
Topics: Array, String, Union Find, Graph

You are given an array of strings equations that represent relationships between variables where each string equations[i] is of length 4 and takes one of two different forms: "xi==yi" or "xi!=yi".Here, xi and yi are lowercase letters (not necessarily different) that represent one-letter variable names.
Return true if it is possible to assign integers to variable names so as to satisfy all the given equations, or false otherwise.

Example 1:
    Input: equations = ["a==b","b!=a"]
    Output: false
    Explanation: If we assign say, a = 1 and b = 1, then the first equation is satisfied, but not the second.
    There is no way to assign the variables to satisfy both equations.

Example 2:
    Input: equations = ["b==a","a==b"]
    Output: true
    Explanation: We could assign a = 1 and b = 1 to satisfy both equations.

Constraints:
    - 1 <= equations.length <= 500
    - equations[i].length == 4
    - equations[i][0] is a lowercase letter.
    - equations[i][1] is either '=' or '!'.
    - equations[i][2] is '='.
    - equations[i][3] is a lowercase letter.

Template (python3):
    class Solution:
        def equationsPossible(self, equations: List[str]) -> bool:

Hint: Union-Find with 26 variables (map char to 0-25). First pass: union all "==". Second pass: check "!=" for contradiction.
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "990. Satisfiability of Equality Equations"
    test_cases = [
        TestCase(input=["a==b", "b!=a"], expected=False, label="example 1"),
        TestCase(input=["b==a", "a==b"], expected=True, label="example 2"),
        TestCase(input=["a==b", "b==c", "a==c"], expected=True, label="example 3"),
        TestCase(input=["a!=a"], expected=False, label="contradiction"),
    ]

    def solve(self, equations: list[str]) -> bool:
        raise NotImplementedError(
            "TODO: Implement solve(self, equations: list[str]) -> bool"
        )


if __name__ == "__main__":
    Solution().run()
