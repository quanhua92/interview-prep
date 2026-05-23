"""
P323: Number of Connected Components in an Undirected Graph (Medium)
https://leetcode.com/problems/number-of-connected-components-in-an-undirected-graph/
Topics: Depth-First Search, Breadth-First Search, Union Find, Graph

You have a graph of n nodes. You are given an integer n and an array edges where edges[i] = [ai, bi] indicates that there is an edge between ai and bi in the graph.
Return the number of connected components in the graph.

Example 1:
    Input: n = 5, edges = [[0,1],[1,2],[3,4]]
    Output: 2

Example 2:
    Input: n = 5, edges = [[0,1],[1,2],[2,3],[3,4]]
    Output: 1

Constraints:
    - 1 <= n <= 2000
    - 1 <= edges.length <= 5000
    - edges[i].length == 2
    - 0 <= ai <= bi < n
    - ai != bi
    - There are no repeated edges.

Template (python3):
    class Solution:
        def countComponents(self, n: int, edges: List[List[int]]) -> int:

Hint: Use a Union-Find data structure to merge connected nodes and count components.
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class UnionFind:
    def __init__(self, n: int): ...

    def find(self, x: int) -> int: ...

    def union(self, x: int, y: int) -> bool: ...


class Solution(Problem):
    name = "323. Number of Connected Components in an Undirected Graph"
    test_cases = [
        TestCase(input=(5, [[0, 1], [1, 2], [3, 4]]), expected=2, label="example"),
        TestCase(
            input=(5, [[0, 1], [1, 2], [2, 3], [3, 4]]),
            expected=1,
            label="fully connected",
        ),
        TestCase(input=(3, []), expected=3, label="no edges"),
        TestCase(input=(1, []), expected=1, label="single node no edges"),
        TestCase(input=(4, [[0, 1], [2, 3]]), expected=2, label="two disjoint pairs"),
        TestCase(input=(6, [[0, 1], [1, 2], [2, 0], [3, 4], [4, 5], [5, 3]]), expected=2, label="two triangles"),
        TestCase(input=(7, [[0, 1], [1, 2], [3, 4], [5, 6]]), expected=3, label="three components with chain and pairs"),
    ]

    def solve(self, n: int, edges: list[list[int]]) -> int:
        raise NotImplementedError(
            "TODO: Implement solve(self, n: int, edges: list[list[int]]) -> int"
        )


if __name__ == "__main__":
    Solution().run()
