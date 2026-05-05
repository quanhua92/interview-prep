"""P990: Satisfiability of Equality Equations (Medium)

TODO: Implement solve() below.
Hint: Union-Find with 26 variables (map char to 0-25). First pass: union all "==". Second pass: check "!=" for contradiction.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "990. Satisfiability of Equality Equations"
    test_cases = [
        TestCase(input=["a==b","b!=a"], expected=False, label="example 1"),
        TestCase(input=["b==a","a==b"], expected=True, label="example 2"),
        TestCase(input=["a==b","b==c","a==c"], expected=True, label="example 3"),
        TestCase(input=["a!=a"], expected=False, label="contradiction"),
    ]

    def solve(self, equations: list[str]) -> bool:
        parent = list(range(26))
        rank = [0] * 26

        def find(x: int) -> int:
            if parent[x] != x:
                parent[x] = find(parent[x])
            return parent[x]

        def union(x: int, y: int) -> None:
            rx, ry = find(x), find(y)
            if rx == ry:
                return
            if rank[rx] < rank[ry]:
                rx, ry = ry, rx
            parent[ry] = rx
            if rank[rx] == rank[ry]:
                rank[rx] += 1

        # First pass: union all equality equations
        for eq in equations:
            if eq[1] == '=':
                a = ord(eq[0]) - ord('a')
                b = ord(eq[3]) - ord('a')
                union(a, b)

        # Second pass: check inequality equations for contradiction
        for eq in equations:
            if eq[1] == '!':
                a = ord(eq[0]) - ord('a')
                b = ord(eq[3]) - ord('a')
                if find(a) == find(b):
                    return False
        return True


if __name__ == "__main__":
    Solution().run()
