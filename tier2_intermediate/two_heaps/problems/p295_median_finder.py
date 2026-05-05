"""P295: Find Median from Data Stream (Hard)

TODO: Implement solve() below.
Hint: Use a max-heap for the lower half and a min-heap for the upper half.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase
import heapq

class Solution(Problem):
    name = "295. Find Median from Data Stream"
    test_cases = [
        TestCase(input=([5,15,1,3], "median"), expected=[5.0, 10.0, 5.0, 4.0], label="stream median"),
        TestCase(input=([1,2], "median"), expected=[1.0, 1.5], label="two elements"),
    ]

    def solve(self, stream: list[int], _unused: str) -> list[float]:
        raise NotImplementedError("TODO: Implement solve(self, stream: list[int], _unused: str) -> list[float]")

if __name__ == "__main__":
    Solution().run()
