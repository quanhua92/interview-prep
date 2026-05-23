"""
P268: Missing Number (Easy)
https://leetcode.com/problems/missing-number/
Topics: Array, Hash Table, Math, Binary Search, Bit Manipulation, Sorting

Given an array nums containing n distinct numbers in the range [0, n], return the only number in the range that is missing from the array.

Example 1:
    Input: nums = [3,0,1]
    Output: 2
    Explanation:
    n = 3 since there are 3 numbers, so all numbers are in the range [0,3] . 2 is the missing number in the range since it does not appear in nums .

Example 2:
    Input: nums = [0,1]
    Output: 2
    Explanation:
    n = 2 since there are 2 numbers, so all numbers are in the range [0,2] . 2 is the missing number in the range since it does not appear in nums .

Example 3:
    Input: nums = [9,6,4,2,3,5,7,0,1]
    Output: 8
    Explanation:
    n = 9 since there are 9 numbers, so all numbers are in the range [0,9] . 8 is the missing number in the range since it does not appear in nums .

Constraints:
    - n == nums.length
    - 1 <= n <= 104
    - 0 <= nums[i] <= n
    - All the numbers of nums are unique.

Follow up:
    - Could you implement a solution using only O(1) extra space complexity and O(n) runtime complexity?

Template (python3):
    class Solution:
        def missingNumber(self, nums: List[int]) -> int:

Hint: Use the sum formula n*(n+1)//2 minus the actual sum to find the missing number.
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "268. Missing Number"
    test_cases = [
        TestCase(input=[3, 0, 1], expected=2, label="example 1"),
        TestCase(input=[0, 1], expected=2, label="example 2"),
        TestCase(input=[9, 6, 4, 2, 3, 5, 7, 0, 1], expected=8, label="example 3"),
        TestCase(input=[1], expected=0, label="missing 0, n=1"),
        TestCase(input=[0], expected=1, label="missing n, n=1"),
        TestCase(input=[0, 1, 2, 3], expected=4, label="missing last, sorted"),
        TestCase(input=[1, 2, 3, 4, 5], expected=0, label="missing 0, n=5"),
    ]

    def solve(self, nums: list[int]) -> int:
        i = 0
        n = len(nums)
        while i < n:
            correct = nums[i]
            if correct < n and nums[i] != nums[correct]:
                nums[i], nums[correct] = nums[correct], nums[i]
            else:
                i += 1
        for i in range(n):
            if nums[i] != i:
                return i
        return n

    def solve_alternative(self, nums: list[int]) -> int:
        n = len(nums)
        expected = n * (n + 1) // 2
        return expected - sum(nums)


if __name__ == "__main__":
    Solution().run()
