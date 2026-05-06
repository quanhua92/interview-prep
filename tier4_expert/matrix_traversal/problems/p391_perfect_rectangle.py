"""
P391: Perfect Rectangle [PREMIUM] (Hard)
https://leetcode.com/problems/perfect-rectangle/
Topics: Array, Hash Table, Math, Geometry, Line Sweep

Given an array rectangles where rectangles[i] = [xi, yi, ai, bi] represents an axis-aligned rectangle. The bottom-left point of the rectangle is (xi, yi) and the top-right point of it is (ai, bi).
Return true if all the rectangles together form an exact cover of a rectangular region.
Example 1:
    Input: rectangles = [[1,1,3,3],[3,1,4,2],[3,2,4,4],[1,3,2,4],[2,3,3,4]]
    Output: true
    Explanation: All 5 rectangles together form an exact cover of a rectangular region.

Example 2:
    Input: rectangles = [[1,1,2,3],[1,3,2,4],[3,1,4,2],[3,2,4,4]]
    Output: false
    Explanation: Because there is a gap between the two rectangular regions.

Example 3:
    Input: rectangles = [[1,1,3,3],[3,1,4,2],[1,3,2,4],[2,2,4,4]]
    Output: false
    Explanation: Because two of the rectangles overlap with each other.

Constraints:
    - 1 <= rectangles.length <= 2 * 104
    - rectangles[i].length == 4
    - -105 <= xi < ai <= 105
    - -105 <= yi < bi <= 105

Template (python3):
    class Solution:
        def isRectangleCover(self, rectangles: List[List[int]]) -> bool:
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "391. Perfect Rectangle"
    test_cases = [
        TestCase(
            input=[
                [1, 1, 3, 3],
                [3, 1, 4, 2],
                [3, 2, 4, 4],
                [1, 3, 2, 4],
                [2, 3, 3, 4],
            ],
            expected=True,
            label="example 1",
        ),
        TestCase(
            input=[[1, 1, 2, 3], [1, 3, 2, 4], [3, 1, 4, 2], [3, 2, 4, 4]],
            expected=False,
            label="example 2",
        ),
        TestCase(
            input=[[1, 1, 3, 3], [3, 1, 4, 2], [1, 3, 2, 4], [2, 2, 4, 4]],
            expected=False,
            label="example 3",
        ),
    ]

    def solve(self, rectangles: list[list[int]]) -> bool:
        raise NotImplementedError("TODO: Implement solve(self, rectangles) -> bool")


if __name__ == "__main__":
    Solution().run()
