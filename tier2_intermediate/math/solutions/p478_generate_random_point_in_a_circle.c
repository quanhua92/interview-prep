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


#include "io.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(void) {
    char *line = read_line();
    double radius, x_center, y_center;
    sscanf(line, "%lf %lf %lf", &radius, &x_center, &y_center);
    free(line);

    int n;
    int *count_arr = read_ints(&n);
    int count = count_arr[0];
    free(count_arr);

    srand((unsigned)time(NULL));

    for (int i = 0; i < count; i++) {
        double x, y;
        for (;;) {
            x = ((double)rand() / RAND_MAX) * 2.0 - 1.0;
            y = ((double)rand() / RAND_MAX) * 2.0 - 1.0;
            if (x * x + y * y <= 1.0) break;
        }
        printf("%.6f %.6f\n", x_center + x * radius, y_center + y * radius);
    }
    return 0;
}
