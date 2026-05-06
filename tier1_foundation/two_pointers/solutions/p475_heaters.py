"""
P475: Heaters [PREMIUM] (Medium)
https://leetcode.com/problems/heaters/
Topics: Array, Two Pointers, Binary Search, Sorting

Winter is coming! During the contest, your first job is to design a standard heater with a fixed warm radius to warm all the houses.
Every house can be warmed, as long as the house is within the heater's warm radius range.
Given the positions of houses and heaters on a horizontal line, return the minimum radius standard of heaters so that those heaters could cover all houses.
Notice that all the heaters follow your radius standard, and the warm radius will the same.
Example 1:
    Input: houses = [1,2,3], heaters = [2]
    Output: 1
    Explanation: The only heater was placed in the position 2, and if we use the radius 1 standard, then all the houses can be warmed.

Example 2:
    Input: houses = [1,2,3,4], heaters = [1,4]
    Output: 1
    Explanation: The two heaters were placed at positions 1 and 4. We need to use a radius 1 standard, then all the houses can be warmed.

Example 3:
    Input: houses = [1,5], heaters = [2]
    Output: 3

Constraints:
    - 1 <= houses.length, heaters.length <= 3 * 104
    - 1 <= houses[i], heaters[i] <= 109

Template (python3):
    class Solution:
        def findRadius(self, houses: List[int], heaters: List[int]) -> int:
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "475. Heaters"
    test_cases = [
        TestCase(input=([1, 2, 3], [2]), expected=1, label="example 1"),
        TestCase(input=([1, 2, 3, 4], [1, 4]), expected=1, label="example 2"),
        TestCase(input=([1, 5], [2]), expected=3, label="example 3"),
    ]

    def solve(self, houses: list[int], heaters: list[int]) -> int:
        houses.sort()
        heaters.sort()
        result = 0
        i = j = 0
        while i < len(houses):
            while j + 1 < len(heaters) and abs(houses[i] - heaters[j]) >= abs(
                houses[i] - heaters[j + 1]
            ):
                j += 1
            result = max(result, abs(houses[i] - heaters[j]))
            i += 1
        return result


if __name__ == "__main__":
    Solution().run()
