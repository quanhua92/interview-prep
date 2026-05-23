"""
P448: Find All Numbers Disappeared in an Array (Easy)
https://leetcode.com/problems/find-all-numbers-disappeared-in-an-array/
Topics: Array, Hash Table

Given an array nums of n integers where nums[i] is in the range [1, n], return an array of all the integers in the range [1, n] that do not appear in nums.

Example 1:
    Input: nums = [4,3,2,7,8,2,3,1]
    Output: [5,6]

Example 2:
    Input: nums = [1,1]
    Output: [2]

Constraints:
    - n == nums.length
    - 1 <= n <= 105
    - 1 <= nums[i] <= n

Follow up:
    - Could you do it without extra space and in O(n) runtime? You may assume the returned list does not count as extra space.

Hints:
    - This is a really easy problem if you decide to use additional memory. For those trying to write an initial solution using additional memory, think <b>counters!</b>
    - However, the trick really is to not use any additional space than what is already available to use. Sometimes, multiple passes over the input array help find the solution. However, there's an interesting piece of information in this problem that makes it easy to re-use the input array itself for the solution.
    - The problem specifies that the numbers in the array will be in the range [1, n] where n is the number of elements in the array. Can we use this information and modify the array in-place somehow to find what we need?

Template (python3):
    class Solution:
        def findDisappearedNumbers(self, nums: List[int]) -> List[int]:

Hint: Negate the value at index abs(n)-1 for each number. Indices with positive values are missing.
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "448. Find All Numbers Disappeared in an Array"
    test_cases = [
        TestCase(input=[4, 3, 2, 7, 8, 2, 3, 1], expected=[5, 6], label="example 1"),
        TestCase(input=[1, 1], expected=[2], label="example 2"),
        TestCase(input=[2, 2], expected=[1], label="example 3"),
        TestCase(input=[1], expected=[], label="single element, none missing"),
        TestCase(input=[1, 1, 1, 1], expected=[2, 3, 4], label="all same value"),
        TestCase(input=[1, 2, 3, 4, 5], expected=[], label="identity permutation, none missing"),
        TestCase(input=[5, 4, 6, 7, 9, 10, 9, 6, 5, 4], expected=[1, 2, 3, 8], label="large, many disappeared"),
    ]

    def solve(self, nums: list[int]) -> list[int]:
        raise NotImplementedError(
            "TODO: Implement solve(self, nums: list[int]) -> list[int]"
        )


if __name__ == "__main__":
    Solution().run()
