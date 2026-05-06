"""
P912: Sort an Array (Medium)
https://leetcode.com/problems/sort-an-array/
Topics: Array, Divide and Conquer, Sorting, Heap (Priority Queue), Merge Sort, Bucket Sort, Radix Sort, Counting Sort

Given an array of integers nums, sort the array in ascending order and return it.
You must solve the problem without using any built-in functions in O(nlog(n)) time complexity and with the smallest space complexity possible.

Example 1:
    Input: nums = [5,2,3,1]
    Output: [1,2,3,5]
    Explanation: After sorting the array, the positions of some numbers are not changed (for example, 2 and 3), while the positions of other numbers are changed (for example, 1 and 5).

Example 2:
    Input: nums = [5,1,1,2,0,0]
    Output: [0,0,1,1,2,5]
    Explanation: Note that the values of nums are not necessarily unique.

Constraints:
    - 1 <= nums.length <= 5 * 104
    - -5 * 104 <= nums[i] <= 5 * 104

Template (python3):
    class Solution:
        def sortArray(self, nums: List[int]) -> List[int]:

Hint: Implement merge sort — divide array in half, sort recursively, merge.
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "912. Sort an Array"
    test_cases = [
        TestCase(input=[5, 2, 3, 1], expected=[1, 2, 3, 5], label="example 1"),
        TestCase(
            input=[5, 1, 1, 2, 0, 0], expected=[0, 0, 1, 1, 2, 5], label="duplicates"
        ),
        TestCase(input=[1], expected=[1], label="single element"),
        TestCase(input=[], expected=[], label="empty array"),
    ]

    def solve(self, nums: list[int]) -> list[int]:
        if len(nums) <= 1:
            return nums[:]

        mid = len(nums) // 2
        left = self.solve(nums[:mid])
        right = self.solve(nums[mid:])

        # Merge
        result: list[int] = []
        i = j = 0
        while i < len(left) and j < len(right):
            if left[i] <= right[j]:
                result.append(left[i])
                i += 1
            else:
                result.append(right[j])
                j += 1
        result.extend(left[i:])
        result.extend(right[j:])
        return result


if __name__ == "__main__":
    Solution().run()
