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
    - 1 <= piles.length <= 10^4
    - piles.length <= h <= 10^9
    - 1 <= piles[i] <= 10^9

Template (python3):
    class Solution:
        def minEatingSpeed(self, piles: List[int], h: int) -> int:

Hint: Binary search on the eating speed, computing total hours for each candidate.
"""

import math

from src.wasm_libs.py.io import *


def solve(piles: list[int], h: int) -> int:
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
    piles = read_ints()
    h = read_int()
    result = solve(piles, h)
    write_int(result)
