"""
P1306: Jump Game III (Medium)
https://leetcode.com/problems/jump-game-iii/
Topics: Array, Depth-First Search, Breadth-First Search

Given an array of non-negative integers arr, you are initially positioned at start index of the array. When you are at index i, you can jump to i + arr[i] or i - arr[i], check if you can reach any index with value 0.
Notice that you can not jump outside of the array at any time.

Example 1:
    Input: arr = [4,2,3,0,3,1,2], start = 5
    Output: true
    Explanation:
    All possible ways to reach at index 3 with value 0 are:
    index 5 -> index 4 -> index 1 -> index 3
    index 5 -> index 6 -> index 4 -> index 1 -> index 3

Example 2:
    Input: arr = [4,2,3,0,3,1,2], start = 0
    Output: true
    Explanation:
    One possible way to reach at index 3 with value 0 is:
    index 0 -> index 4 -> index 1 -> index 3

Example 3:
    Input: arr = [3,0,2,1,2], start = 2
    Output: false
    Explanation: There is no way to reach at index 1 with value 0.

Constraints:
    - 1 <= arr.length <= 5 * 104
    - 0 <= arr[i] < arr.length
    - 0 <= start < arr.length

Hints:
    - Think of BFS to solve the problem.
    - When you reach a position with a value = 0 then return true.

Template (python3):
    class Solution:
        def canReach(self, arr: List[int], start: int) -> bool:

Hint: DFS with a visited set; explore start+arr[start] and start-arr[start], checking bounds and visited.
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "1306. Jump Game III"
    test_cases = [
        TestCase(input=([4, 2, 3, 0, 3, 1, 2], 5), expected=True, label="example 1"),
        TestCase(
            input=([4, 2, 3, 0, 3, 1, 2], 0), expected=True, label="start at index 0"
        ),
        TestCase(input=([3, 0, 2, 1, 2], 2), expected=False, label="cannot reach zero"),
        TestCase(input=([0], 0), expected=True, label="single element zero"),
        TestCase(input=([2], 0), expected=False, label="single element non-zero"),
        TestCase(input=([0, 1], 1), expected=True, label="start next to zero"),
        TestCase(input=([1, 1, 1, 1, 0], 0), expected=True, label="linear path to zero"),
        TestCase(input=([7, 0, 0, 0, 0, 0, 0, 0], 0), expected=True, label="jump directly to zero"),
    ]

    def solve(self, arr: list[int], start: int) -> bool:
        raise NotImplementedError(
            "TODO: Implement solve(self, arr: list[int], start: int) -> bool"
        )


if __name__ == "__main__":
    Solution().run()
