"""
P347: Top K Frequent Elements (Medium)
https://leetcode.com/problems/top-k-frequent-elements/
Topics: Array, Hash Table, Divide and Conquer, Sorting, Heap (Priority Queue), Bucket Sort, Counting, Quickselect

Given an integer array nums and an integer k, return the k most frequent elements. You may return the answer in any order.

Example 1:
    Input: nums = [1,1,1,2,2,3], k = 2
    Output: [1,2]

Example 2:
    Input: nums = [1], k = 1
    Output: [1]

Constraints:
    - 1 <= nums.length <= 105
    - -104 <= nums[i] <= 104
    - k is in the range [1, the number of unique elements in the array].
    - It is guaranteed that the answer is unique.

Follow up:
    - Your algorithm's time complexity must be better than O(n log n), where n is the array's size.

Template (python3):
    class Solution:
        def topKFrequent(self, nums: List[int], k: int) -> List[int]:

Hint: Use a frequency counter and a min-heap of size k.
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase
from collections import Counter


class Solution(Problem):
    name = "347. Top K Frequent Elements"
    test_cases = [
        TestCase(input=([1, 1, 1, 2, 2, 3], 2), expected=[1, 2], label="example 1"),
        TestCase(input=([1], 1), expected=[1], label="example 2"),
        TestCase(input=([7, 7, 7, 7, 1, 2, 2, 2], 2), expected=[7, 2], label="distinct frequencies"),
        TestCase(input=([1, 2, 3, 4, 5, 6], 3), expected=[6, 5, 4], label="all freq 1"),
        TestCase(input=([1, 1, 1, 1], 1), expected=[1], label="all same element"),
        TestCase(input=([1, 1, 2, 2, 2, 3, 3, 3, 3], 2), expected=[3, 2], label="clear frequency ranking"),
        TestCase(input=([-1, -1, -1, 2, 2], 1), expected=[-1], label="negative numbers"),
        TestCase(input=([0, 0, 0, 0, 1, 1, 2], 2), expected=[0, 1], label="zero values"),
    ]

    def solve(self, nums: list[int], k: int) -> list[int]:
        count = Counter(nums)
        return [item for item, _ in sorted(count.items(), key=lambda x: (-x[1], -x[0]))[:k]]


if __name__ == "__main__":
    Solution().run()
