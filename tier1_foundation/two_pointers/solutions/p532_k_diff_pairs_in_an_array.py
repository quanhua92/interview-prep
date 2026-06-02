"""
P532: K-diff Pairs in an Array [PREMIUM] (Medium)
https://leetcode.com/problems/k-diff-pairs-in-an-array/
Topics: Array, Hash Table, Two Pointers, Binary Search, Sorting

Given an array of integers nums and an integer k, return the number of unique k-diff pairs in the array.
A k-diff pair is an integer pair (nums[i], nums[j]), where the following are true:

    0 <= i, j < nums.length
    i != j
    |nums[i] - nums[j]| == k

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
    - 1 <= nums.length <= 10^4
    - -10^7 <= nums[i] <= 10^7
    - 0 <= k <= 10^7

Template (python3):
    class Solution:
        def findPairs(self, nums: List[int], k: int) -> int:
"""

from src.wasm_libs.py.io import *


def solve(nums: list[int], k: int) -> int:
    if k < 0:
        return 0
    nums.sort()
    count = 0
    left, right = 0, 1
    while right < len(nums):
        diff = nums[right] - nums[left]
        if diff < k:
            right += 1
        elif diff > k:
            left += 1
        else:
            count += 1
            left_val, right_val = nums[left], nums[right]
            while left < len(nums) and nums[left] == left_val:
                left += 1
            while right < len(nums) and nums[right] == right_val:
                right += 1
        if left == right:
            right += 1
    return count


if __name__ == "__main__":
    nums = read_ints()
    k = read_int()
    result = solve(nums, k)
    write_int(result)
