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
    Point corners[80000];
    int nc = 0;
    ll total_area = 0;
    ll min_x = 200000LL, min_y = 200000LL;
    ll max_x = -200000LL, max_y = -200000LL;

    for (int i = 0; i < n; i++) {
        ll x1 = rects[i * 4 + 0];
        ll y1 = rects[i * 4 + 1];
        ll x2 = rects[i * 4 + 2];
        ll y2 = rects[i * 4 + 3];
        if (x1 < min_x) min_x = x1;
        if (y1 < min_y) min_y = y1;
        if (x2 > max_x) max_x = x2;
        if (y2 > max_y) max_y = y2;
        total_area += (x2 - x1) * (y2 - y1);

        Point pts[4] = {{x1,y1},{x1,y2},{x2,y1},{x2,y2}};
        for (int p = 0; p < 4; p++) {
            int found = -1;
            for (int k = 0; k < nc; k++) {
                if (corners[k].x == pts[p].x && corners[k].y == pts[p].y) {
                    found = k;
                    break;
                }
            }
            if (found >= 0) {
                corners[found] = corners[--nc];
            } else {
                corners[nc++] = pts[p];
            }
        }
    }

    if (nc != 4) return false;
    Point exp[4] = {{min_x,min_y},{min_x,max_y},{max_x,min_y},{max_x,max_y}};
    for (int i = 0; i < 4; i++) {
        int found = 0;
        for (int k = 0; k < nc; k++) {
            if (corners[k].x == exp[i].x && corners[k].y == exp[i].y) {
                found = 1;
                break;
            }
        }
        if (!found) return false;
    }

    return total_area == (max_x - min_x) * (max_y - min_y);
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
