"""
P478: Generate Random Point in a Circle [PREMIUM] (Medium)
https://leetcode.com/problems/generate-random-point-in-a-circle/
Topics: Math, Geometry, Rejection Sampling, Randomized

Given the radius and the position of the center of a circle, implement the function randPoint which generates a uniform random point inside the circle.
Implement the Solution class:
Example 1:
    Input
Example 1:
    ["Solution", "randPoint", "randPoint", "randPoint"]
    [[1.0, 0.0, 0.0], [], [], []]
    Output
    [null, [-0.02493, -0.38077], [0.82314, 0.38945], [0.36572, 0.17248]]

    Explanation
    Solution solution = new Solution(1.0, 0.0, 0.0);
    solution.randPoint(); // return [-0.02493, -0.38077]
    solution.randPoint(); // return [0.82314, 0.38945]
    solution.randPoint(); // return [0.36572, 0.17248]

Constraints:
    - 0 < radius <= 108
    - -107 <= x_center, y_center <= 107
    - At most 3 * 104 calls will be made to randPoint.

Template (python3):
    class Solution:

        def __init__(self, radius: float, x_center: float, y_center: float):


        def randPoint(self) -> List[float]:



    # Your Solution object will be instantiated and called as such:
    # obj = Solution(radius, x_center, y_center)
    # param_1 = obj.randPoint()
"""

from src.wasm_libs.py.io import *


def solve(radius: float, x_center: float, y_center: float, count: int) -> list[list[float]]:
    import random
    random.seed(42)

    points = []
    for _ in range(count):
        while True:
            x = random.uniform(-1, 1)
            y = random.uniform(-1, 1)
            if x * x + y * y <= 1:
                break
        points.append([x_center + x * radius, y_center + y * radius])
    return points


if __name__ == "__main__":
    params = read_line().split()
    radius = float(params[0])
    x_center = float(params[1])
    y_center = float(params[2])
    count = read_int()
    points = solve(radius, x_center, y_center, count)
    for p in points:
        print(f"{p[0]} {p[1]}")
