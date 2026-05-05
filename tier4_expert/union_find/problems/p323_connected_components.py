"""P323: Number of Connected Components in an Undirected Graph (Medium)

TODO: Implement solve() below.
Hint: Use a Union-Find data structure to merge connected nodes and count components.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase

class UnionFind:
    def __init__(self, n: int):
        ...

    def find(self, x: int) -> int:
        ...

    def union(self, x: int, y: int) -> bool:
        ...

class Solution(Problem):
    name = "323. Number of Connected Components in an Undirected Graph"
    test_cases = [
        TestCase(input=(5, [[0,1],[1,2],[3,4]]), expected=2, label="example"),
        TestCase(input=(5, [[0,1],[1,2],[2,3],[3,4]]), expected=1, label="fully connected"),
        TestCase(input=(3, []), expected=3, label="no edges"),
    ]

    def solve(self, n: int, edges: list[list[int]]) -> int:
        raise NotImplementedError("TODO: Implement solve(self, n: int, edges: list[list[int]]) -> int")

if __name__ == "__main__":
    Solution().run()
