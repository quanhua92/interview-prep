"""
P493: Reverse Pairs [PREMIUM] (Hard)
https://leetcode.com/problems/reverse-pairs/
Topics: Array, Binary Search, Divide and Conquer, Binary Indexed Tree, Segment Tree, Merge Sort, Ordered Set

Given an integer array nums, return the number of reverse pairs in the array.
A reverse pair is a pair (i, j) where:

Example 1:
    Input: nums = [1,3,2,3,1]
    Output: 2

Example 2:
    Input: nums = [2,4,3,5,1]
    Output: 3

Constraints:
    - 1 <= nums.length <= 5 * 104
    - -231 <= nums[i] <= 231 - 1

Hint: Use the merge-sort technique.
Hint: Divide the array into two parts and sort them.
Hint: For each integer in the first part, count the number of integers that satisfy the condition from the second part. Use the pointer to help you in the counting process.
"""

from src.wasm_libs.py.io import *


def solve(nums: list[int]) -> int:
    raise NotImplementedError


if __name__ == "__main__":
    nums = read_ints()
    result = solve(nums)
    write_int(result)
