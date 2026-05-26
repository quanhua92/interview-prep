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

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "447. Number of Boomerangs"
    test_cases = [
        TestCase(input=[[0, 0], [1, 0], [2, 0]], expected=2, label="example 1"),
        TestCase(input=[[1, 1], [2, 2], [3, 3]], expected=2, label="example 2"),
        TestCase(input=[[1, 1]], expected=0, label="example 3"),
        TestCase(input=[[0, 0], [1, 0]], expected=0, label="only 2 points"),
        TestCase(input=[[0, 0], [0, 1], [1, 0], [1, 1]], expected=8, label="square 4 points"),
        TestCase(input=[[0, 0], [1, 1], [1, -1]], expected=2, label="isoceles triangle"),
        TestCase(input=[[0, 0], [3, 4], [3, -4]], expected=2, label="isoceles different heights"),
    ]

    def solve(self, points: list[list[int]]) -> int:
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

    def solve_alternative(self, points: list[list[int]]) -> int:
        from collections import defaultdict

        result = 0
        for p in points:
            dist_count: dict[int, int] = defaultdict(int)
            for q in points:
                if p is q:
                    continue
                dx = p[0] - q[0]
                dy = p[1] - q[1]
                dist = dx * dx + dy * dy
                dist_count[dist] += 1
            for count in dist_count.values():
                result += count * (count - 1)
        return result


if __name__ == "__main__":
    Solution().run()
