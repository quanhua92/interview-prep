"""P498: Diagonal Traverse (Medium)

TODO: Implement solve() below.
Hint: Group by i+j diagonal index. If d is even, reverse to simulate up-right direction.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "498. Diagonal Traverse"
    test_cases = [
        TestCase(input=[[1,2,3],[4,5,6],[7,8,9]], expected=[1,2,4,7,5,3,6,8,9], label="example 1"),
        TestCase(input=[[1,2],[3,4],[5,6]], expected=[1,2,3,5,4,6], label="example 2"),
        TestCase(input=[[1]], expected=[1], label="single element"),
    ]

    def solve(self, mat: list[list[int]]) -> list[int]:
        if not mat or not mat[0]:
            return []
        m, n = len(mat), len(mat[0])
        result: list[int] = []
        diagonals: dict[int, list[int]] = {}

        for i in range(m):
            for j in range(n):
                d = i + j
                if d not in diagonals:
                    diagonals[d] = []
                diagonals[d].append(mat[i][j])

        for d in range(m + n - 1):
            if d % 2 == 0:
                result.extend(reversed(diagonals[d]))
            else:
                result.extend(diagonals[d])

        return result


if __name__ == "__main__":
    Solution().run()
