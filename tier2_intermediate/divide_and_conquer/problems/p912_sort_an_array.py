"""
P912: Sort an Array (Medium)
https://leetcode.com/problems/sort-an-array/
Topics: Array, Divide and Conquer, Sorting, Heap (Priority Queue), Merge Sort, Bucket Sort, Radix Sort, Counting Sort

Given an array of integers nums, sort the array in ascending order and return it.
You must solve the problem without using any built-in functions in O(nlog(n)) time complexity and with the smallest space complexity possible.

Example 1:
    Input: nums = [5,2,3,1]
    Output: [1,2,3,5]

Example 2:
    Input: nums = [5,1,1,2,0,0]
    Output: [0,0,1,1,2,5]

Constraints:
    - 1 <= nums.length <= 5 * 104
    - -5 * 104 <= nums[i] <= 5 * 104

Hint: Implement merge sort — divide array in half, sort recursively, merge.
"""

from src.wasm_libs.py.io import *


def solve(nums: list[int]) -> list[int]:
    raise NotImplementedError


if __name__ == "__main__":
    nums = read_ints()
    result = solve(nums)
    write_ints(result)
