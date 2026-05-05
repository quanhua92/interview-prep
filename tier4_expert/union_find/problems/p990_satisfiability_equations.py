"""P990: Satisfiability of Equality Equations (Medium)

TODO: Implement solve() below.
Hint: Union-Find with 26 variables (map char to 0-25). First pass: union all "==". Second pass: check "!=" for contradiction.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "990. Satisfiability of Equality Equations"
    test_cases = [
        TestCase(input=["a==b","b!=a"], expected=False, label="example 1"),
        TestCase(input=["b==a","a==b"], expected=True, label="example 2"),
        TestCase(input=["a==b","b==c","a==c"], expected=True, label="example 3"),
        TestCase(input=["a!=a"], expected=False, label="contradiction"),
    ]

    def solve(self, equations: list[str]) -> bool:
        raise NotImplementedError("TODO: Implement solve(self, equations: list[str]) -> bool")


if __name__ == "__main__":
    Solution().run()
