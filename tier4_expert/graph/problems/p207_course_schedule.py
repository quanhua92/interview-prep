"""P207: Course Schedule (Medium)

TODO: Implement solve() below.
Hint: Build a graph and use topological sort (Kahn's algorithm) to detect cycles.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase
from collections import deque

class Solution(Problem):
    name = "207. Course Schedule"
    test_cases = [
        TestCase(input=(2, [[1,0]]), expected=True, label="example 1"),
        TestCase(input=(2, [[1,0],[0,1]]), expected=False, label="example 2"),
        TestCase(input=(1, []), expected=True, label="no prerequisites"),
    ]

    def solve(self, num_courses: int, prerequisites: list[list[int]]) -> bool:
        raise NotImplementedError("TODO: Implement solve(self, num_courses: int, prerequisites: list[list[int]]) -> bool")

if __name__ == "__main__":
    Solution().run()
