"""
P853: Car Fleet (Medium)
https://leetcode.com/problems/car-fleet/
Topics: Array, Stack, Sorting, Monotonic Stack

There are n cars at given miles away from the starting mile 0, traveling to reach the mile target.
You are given two integer arrays position and speed, both of length n, where position[i] is the starting mile of the ith car and speed[i] is the speed of the ith car in miles per hour.
A car cannot pass another car, but it can catch up and then travel next to it at the speed of the slower car.
A car fleet is a car or cars driving next to each other. The speed of the car fleet is the minimum speed of any car in the fleet.
If a car catches up to a car fleet at the mile target, it will still be considered as part of the car fleet.
Return the number of car fleets that will arrive at the destination.

Example 1:
    Input: target = 12, position = [10,8,0,5,3], speed = [2,4,1,1,3]
    Output: 3
    Explanation:

Example 2:
    Input: target = 10, position = [3], speed = [3]
    Output: 1
    Explanation:

Example 3:
    Input: target = 100, position = [0,2,4], speed = [4,2,1]
    Output: 1
    Explanation:

Constraints:
    - n == position.length == speed.length
    - 1 <= n <= 105
    - 0 < target <= 106
    - 0 <= position[i] < target
    - All the values of position are unique.
    - 0 < speed[i] <= 106

Template (python3):
    class Solution:
        def carFleet(self, target: int, position: List[int], speed: List[int]) -> int:

Hint: Sort by position desc, calculate time to target. A car forms a new fleet only if it arrives before the current fleet.
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "853. Car Fleet"
    test_cases = [
        TestCase(
            input=(12, [10, 8, 0, 5, 3], [2, 4, 1, 1, 3]), expected=3, label="example 1"
        ),
        TestCase(input=(10, [3], [3]), expected=1, label="example 2"),
        TestCase(input=(100, [0, 2, 4], [4, 2, 1]), expected=1, label="all merge"),
        TestCase(input=(10, [8, 0], [2, 1]), expected=2, label="two cars no merge"),
        TestCase(input=(10, [0, 3], [3, 2]), expected=1, label="two cars merge"),
        TestCase(input=(10, [1, 2, 3], [1, 1, 1]), expected=3, label="all same speed"),
    ]

    def solve(self, target: int, position: list[int], speed: list[int]) -> int:
        raise NotImplementedError(
            "TODO: Implement solve(self, target: int, position: list[int], speed: list[int]) -> int"
        )


if __name__ == "__main__":
    Solution().run()
