"""
P493: Reverse Pairs [PREMIUM] (Hard)
https://leetcode.com/problems/reverse-pairs/
Topics: Array, Binary Search, Divide and Conquer, Binary Indexed Tree, Segment Tree, Merge Sort, Ordered Set

Given an integer array nums, return the number of reverse pairs in the array.
A reverse pair is a pair (i, j) where:
Example 1:
    Input: nums = [1,3,2,3,1]
    Output: 2
    Explanation: The reverse pairs are:
    (1, 4) --> nums[1] = 3, nums[4] = 1, 3 > 2 * 1
    (3, 4) --> nums[3] = 3, nums[4] = 1, 3 > 2 * 1

Example 2:
    Input: nums = [2,4,3,5,1]
    Output: 3
    Explanation: The reverse pairs are:
    (1, 4) --> nums[1] = 4, nums[4] = 1, 4 > 2 * 1
    (2, 4) --> nums[2] = 3, nums[4] = 1, 3 > 2 * 1
    (3, 4) --> nums[3] = 5, nums[4] = 1, 5 > 2 * 1

Constraints:
    - 1 <= nums.length <= 5 * 104
    - -231 <= nums[i] <= 231 - 1

Hint: Use the merge-sort technique.
Hint: Divide the array into two parts and sort them.
Hint: For each integer in the first part, count the number of integers that satisfy the condition from the second part. Use the pointer to help you in the counting process.

Template (python3):
    class Solution:
        def reversePairs(self, nums: List[int]) -> int:
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "493. Reverse Pairs"
    test_cases = [
        TestCase(input=[1, 3, 2, 3, 1], expected=2, label="example 1"),
        TestCase(input=[2, 4, 3, 5, 1], expected=3, label="example 2"),
        TestCase(input=[1], expected=0, label="single element"),
        TestCase(input=[5, 4, 3, 2, 1], expected=4, label="all descending"),
        TestCase(input=[1, 2, 3, 4, 5], expected=0, label="sorted ascending"),
        TestCase(input=[2, 1, -1], expected=2, label="negative numbers"),
        TestCase(input=[1, 1, 1, 1], expected=0, label="all equal"),
    ]

    def solve(self, nums: list[int]) -> int:
        def merge_sort(arr: list[int]) -> int:
            if len(arr) <= 1:
                return 0
            mid = len(arr) // 2
            left, right = arr[:mid], arr[mid:]
            count = merge_sort(left) + merge_sort(right)
            # Count reverse pairs: left[i] > 2 * right[j]
            j = 0
            for num in left:
                while j < len(right) and num > 2 * right[j]:
                    j += 1
                count += j
            # Merge
            arr[:] = sorted(left + right)
            return count

        return merge_sort(nums[:])


if __name__ == "__main__":
    Solution().run()
