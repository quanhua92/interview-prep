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
 *     - 0 < radius <= 108
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
#include "ctest.h"
#pragma GCC diagnostic pop
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    double radius, x_center, y_center;
} CircleSolver;

CircleSolver circle_new(double radius, double x_center, double y_center) {
    CircleSolver c = {radius, x_center, y_center};
    srand((unsigned)(time(NULL) * 1000 + (long)&c));
    return c;
}

void circle_rand_point(CircleSolver *c, double *out_x, double *out_y) {
    double r = c->radius;
    for (;;) {
        double x = ((double)rand() / RAND_MAX) * 2.0 - 1.0;
        double y = ((double)rand() / RAND_MAX) * 2.0 - 1.0;
        if (x * x + y * y <= 1.0) {
            *out_x = c->x_center + x * r;
            *out_y = c->y_center + y * r;
            return;
        }
    }
}

int main(void) {
    printf("\n============================================================\n");
    printf("  478. Generate Random Point in a Circle\n");
    printf("============================================================\n");
    struct { const char *label; double r, cx, cy; int count; } tests[] = {
        {"points within unit circle", 1.0, 0.0, 0.0, 1000},
        {"points within offset circle", 0.5, 1.0, 2.0, 1000},
        {"tiny circle", 0.01, 0.0, 0.0, 100},
        {"large offset center", 5.0, -100.0, 200.0, 500},
        {"single point", 1.0, 0.0, 0.0, 1},
    };
    int tc = (int)(sizeof(tests) / sizeof(tests[0]));
    int passed = 0;
    for (int i = 0; i < tc; i++) {
        CircleSolver solver = circle_new(tests[i].r, tests[i].cx, tests[i].cy);
        int in_circle = 1;
        for (int j = 0; j < tests[i].count; j++) {
            double px, py;
            circle_rand_point(&solver, &px, &py);
            double dx = px - tests[i].cx, dy = py - tests[i].cy;
            if (dx * dx + dy * dy > tests[i].r * tests[i].r + 1e-9) {
                in_circle = 0;
                break;
            }
        }
        if (in_circle) {
            passed++;
            printf("  Test %d (%s): PASS\n", i + 1, tests[i].label);
        } else {
            printf("  Test %d (%s): FAIL\n", i + 1, tests[i].label);
            printf("    Some points outside circle!\n");
        }
    }
    printf("\n  %d/%d passed\n", passed, tc);
    printf("============================================================\n\n");
    return passed == tc ? 0 : 1;
}
