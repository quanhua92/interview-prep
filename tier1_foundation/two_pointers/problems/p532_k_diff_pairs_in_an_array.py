"""
P532: K-diff Pairs in an Array [PREMIUM] (Medium)
https://leetcode.com/problems/k-diff-pairs-in-an-array/
Topics: Array, Hash Table, Two Pointers, Binary Search, Sorting

Given an array of integers nums and an integer k, return the number of unique k-diff pairs in the array.
A k-diff pair is an integer pair (nums[i], nums[j]), where the following are true:
Notice that |val| denotes the absolute value of val.
Example 1:
    Input: nums = [3,1,4,1,5], k = 2
    Output: 2
    Explanation: There are two 2-diff pairs in the array, (1, 3) and (3, 5).
    Although we have two 1s in the input, we should only return the number of unique pairs.

Example 2:
    Input: nums = [1,2,3,4,5], k = 1
    Output: 4
    Explanation: There are four 1-diff pairs in the array, (1, 2), (2, 3), (3, 4) and (4, 5).

Example 3:
    Input: nums = [1,3,1,5,4], k = 0
    Output: 1
    Explanation: There is one 0-diff pair in the array, (1, 1).

Constraints:
    - 1 <= nums.length <= 104
    - -107 <= nums[i] <= 107
    - 0 <= k <= 107

Template (python3):
    class Solution:
        def findPairs(self, nums: List[int], k: int) -> int:
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "532. K-diff Pairs in an Array"
    test_cases = [
        TestCase(input=([3, 1, 4, 1, 5], 2), expected=2, label="example 1"),
        TestCase(input=([1, 2, 3, 4, 5], 1), expected=4, label="example 2"),
        TestCase(input=([1, 3, 1, 5, 4], 0), expected=1, label="example 3"),
    ]

    def solve(self, nums: list[int], k: int) -> int:
        raise NotImplementedError("TODO: Implement solve(self, nums, k) -> int")


if __name__ == "__main__":
    Solution().run()
