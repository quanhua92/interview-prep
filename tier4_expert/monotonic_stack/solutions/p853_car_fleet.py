"""P853: Car Fleet (Medium)

TODO: Implement solve() below.
Hint: Sort by position desc, calculate time to target. A car forms a new fleet only if it arrives before the current fleet.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "853. Car Fleet"
    test_cases = [
        TestCase(input=(12, [10,8,0,5,3], [2,4,1,1,3]), expected=3, label="example 1"),
        TestCase(input=(10, [3], [3]), expected=1, label="example 2"),
        TestCase(input=(100, [0,2,4], [4,2,1]), expected=1, label="all merge"),
    ]

    def solve(self, target: int, position: list[int], speed: list[int]) -> int:
        # Pair position with speed, sort by position descending
        cars = sorted(zip(position, speed), key=lambda x: -x[0])
        fleets = 0
        slowest_time = -1.0

        for pos, spd in cars:
            time = (target - pos) / spd
            if time > slowest_time:
                fleets += 1
                slowest_time = time

        return fleets


if __name__ == "__main__":
    Solution().run()
