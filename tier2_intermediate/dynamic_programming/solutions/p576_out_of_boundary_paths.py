"""
P576: Out of Boundary Paths [PREMIUM] (Medium)
https://leetcode.com/problems/out-of-boundary-paths/
Topics: Dynamic Programming

There is an m x n grid with a ball. The ball is initially at the position [startRow, startColumn]. You are allowed to move the ball to one of the four adjacent cells in the grid (possibly out of the grid crossing the grid boundary). You can apply at most maxMove moves to the ball.
Given the five integers m, n, maxMove, startRow, startColumn, return the number of paths to move the ball out of the grid boundary. Since the answer can be very large, return it modulo 109 + 7.
Example 1:
    Input: m = 2, n = 2, maxMove = 2, startRow = 0, startColumn = 0
    Output: 6

Example 2:
    Input: m = 1, n = 3, maxMove = 3, startRow = 0, startColumn = 1
    Output: 12

Constraints:
    - 1 <= m, n <= 50
    - 0 <= maxMove <= 50
    - 0 <= startRow < m
    - 0 <= startColumn < n

Hint: Is traversing every path feasible? There are many possible paths for a small matrix. Try to optimize it.
Hint: Can we use some space to store the number of paths and update them after every move?
Hint: One obvious thing: the ball will go out of the boundary only by crossing it. Also, there is only one possible way the ball can go out of the boundary from the boundary cell except for corner cells. From the corner cell, the ball can go out in two different ways.

Can you use this thing to solve the problem?

Template (python3):
    class Solution:
        def findPaths(self, m: int, n: int, maxMove: int, startRow: int, startColumn: int) -> int:
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "576. Out of Boundary Paths"
    test_cases = [
        TestCase(input=(2, 2, 2, 0, 0), expected=6, label="example 1"),
        TestCase(input=(1, 3, 3, 0, 1), expected=12, label="example 2"),
    ]

    def solve(
        self, m: int, n: int, maxMove: int, startRow: int, startColumn: int
    ) -> int:
        mod = 10**9 + 7
        dp = [[[0] * n for _ in range(m)] for _ in range(maxMove + 1)]
        dirs = [(-1, 0), (1, 0), (0, -1), (0, 1)]
        dp[0][startRow][startColumn] = 1
        result = 0
        for move in range(maxMove):
            for r in range(m):
                for c in range(n):
                    if dp[move][r][c] == 0:
                        continue
                    for dr, dc in dirs:
                        nr, nc = r + dr, c + dc
                        if 0 <= nr < m and 0 <= nc < n:
                            dp[move + 1][nr][nc] = (
                                dp[move + 1][nr][nc] + dp[move][r][c]
                            ) % mod
                        else:
                            result = (result + dp[move][r][c]) % mod
        return result


if __name__ == "__main__":
    Solution().run()
