"""P994: Rotting Oranges (Medium)

TODO: Implement solve() below.
Hint: Use BFS starting from all rotten oranges simultaneously.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase
from collections import deque


class Solution(Problem):
    name = "994. Rotting Oranges"
    test_cases = [
        TestCase(input=[[2,1,1],[1,1,0],[0,1,1]], expected=4, label="example 1"),
        TestCase(input=[[2,1,1],[0,1,1],[1,0,1]], expected=-1, label="example 2"),
        TestCase(input=[[0,2]], expected=0, label="no fresh"),
    ]

    def solve(self, grid: list[list[int]]) -> int:
        rows, cols = len(grid), len(grid[0])
        queue: deque[tuple[int, int]] = deque()
        fresh = 0
        for r in range(rows):
            for c in range(cols):
                if grid[r][c] == 2:
                    queue.append((r, c))
                elif grid[r][c] == 1:
                    fresh += 1
        if fresh == 0:
            return 0
        minutes = 0
        directions = [(0,1),(0,-1),(1,0),(-1,0)]
        while queue:
            for _ in range(len(queue)):
                r, c = queue.popleft()
                for dr, dc in directions:
                    nr, nc = r + dr, c + dc
                    if 0 <= nr < rows and 0 <= nc < cols and grid[nr][nc] == 1:
                        grid[nr][nc] = 2
                        fresh -= 1
                        queue.append((nr, nc))
            if queue:
                minutes += 1
        return minutes if fresh == 0 else -1


if __name__ == "__main__":
    Solution().run()
