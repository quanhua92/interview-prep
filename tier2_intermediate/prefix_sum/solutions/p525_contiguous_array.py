"""
P525: Contiguous Array [PREMIUM] (Medium)
https://leetcode.com/problems/contiguous-array/
Topics: Array, Hash Table, Prefix Sum

Given a binary array nums, return the maximum length of a contiguous subarray with an equal number of 0 and 1.
Example 1:
    Input: nums = [0,1]
    Output: 2
    Explanation: [0, 1] is the longest contiguous subarray with an equal number of 0 and 1.

Example 2:
    Input: nums = [0,1,0]
    Output: 2
    Explanation: [0, 1] (or [1, 0]) is a longest contiguous subarray with equal number of 0 and 1.

Example 3:
    Input: nums = [0,1,1,1,1,1,0,0,0]
    Output: 6
    Explanation: [1,1,1,0,0,0] is the longest contiguous subarray with equal number of 0 and 1.

Constraints:
    - 1 <= nums.length <= 105
    - nums[i] is either 0 or 1.

Template (python3):
    class Solution:
        def findMaxLength(self, nums: List[int]) -> int:
"""

from src.wasm_libs.py.io import *


def solve(nums: list[int]) -> int:
    first_occurrence = {0: -1}
    max_len = count = 0
    for i, num in enumerate(nums):
        count += 1 if num == 1 else -1
        if count in first_occurrence:
            max_len = max(max_len, i - first_occurrence[count])
        else:
            first_occurrence[count] = i
    return max_len


if __name__ == "__main__":
    nums = read_ints()
    result = solve(nums)
    write_int(result)
