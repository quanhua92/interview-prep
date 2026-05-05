"""P323: Number of Connected Components in an Undirected Graph (Medium)

TODO: Implement solve() below.
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
        TestCase(input=(5, [[0,1],[1,2],[3,4]]), expected=2, label="example"),
        TestCase(input=(5, [[0,1],[1,2],[2,3],[3,4]]), expected=1, label="fully connected"),
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
