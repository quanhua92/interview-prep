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
    def __init__(self, n: int):
        self.parent = list(range(n))
        self.rank = [0] * n

    def find(self, x: int) -> int:
        if self.parent[x] != x:
            self.parent[x] = self.find(self.parent[x])
        return self.parent[x]

    def union(self, x: int, y: int) -> bool:
        rx, ry = self.find(x), self.find(y)
        if rx == ry:
            return False
        if self.rank[rx] < self.rank[ry]:
            rx, ry = ry, rx
        self.parent[ry] = rx
        if self.rank[rx] == self.rank[ry]:
            self.rank[rx] += 1
        return True


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
    ]

    def solve(self, n: int, edges: list[list[int]]) -> int:
        uf = UnionFind(n)
        components = n
        for u, v in edges:
            if uf.union(u, v):
                components -= 1
        return components


if __name__ == "__main__":
    Solution().run()
