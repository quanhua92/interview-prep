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
    - 0 <= heightMap[i][j] <= 2 * 104

Template (python3):
    class Solution:
        def trapRainWater(self, heightMap: List[List[int]]) -> int:
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "407. Trapping Rain Water II"
    test_cases = [
        TestCase(
            input=[[1, 4, 3, 1, 3, 2], [3, 2, 1, 3, 2, 4], [2, 3, 3, 2, 3, 1]],
            expected=4,
            label="example 1",
        ),
        TestCase(
            input=[
                [3, 3, 3, 3, 3],
                [3, 2, 2, 2, 3],
                [3, 2, 1, 2, 3],
                [3, 2, 2, 2, 3],
                [3, 3, 3, 3, 3],
            ],
            expected=10,
            label="example 2",
        ),
    ]

    def solve(self, heightMap: list[list[int]]) -> int:
        raise NotImplementedError("TODO: Implement solve(self, heightMap) -> int")


if __name__ == "__main__":
    Solution().run()
