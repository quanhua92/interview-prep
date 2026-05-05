"""P997: Find the Town Judge (Easy)

TODO: Implement solve() below.
Hint: Trust score array: for each [a,b], scores[a]-=1 and scores[b]+=1. Judge has score n-1.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "997. Find the Town Judge"
    test_cases = [
        TestCase(input=(2, [[1,2]]), expected=2, label="example 1"),
        TestCase(input=(3, [[1,3],[2,3]]), expected=3, label="example 2"),
        TestCase(input=(3, [[1,3],[2,3],[3,1]]), expected=-1, label="no judge"),
        TestCase(input=(1, []), expected=1, label="single person"),
    ]

    def solve(self, n: int, trust: list[list[int]]) -> int:
        scores = [0] * (n + 1)
        for a, b in trust:
            scores[a] -= 1
            scores[b] += 1
        for i in range(1, n + 1):
            if scores[i] == n - 1:
                return i
        return -1


if __name__ == "__main__":
    Solution().run()
