"""P077: Combinations (Medium)

TODO: Implement solve() below.
Hint: Use backtracking with a start index to generate all k-length combinations from 1..n.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "77. Combinations"
    test_cases = [
        TestCase(input=(4, 2), expected=[[1,2],[1,3],[1,4],[2,3],[2,4],[3,4]], label="example 1"),
        TestCase(input=(1, 1), expected=[[1]], label="example 2"),
        TestCase(input=(3, 1), expected=[[1],[2],[3]], label="example 3"),
    ]

    def solve(self, n: int, k: int) -> list[list[int]]:
        result: list[list[int]] = []

        def backtrack(start: int, path: list[int]):
            if len(path) == k:
                result.append(path[:])
                return
            for i in range(start, n + 1):
                path.append(i)
                backtrack(i + 1, path)
                path.pop()

        backtrack(1, [])
        return result


if __name__ == "__main__":
    Solution().run()
