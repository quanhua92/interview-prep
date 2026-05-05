"""P875: Koko Eating Bananas (Medium)

TODO: Implement solve() below.
Hint: Binary search on the eating speed, computing total hours for each candidate.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase
import math

class Solution(Problem):
    name = "875. Koko Eating Bananas"
    test_cases = [
        TestCase(input=([3,6,7,11], 8), expected=4, label="example 1"),
        TestCase(input=([30,11,23,4,20], 5), expected=30, label="example 2"),
        TestCase(input=([30,11,23,4,20], 6), expected=23, label="example 3"),
    ]

    def solve(self, piles: list[int], h: int) -> int:
        raise NotImplementedError("TODO: Implement solve(self, piles: list[int], h: int) -> int")

if __name__ == "__main__":
    Solution().run()
