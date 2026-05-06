"""
P704: Binary Search (Easy)
https://leetcode.com/problems/binary-search/
Topics: Array, Binary Search

Given an array of integers nums which is sorted in ascending order, and an integer target, write a function to search target in nums. If target exists, then return its index. Otherwise, return -1.
You must write an algorithm with O(log n) runtime complexity.

Example 1:
    Input: nums = [-1,0,3,5,9,12], target = 9
    Output: 4
    Explanation: 9 exists in nums and its index is 4

Example 2:
    Input: nums = [-1,0,3,5,9,12], target = 2
    Output: -1
    Explanation: 2 does not exist in nums so return -1

Constraints:
    - 1 <= nums.length <= 104
    - -104 < nums[i], target < 104
    - All the integers in nums are unique.
    - nums is sorted in ascending order.

Template (python3):
    class Solution:
        def search(self, nums: List[int], target: int) -> int:

Hint: Use the classic binary search pattern with left and right pointers.
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "704. Binary Search"
    test_cases = [
        TestCase(input=([-1, 0, 3, 5, 9, 12], 9), expected=4, label="example 1"),
        TestCase(input=([-1, 0, 3, 5, 9, 12], 2), expected=-1, label="example 2"),
        TestCase(input=([5], 5), expected=0, label="single element"),
    ]

    def solve(self, nums: list[int], target: int) -> int:
        raise NotImplementedError(
            "TODO: Implement solve(self, nums: list[int], target: int) -> int"
        )


if __name__ == "__main__":
    Solution().run()
