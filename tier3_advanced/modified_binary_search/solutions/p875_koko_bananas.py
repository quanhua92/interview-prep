"""
P875: Koko Eating Bananas (Medium)
https://leetcode.com/problems/koko-eating-bananas/
Topics: Array, Binary Search

Koko loves to eat bananas. There are n piles of bananas, the ith pile has piles[i] bananas. The guards have gone and will come back in h hours.
Koko can decide her bananas-per-hour eating speed of k. Each hour, she chooses some pile of bananas and eats k bananas from that pile. If the pile has less than k bananas, she eats all of them instead and will not eat any more bananas during this hour.
Koko likes to eat slowly but still wants to finish eating all the bananas before the guards return.
Return the minimum integer k such that she can eat all the bananas within h hours.

Example 1:
    Input: piles = [3,6,7,11], h = 8
    Output: 4

Example 2:
    Input: piles = [30,11,23,4,20], h = 5
    Output: 30

Example 3:
    Input: piles = [30,11,23,4,20], h = 6
    Output: 23

Constraints:
    - 1 <= piles.length <= 104
    - piles.length <= h <= 109
    - 1 <= piles[i] <= 109

Template (python3):
    class Solution:
        def minEatingSpeed(self, piles: List[int], h: int) -> int:

Hint: Binary search on the eating speed, computing total hours for each candidate.
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase
import math


class Solution(Problem):
    name = "875. Koko Eating Bananas"
    test_cases = [
        TestCase(input=([3, 6, 7, 11], 8), expected=4, label="example 1"),
        TestCase(input=([30, 11, 23, 4, 20], 5), expected=30, label="example 2"),
        TestCase(input=([30, 11, 23, 4, 20], 6), expected=23, label="example 3"),
        TestCase(input=([1], 1), expected=1, label="single pile single hour"),
        TestCase(input=([312884470], 970709593), expected=1, label="single pile many hours"),
        TestCase(input=([1, 1, 1, 1], 4), expected=1, label="all ones h equals length"),
        TestCase(input=([1000000000, 1000000000], 3), expected=1000000000, label="large values tight deadline"),
        TestCase(input=([5, 5, 5, 5, 5], 10), expected=3, label="uniform piles extra hours"),
    ]

    def solve(self, piles: list[int], h: int) -> int:
        left, right = 1, max(piles)
        while left < right:
            mid = left + (right - left) // 2
            hours = sum(math.ceil(p / mid) for p in piles)
            if hours <= h:
                right = mid
            else:
                left = mid + 1
        return left


if __name__ == "__main__":
    Solution().run()
