"""
P268: Missing Number (Easy)
https://leetcode.com/problems/missing-number/
Topics: Array, Hash Table, Math, Binary Search, Bit Manipulation, Sorting

Given an array nums containing n distinct numbers in the range [0, n], return the only number in the range that is missing from the array.

Example 1:
    Input: nums = [3,0,1]
    Output: 2

Example 2:
    Input: nums = [0,1]
    Output: 2

Example 3:
    Input: nums = [9,6,4,2,3,5,7,0,1]
    Output: 8

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

from src.wasm_libs.py.io import *


def solve(nums: list[int]) -> int:
    raise NotImplementedError


if __name__ == "__main__":
    nums = read_ints()
    result = solve(nums)
    write_int(result)
