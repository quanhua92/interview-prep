"""P1091: Shortest Path in Binary Matrix (Medium)

TODO: Implement solve() below.
Hint: BFS from (0,0) with 8 directions, return distance to (n-1,n-1) or -1.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase
from collections import deque


class Solution(Problem):
    name = "1091. Shortest Path in Binary Matrix"
    test_cases = [
        TestCase(input=[[0, 1], [1, 0]], expected=2, label="example 1"),
        TestCase(input=[[0, 0, 0], [1, 1, 0], [1, 1, 0]], expected=4, label="example 2"),
        TestCase(input=[[1, 0], [0, 1]], expected=-1, label="blocked"),
        TestCase(input=[[0]], expected=1, label="single cell"),
    ]

    def solve(self, grid: list[list[int]]) -> int:
        n = len(grid)
        if grid[0][0] == 1 or grid[n - 1][n - 1] == 1:
            return -1
        if n == 1:
            return 1
        # 8 directions
        directions = [(-1, -1), (-1, 0), (-1, 1), (0, -1), (0, 1), (1, -1), (1, 0), (1, 1)]
        queue = deque([(0, 0, 1)])  # (row, col, distance)
        grid[0][0] = 1  # mark visited
        while queue:
            row, col, dist = queue.popleft()
            for dr, dc in directions:
                nr, nc = row + dr, col + dc
                if 0 <= nr < n and 0 <= nc < n and grid[nr][nc] == 0:
                    if nr == n - 1 and nc == n - 1:
                        return dist + 1
                    grid[nr][nc] = 1  # mark visited
                    queue.append((nr, nc, dist + 1))
        return -1


if __name__ == "__main__":
    Solution().run()
