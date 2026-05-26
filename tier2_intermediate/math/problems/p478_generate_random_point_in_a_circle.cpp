/*
 * P478: Generate Random Point in a Circle [PREMIUM] (Medium)
 * https://leetcode.com/problems/generate-random-point-in-a-circle/
 * Topics: Math, Geometry, Rejection Sampling, Randomized
 * 
 * Given the radius and the position of the center of a circle, implement the function randPoint which generates a uniform random point inside the circle.
 * Implement the Solution class:
 * Example 1:
 *     Input
 * Example 1:
 *     ["Solution", "randPoint", "randPoint", "randPoint"]
 *     [[1.0, 0.0, 0.0], [], [], []]
 *     Output
 *     [null, [-0.02493, -0.38077], [0.82314, 0.38945], [0.36572, 0.17248]]
 * 
 *     Explanation
 *     Solution solution = new Solution(1.0, 0.0, 0.0);
 *     solution.randPoint(); // return [-0.02493, -0.38077]
 *     solution.randPoint(); // return [0.82314, 0.38945]
 *     solution.randPoint(); // return [0.36572, 0.17248]
 * 
 * Constraints:
 *     - 0 < radius <= 108
 *     - -107 <= x_center, y_center <= 107
 *     - At most 3 * 104 calls will be made to randPoint.
 * 
 * Template (python3):
 *     class Solution:
 * 
 *         def __init__(self, radius: float, x_center: float, y_center: float):
 * 
 * 
 *         def randPoint(self) -> List[float]:
 * 
 * 
 * 
 *     # Your Solution object will be instantiated and called as such:
 *     # obj = Solution(radius, x_center, y_center)
 *     # param_1 = obj.randPoint()
 */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#include "cpptest.h"
#pragma GCC diagnostic pop
#include <cmath>
#include <random>

struct CircleSolver {
    double radius, x_center, y_center;
    std::mt19937 rng;
    std::uniform_real_distribution<double> dist{-1.0, 1.0};
    CircleSolver(double r, double x, double y) : radius(r), x_center(x), y_center(y), rng(std::random_device{}()) {}
    std::pair<double, double> randPoint() {
        abort();
    }
};

int main() {
    printf("\n============================================================\n");
    printf("  478. Generate Random Point in a Circle\n");
    printf("============================================================\n");
    struct T { const char *label; double r, cx, cy; int count; };
    std::vector<T> tests = {
        {"points within unit circle", 1.0, 0.0, 0.0, 1000},
        {"points within offset circle", 0.5, 1.0, 2.0, 1000},
        {"tiny circle", 0.01, 0.0, 0.0, 100},
        {"large offset center", 5.0, -100.0, 200.0, 500},
        {"single point", 1.0, 0.0, 0.0, 1},
    };
    int passed = 0;
    for (int i = 0; i < (int)tests.size(); i++) {
        CircleSolver solver(tests[i].r, tests[i].cx, tests[i].cy);
        bool ok = true;
        for (int j = 0; j < tests[i].count; j++) {
            auto [px, py] = solver.randPoint();
            double dx = px - tests[i].cx, dy = py - tests[i].cy;
            if (dx * dx + dy * dy > tests[i].r * tests[i].r + 1e-9) { ok = false; break; }
        }
        if (ok) { passed++; printf("  Test %d (%s): PASS\n", i + 1, tests[i].label); }
        else { printf("  Test %d (%s): FAIL\n", i + 1, tests[i].label); printf("    Some points outside circle!\n"); }
    }
    printf("\n  %d/%d passed\n", passed, (int)tests.size());
    printf("============================================================\n\n");
    return passed == (int)tests.size() ? 0 : 1;
}
