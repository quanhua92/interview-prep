"""
P215: Kth Largest Element in an Array (Medium)
https://leetcode.com/problems/kth-largest-element-in-an-array/
Topics: Array, Divide and Conquer, Sorting, Heap (Priority Queue), Quickselect

Given an integer array nums and an integer k, return the kth largest element in the array.
Note that it is the kth largest element in the sorted order, not the kth distinct element.
Can you solve it without sorting?

Example 1:
    Input: nums = [3,2,1,5,6,4], k = 2
    Output: 5

Example 2:
    Input: nums = [3,2,3,1,2,4,5,5,6], k = 4
    Output: 4

Constraints:
    - 1 <= k <= nums.length <= 105
    - -104 <= nums[i] <= 104

Template (python3):
    class Solution:
        def findKthLargest(self, nums: List[int], k: int) -> int:

Hint: Use a min-heap of size k to efficiently find the kth largest element.
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase
import heapq


class Solution(Problem):
    name = "215. Kth Largest Element in an Array"
    test_cases = [
        TestCase(input=([3, 2, 1, 5, 6, 4], 2), expected=5, label="example 1"),
        TestCase(input=([3, 2, 3, 1, 2, 4, 5, 5, 6], 4), expected=4, label="example 2"),
        TestCase(input=([1], 1), expected=1, label="single element"),
        TestCase(input=([-1, -2, -3], 1), expected=-1, label="negative numbers"),
        TestCase(input=([5, 5, 5, 5], 2), expected=5, label="all duplicates"),
        TestCase(input=([1, 2, 3], 3), expected=1, label="k equals length"),
        TestCase(input=([-100, 0, 100], 2), expected=0, label="mixed negatives and zero"),
        TestCase(input=(list(range(1, 101)), 50), expected=51, label="100 elements k=50"),
        TestCase(input=([-1, -1, -1, -1], 3), expected=-1, label="all negative duplicates"),
    ]

    def solve(self, nums: list[int], k: int) -> int:
        return heapq.nlargest(k, nums)[-1]


if __name__ == "__main__":
    Solution().run()
