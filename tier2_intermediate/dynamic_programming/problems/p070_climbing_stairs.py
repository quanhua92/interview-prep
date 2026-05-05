"""P070: Climbing Stairs (Easy)

TODO: Implement solve() below.
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
    ]

    def solve(self, n: int) -> int:
        raise NotImplementedError("TODO: Implement solve(self, n: int) -> int")

if __name__ == "__main__":
    Solution().run()
