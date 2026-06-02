"""
P407: Trapping Rain Water II [PREMIUM] (Hard)
https://leetcode.com/problems/trapping-rain-water-ii/
Topics: Array, Breadth-First Search, Heap (Priority Queue), Matrix

Given an m x n integer matrix heightMap representing the height of each unit cell in a 2D elevation map, return the volume of water it can trap after raining.
Example 1:
    Input: heightMap = [[1,4,3,1,3,2],[3,2,1,3,2,4],[2,3,3,2,3,1]]
    Output: 4
    Explanation: After the rain, water is trapped between the blocks.
    We have two small ponds 1 and 3 units trapped.
    The total volume of water trapped is 4.

Example 2:
    Input: heightMap = [[3,3,3,3,3],[3,2,2,2,3],[3,2,1,2,3],[3,2,2,2,3],[3,3,3,3,3]]
    Output: 10

Constraints:
    - m == heightMap.length
    - n == heightMap[i].length
    - 1 <= m, n <= 200
    - 0 <= heightMap[i][j] <= 2 * 10^4

Template (python3):
    class Solution:
        def trapRainWater(self, heightMap: List[List[int]]) -> int:
"""

from src.wasm_libs.py.io import *
import heapq


def solve(heightMap: list[list[int]]) -> int:
    if not heightMap or not heightMap[0]:
        return 0
    m, n = len(heightMap), len(heightMap[0])
    if m < 3 or n < 3:
        return 0
    visited = [[False] * n for _ in range(m)]
    heap: list[tuple[int, int, int]] = []
    for r in range(m):
        for c in (0, n - 1):
            heapq.heappush(heap, (heightMap[r][c], r, c))
            visited[r][c] = True
    for c in range(1, n - 1):
        for r in (0, m - 1):
            heapq.heappush(heap, (heightMap[r][c], r, c))
            visited[r][c] = True
    water = 0
    dirs = [(-1, 0), (1, 0), (0, -1), (0, 1)]
    while heap:
        h, r, c = heapq.heappop(heap)
        for dr, dc in dirs:
            nr, nc = r + dr, c + dc
            if 0 <= nr < m and 0 <= nc < n and not visited[nr][nc]:
                visited[nr][nc] = True
                water += max(0, h - heightMap[nr][nc])
                heapq.heappush(heap, (max(h, heightMap[nr][nc]), nr, nc))
    return water


if __name__ == "__main__":
    dims = read_ints()
    m, n = dims[0], dims[1]
    heightMap = [read_ints() for _ in range(m)]
    result = solve(heightMap)
    write_int(result)
