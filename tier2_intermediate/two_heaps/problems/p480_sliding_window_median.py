"""
P480: Sliding Window Median (Hard)
https://leetcode.com/problems/sliding-window-median/
Topics: Array, Hash Table, Sliding Window, Heap (Priority Queue)

The median is the middle value in an ordered integer list. If the size of the list is even, there is no middle value. So the median is the mean of the two middle values.
You are given an integer array nums and an integer k. There is a sliding window of size k which is moving from the very left of the array to the very right. You can only see the k numbers in the window. Each time the sliding window moves right by one position.
Return the median array for each window in the original array. Answers within 10-5 of the actual value will be accepted.

Example 1:
    Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
    Output: [1.00000,-1.00000,-1.00000,3.00000,5.00000,6.00000]
    Explanation:
    Window position                Median
    ---------------                -----
    [1  3  -1] -3  5  3  6  7        1
     1 [3  -1  -3] 5  3  6  7       -1
     1  3 [-1  -3  5] 3  6  7       -1
     1  3  -1 [-3  5  3] 6  7        3
     1  3  -1  -3 [5  3  6] 7        5
     1  3  -1  -3  5 [3  6  7]       6

Example 2:
    Input: nums = [1,2,3,4,2,3,1,4,2], k = 3
    Output: [2.00000,3.00000,3.00000,3.00000,2.00000,3.00000,2.00000]

Constraints:
    - 1 <= k <= nums.length <= 105
    - -231 <= nums[i] <= 231 - 1

Hints:
    - The simplest of solutions comes from the basic idea of finding the median given a set of numbers. We know that by definition, a median is the center element (or an average of the two center elements). Given an unsorted list of numbers, how do we find the median element? If you know the answer to this question, can we extend this idea to every sliding window that we come across in the array?
    - Is there a better way to do what we are doing in the above hint? Don't you think there is duplication of calculation being done there? Is there some sort of optimization that we can do to achieve the same result? This approach is merely a modification of the basic approach except that it simply reduces duplication of calculations once done.
    - The third line of thought is also based on this same idea but achieving the result in a different way. We obviously need the window to be sorted for us to be able to find the median. Is there a data-structure out there that we can use (in one or more quantities) to obtain the median element extremely fast, say O(1) time while having the ability to perform the other operations fairly efficiently as well?

Template (python3):
    class Solution:
        def medianSlidingWindow(self, nums: List[int], k: int) -> List[float]:

Hint: Use a max-heap for the small half and a min-heap for the large half with lazy deletion.
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "480. Sliding Window Median"
    test_cases = [
        TestCase(
            input=([1, 3, -1, -3, 5, 3, 6, 7], 3),
            expected=[1.0, -1.0, -1.0, 3.0, 5.0, 6.0],
            label="example 1",
        ),
        TestCase(input=([1, 2], 1), expected=[1.0, 2.0], label="window size 1"),
        TestCase(
            input=([1, 2, 3, 4, 2, 3, 1, 4, 2], 3),
            expected=[2.0, 3.0, 3.0, 3.0, 2.0, 3.0, 2.0],
            label="example 2",
        ),
        TestCase(
            input=([2147483647, -2147483648], 2),
            expected=[-0.5],
            label="large int boundary",
        ),
        TestCase(
            input=([1, 1, 1, 1], 2),
            expected=[1.0, 1.0, 1.0],
            label="all same values",
        ),
        TestCase(
            input=([5, 5, 5, 5, 5], 5),
            expected=[5.0],
            label="window equals array",
        ),
        TestCase(
            input=([-5, -4, -3, -2, -1], 3),
            expected=[-4.0, -3.0, -2.0],
            label="all negative ascending",
        ),
        TestCase(
            input=([10, 9, 8, 7, 6], 3),
            expected=[9.0, 8.0, 7.0],
            label="descending order",
        ),
    ]

    def solve(self, nums: list[int], k: int) -> list[float]:
        raise NotImplementedError(
            "TODO: Implement solve(self, nums: list[int], k: int) -> list[float]"
        )


if __name__ == "__main__":
    Solution().run()
