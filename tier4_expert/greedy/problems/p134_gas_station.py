"""P134: Gas Station (Medium)

TODO: Implement solve() below.
Hint: Track total_surplus and current_surplus. If current_surplus < 0, reset start to next station.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "134. Gas Station"
    test_cases = [
        TestCase(input=([1,2,3,4,5], [3,4,5,1,2]), expected=3, label="example 1"),
        TestCase(input=([2,3,4], [3,4,3]), expected=-1, label="example 2"),
        TestCase(input=([5,1,2,3,4], [4,4,1,5,1]), expected=4, label="example 3"),
    ]

    def solve(self, gas: list[int], cost: list[int]) -> int:
        raise NotImplementedError("TODO: Implement solve(self, gas: list[int], cost: list[int]) -> int")


if __name__ == "__main__":
    Solution().run()
