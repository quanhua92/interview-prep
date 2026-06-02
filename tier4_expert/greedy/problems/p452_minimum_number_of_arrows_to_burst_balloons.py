"""
P452: Minimum Number of Arrows to Burst Balloons [PREMIUM] (Medium)
https://leetcode.com/problems/minimum-number-of-arrows-to-burst-balloons/
Topics: Array, Greedy, Sorting

Given the array points, return the minimum number of arrows that must be shot to burst all balloons.

Constraints:
    - 1 <= points.length <= 10^5
    - points[i].length == 2
    - -2^31 <= xstart < xend <= 2^31 - 1
"""

import sys

from src.wasm_libs.py.io import *


def solve(points: list[list[int]]) -> int:
    raise NotImplementedError


if __name__ == "__main__":
    _ = read_int()  # cols (not needed for logic)
    points = []
    for line in sys.stdin:
        line = line.strip()
        if line:
            points.append([int(x) for x in line.split()])
    result = solve(points)
    write_int(result)
