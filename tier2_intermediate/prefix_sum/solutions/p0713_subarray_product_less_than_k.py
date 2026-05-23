"""
P713: Subarray Product Less Than K (Medium)
https://leetcode.com/problems/subarray-product-less-than-k/
Topics: Array, Binary Search, Sliding Window, Prefix Sum

Given an array of integers nums and an integer k, return the number of contiguous subarrays where the product of all the elements in the subarray is strictly less than k.

Example 1:
    Input: nums = [10,5,2,6], k = 100
    Output: 8
    Explanation: The 8 subarrays that have product less than 100 are:
    [10], [5], [2], [6], [10, 5], [5, 2], [2, 6], [5, 2, 6]
    Note that [10, 5, 2] is not included as the product of 100 is not strictly less than k.

Example 2:
    Input: nums = [1,2,3], k = 0
    Output: 0

Constraints:
    - 1 <= nums.length <= 3 * 104
    - 1 <= nums[i] <= 1000
    - 0 <= k <= 106

Hints:
    - For each j, let opt(j) be the smallest i so that nums[i] * nums[i+1] * ... * nums[j] is less than k.  opt is an increasing function.

Template (python3):
    class Solution:
        def numSubarrayProductLessThanK(self, nums: List[int], k: int) -> int:

Hint: Use a sliding window where you shrink from the left when product >= k.
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "713. Subarray Product Less Than K"
    test_cases = [
        TestCase(input=([10, 5, 2, 6], 100), expected=8, label="example 1"),
        TestCase(input=([1, 2, 3], 0), expected=0, label="zero k"),
        TestCase(input=([1, 1, 1], 2), expected=6, label="all ones"),
        TestCase(input=([1, 2, 3], 0), expected=0, label="k equals 0"),
        TestCase(input=([1, 2, 3], 1), expected=0, label="k equals 1"),
        TestCase(input=([1000, 1000, 1000], 1000000), expected=3, label="all large numbers"),
        TestCase(input=([10, 5, 2, 6], 8), expected=3, label="small k many singles"),
    ]

    def solve(self, nums: list[int], k: int) -> int:
        if k <= 1:
            return 0

        count = 0
        product = 1
        left = 0

        for right in range(len(nums)):
            product *= nums[right]
            while product >= k:
                product //= nums[left]
                left += 1
            count += right - left + 1

        return count


if __name__ == "__main__":
    Solution().run()
