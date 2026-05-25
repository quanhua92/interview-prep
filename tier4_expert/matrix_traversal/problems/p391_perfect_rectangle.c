/*
 * P391: Perfect Rectangle [PREMIUM] (Hard)
 * https://leetcode.com/problems/perfect-rectangle/
 * Topics: Array, Hash Table, Math, Geometry, Line Sweep
 * 
 * Given an array rectangles where rectangles[i] = [xi, yi, ai, bi] represents an axis-aligned rectangle. The bottom-left point of the rectangle is (xi, yi) and the top-right point of it is (ai, bi).
 * Return true if all the rectangles together form an exact cover of a rectangular region.
 * Example 1:
 *     Input: rectangles = [[1,1,3,3],[3,1,4,2],[3,2,4,4],[1,3,2,4],[2,3,3,4]]
 *     Output: true
 *     Explanation: All 5 rectangles together form an exact cover of a rectangular region.
 * 
 * Example 2:
 *     Input: rectangles = [[1,1,2,3],[1,3,2,4],[3,1,4,2],[3,2,4,4]]
 *     Output: false
 *     Explanation: Because there is a gap between the two rectangular regions.
 * 
 * Example 3:
 *     Input: rectangles = [[1,1,3,3],[3,1,4,2],[1,3,2,4],[2,2,4,4]]
 *     Output: false
 *     Explanation: Because two of the rectangles overlap with each other.
 * 
 * Constraints:
 *     - 1 <= rectangles.length <= 2 * 104
 *     - rectangles[i].length == 4
 *     - -105 <= xi < ai <= 105
 *     - -105 <= yi < bi <= 105
 * 
 * Template (python3):
 *     class Solution:
 *         def isRectangleCover(self, rectangles: List[List[int]]) -> bool:
 */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#include "ctest.h"
#pragma GCC diagnostic pop
#include <stdbool.h>
#include <stdlib.h>

typedef long long ll;

typedef struct {
    ll x, y;
} Point;

static bool isRectangleCover(const int *rects, int n)
{
    /* TODO: Implement */
    return 0;
}

typedef struct {
    const char *label;
    const int *rects;
    int n;
    bool expected;
} RectTC;

int main(void)
{
    int r1[] = {1,1,3,3, 3,1,4,2, 3,2,4,4, 1,3,2,4, 2,3,3,4};
    int r2[] = {1,1,2,3, 1,3,2,4, 3,1,4,2, 3,2,4,4};
    int r3[] = {1,1,3,3, 3,1,4,2, 1,3,2,4, 2,2,4,4};
    int r4[] = {0,0,1,1};
    int r5[] = {0,0,1,2, 1,0,2,2};
    int r6[] = {0,0,2,2, 1,1,3,3};

    RectTC tests[] = {
        {"example 1", r1, 5, true},
        {"example 2", r2, 4, false},
        {"example 3", r3, 4, false},
        {"single rectangle", r4, 1, true},
        {"two rects side by side", r5, 2, true},
        {"overlapping rectangles", r6, 2, false},
    };

    int n_tests = (int)(sizeof(tests) / sizeof(tests[0]));
    printf("\n============================================================\n");
    printf("  391. Perfect Rectangle\n");
    printf("============================================================\n");
    int passed = 0;
    for (int t = 0; t < n_tests; t++) {
        RectTC *tc = &tests[t];
        bool got = isRectangleCover(tc->rects, tc->n);
        if (got == tc->expected) {
            passed++;
            printf("  Test %d (%s): PASS\n", t + 1, tc->label);
        } else {
            printf("  Test %d (%s): FAIL\n", t + 1, tc->label);
            printf("    Expected: %s\n", tc->expected ? "true" : "false");
            printf("    Got:      %s\n", got ? "true" : "false");
        }
    }
    printf("\n  %d/%d passed\n", passed, n_tests);
    printf("============================================================\n\n");
    return passed == n_tests ? 0 : 1;
}
