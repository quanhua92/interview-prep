"""
P447: Number of Boomerangs [PREMIUM] (Medium)
https://leetcode.com/problems/number-of-boomerangs/
Topics: Array, Hash Table, Math

You are given n points in the plane that are all distinct, where points[i] = [xi, yi]. A boomerang is a tuple of points (i, j, k) such that the distance between i and j equals the distance between i and k (the order of the tuple matters).
Return the number of boomerangs.
Example 1:
    Input: points = [[0,0],[1,0],[2,0]]
    Output: 2
    Explanation: The two boomerangs are [[1,0],[0,0],[2,0]] and [[1,0],[2,0],[0,0]].

Example 2:
    Input: points = [[1,1],[2,2],[3,3]]
    Output: 2

Example 3:
    Input: points = [[1,1]]
    Output: 0

Constraints:
    - n == points.length
    - 1 <= n <= 500
    - points[i].length == 2
    - -104 <= xi, yi <= 104
    - All the points are unique.

Template (python3):
    class Solution:
        def numberOfBoomerangs(self, points: List[List[int]]) -> int:
"""

from src.wasm_libs.py.io import *


def solve(points: list[list[int]]) -> int:
    result = 0
    for p in points:
        dists = []
        for q in points:
            if p is q:
                continue
            dx = p[0] - q[0]
            dy = p[1] - q[1]
            dists.append(dx * dx + dy * dy)
        dists.sort()
        left = 0
        while left < len(dists):
            right = left
            while right < len(dists) and dists[right] == dists[left]:
                right += 1
            count = right - left
            result += count * (count - 1)
            left = right
    return result


if __name__ == "__main__":
    n = read_int()
    points = []
    for _ in range(n):
        points.append(read_ints())
    write_int(solve(points))
