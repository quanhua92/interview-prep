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
 *     - 1 <= rectangles.length <= 2 * 10^4
 *     - rectangles[i].length == 4
 *     - -10^5 <= xi < ai <= 10^5
 *     - -10^5 <= yi < bi <= 10^5
 *
 * Template (python3):
 *     class Solution:
 *         def isRectangleCover(self, rectangles: List[List[int]]) -> bool:
 */


#include "io.h"
#include <stdbool.h>
#include <stdlib.h>

typedef long long ll;

typedef struct {
    ll x, y;
} Point;

static bool isRectangleCover(const int *flat, int n)
{
    abort();
}

int main(void)
{
    int cnt;
    int *header = read_ints(&cnt);
    int n = header[0];
    free(header);

    int *flat = malloc(n * 4 * sizeof(int));
    int total_read = 0;
    for (int i = 0; i < n; i++) {
        int rc;
        int *row = read_ints(&rc);
        for (int j = 0; j < rc; j++)
            flat[total_read++] = row[j];
        free(row);
    }
    write_bool(isRectangleCover(flat, n));
    free(flat);
    return 0;
}
