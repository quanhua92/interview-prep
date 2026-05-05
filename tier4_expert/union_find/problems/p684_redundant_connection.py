"""P684: Redundant Connection (Medium)

TODO: Implement solve() below.
Hint: Use Union-Find to detect the first edge that connects two already-connected nodes.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase

class Solution(Problem):
    name = "684. Redundant Connection"
    test_cases = [
        TestCase(input=[[1,2],[1,3],[2,3]], expected=[2,3], label="example 1"),
        TestCase(input=[[1,2],[2,3],[3,4],[1,4],[1,5]], expected=[1,4], label="example 2"),
    ]

    def solve(self, edges: list[list[int]]) -> list[int]:
        raise NotImplementedError("TODO: Implement solve(self, edges: list[list[int]]) -> list[int]")

if __name__ == "__main__":
    Solution().run()
