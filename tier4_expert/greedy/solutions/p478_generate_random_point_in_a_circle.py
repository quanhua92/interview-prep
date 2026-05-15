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
    - 0 < radius <= 108
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

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "478. Generate Random Point in a Circle"
    test_cases = [
        TestCase(
            input={"radius": 1.0, "x_center": 0.0, "y_center": 0.0, "count": 1000},
            expected="in_circle",
            label="points within unit circle",
        ),
        TestCase(
            input={"radius": 0.5, "x_center": 1.0, "y_center": 2.0, "count": 1000},
            expected="in_circle",
            label="points within offset circle",
        ),
    ]

    def solve(self, radius: float, x_center: float, y_center: float, count: int) -> list[list[float]]:
        import random

        points = []
        for _ in range(count):
            while True:
                x = random.uniform(-1, 1)
                y = random.uniform(-1, 1)
                if x * x + y * y <= 1:
                    break
            points.append([x_center + x * radius, y_center + y * radius])
        return points

    def run(self) -> bool:
        print(f"\n{'=' * 60}")
        print(f"  {self.name}")
        print(f"{'=' * 60}")

        all_passed = True
        for i, tc in enumerate(self.test_cases, 1):
            label = f" ({tc.label})" if tc.label else ""
            inp = tc.input
            points = self.solve(inp["radius"], inp["x_center"], inp["y_center"], inp["count"])
            r = inp["radius"]
            cx, cy = inp["x_center"], inp["y_center"]
            in_circle = all(
                (p[0] - cx) ** 2 + (p[1] - cy) ** 2 <= r * r + 1e-9 for p in points
            )
            passed = in_circle and len(points) == inp["count"]
            status = "PASS" if passed else "FAIL"
            if not passed:
                all_passed = False
            print(f"  Test {i}{label}: {status}")
            if not in_circle:
                print("    Some points outside circle!")

        total = len(self.test_cases)
        passed_count = total if all_passed else 0
        print(f"\n  {passed_count}/{total} passed")
        print(f"{'=' * 60}\n")
        return all_passed


if __name__ == "__main__":
    Solution().run()
