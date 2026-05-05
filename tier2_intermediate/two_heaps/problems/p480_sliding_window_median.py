"""P480: Sliding Window Median (Hard)

TODO: Implement solve() below.
Hint: Use a max-heap for the small half and a min-heap for the large half with lazy deletion.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "480. Sliding Window Median"
    test_cases = [
        TestCase(input=([1,3,-1,-3,5,3,6,7], 3), expected=[1.0,-1.0,-1.0,3.0,5.0,6.0], label="example 1"),
        TestCase(input=([1,2], 1), expected=[1.0,2.0], label="window size 1"),
    ]

    def solve(self, nums: list[int], k: int) -> list[float]:
        raise NotImplementedError("TODO: Implement solve(self, nums: list[int], k: int) -> list[float]")


if __name__ == "__main__":
    Solution().run()
