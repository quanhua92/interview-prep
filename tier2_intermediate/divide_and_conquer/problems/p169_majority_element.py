"""
P169: Majority Element (Easy)
https://leetcode.com/problems/majority-element/
Topics: Array, Hash Table, Divide and Conquer, Sorting, Counting

Given an array nums of size n, return the majority element.
The majority element is the element that appears more than ⌊n / 2⌋ times. You may assume that the majority element always exists in the array.

Example 1:
    Input: nums = [3,2,3]
    Output: 3

Example 2:
    Input: nums = [2,2,1,1,1,2,2]
    Output: 2

Constraints:
    - n == nums.length
    - 1 <= n <= 5 * 104
    - -109 <= nums[i] <= 109

Hint: Use Boyer-Moore voting algorithm — maintain a candidate and count.
"""

from src.wasm_libs.py.io import *


def solve(nums: list[int]) -> int:
    raise NotImplementedError


if __name__ == "__main__":
    nums = read_ints()
    result = solve(nums)
    write_int(result)
