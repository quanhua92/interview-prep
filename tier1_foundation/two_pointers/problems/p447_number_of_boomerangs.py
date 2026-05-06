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
    ]

    def solve(self, points: list[list[int]]) -> int:
        raise NotImplementedError("TODO: Implement solve(self, points) -> int")


if __name__ == "__main__":
    Solution().run()
