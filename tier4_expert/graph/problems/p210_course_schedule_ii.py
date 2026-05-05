"""P210: Course Schedule II (Medium)

TODO: Implement solve() below.
Hint: Use Kahn's algorithm (topological sort with BFS) to produce a valid course order.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase
from collections import deque

class Solution(Problem):
    name = "210. Course Schedule II"
    test_cases = [
        TestCase(input=(2, [[1,0]]), expected=[0,1], label="example 1"),
        TestCase(input=(4, [[1,0],[2,0],[3,1],[3,2]]), expected=[0,1,2,3], label="example 2"),
        TestCase(input=(1, []), expected=[0], label="no prerequisites"),
    ]

    def solve(self, num_courses: int, prerequisites: list[list[int]]) -> list[int]:
        raise NotImplementedError("TODO: Implement solve(self, num_courses: int, prerequisites: list[list[int]]) -> list[int]")

if __name__ == "__main__":
    Solution().run()
