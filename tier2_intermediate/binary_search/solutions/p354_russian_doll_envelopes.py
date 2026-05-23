"""
P354: Russian Doll Envelopes [PREMIUM] (Hard)
https://leetcode.com/problems/russian-doll-envelopes/
Topics: Array, Binary Search, Dynamic Programming, Sorting

You are given a 2D array of integers envelopes where envelopes[i] = [wi, hi] represents the width and the height of an envelope.
One envelope can fit into another if and only if both the width and height of one envelope are greater than the other envelope's width and height.
Return the maximum number of envelopes you can Russian doll (i.e., put one inside the other).
Note: You cannot rotate an envelope.
Example 1:
    Input: envelopes = [[5,4],[6,4],[6,7],[2,3]]
    Output: 3
    Explanation: The maximum number of envelopes you can Russian doll is 3 ([2,3] => [5,4] => [6,7]).

Example 2:
    Input: envelopes = [[1,1],[1,1],[1,1]]
    Output: 1

Constraints:
    - 1 <= envelopes.length <= 105
    - envelopes[i].length == 2
    - 1 <= wi, hi <= 105

Template (python3):
    class Solution:
        def maxEnvelopes(self, envelopes: List[List[int]]) -> int:
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "354. Russian Doll Envelopes"
    test_cases = [
        TestCase(input=[[5, 4], [6, 4], [6, 7], [2, 3]], expected=3, label="example 1"),
        TestCase(input=[[1, 1], [1, 1], [1, 1]], expected=1, label="example 2"),
        TestCase(input=[[1, 1]], expected=1, label="single envelope"),
        TestCase(input=[[1, 2], [2, 3], [3, 4]], expected=3, label="strictly increasing"),
        TestCase(input=[[4, 5], [4, 6], [6, 7], [2, 3], [1, 1]], expected=4, label="width ties sorted by height desc"),
        TestCase(input=[[2, 100], [3, 200], [4, 300], [5, 250]], expected=3, label="height breaks chain"),
    ]

    def solve(self, envelopes: list[list[int]]) -> int:
        import bisect

        envelopes.sort(key=lambda x: (x[0], -x[1]))
        heights: list[int] = []
        for _, h in envelopes:
            idx = bisect.bisect_left(heights, h)
            if idx == len(heights):
                heights.append(h)
            else:
                heights[idx] = h
        return len(heights)


if __name__ == "__main__":
    Solution().run()
