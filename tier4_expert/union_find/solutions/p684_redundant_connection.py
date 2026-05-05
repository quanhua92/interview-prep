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
        parent = list(range(len(edges) + 1))
        rank = [0] * (len(edges) + 1)

        def find(x: int) -> int:
            if parent[x] != x:
                parent[x] = find(parent[x])
            return parent[x]

        def union(x: int, y: int) -> bool:
            rx, ry = find(x), find(y)
            if rx == ry:
                return False
            if rank[rx] < rank[ry]:
                rx, ry = ry, rx
            parent[ry] = rx
            if rank[rx] == rank[ry]:
                rank[rx] += 1
            return True

        for u, v in edges:
            if not union(u, v):
                return [u, v]
        return []

if __name__ == "__main__":
    Solution().run()
