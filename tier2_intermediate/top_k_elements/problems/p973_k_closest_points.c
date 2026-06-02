/*
 * P973: K Closest Points to Origin (Medium)
 * https://leetcode.com/problems/k-closest-points-to-origin/
 * Topics: Array, Math, Divide and Conquer, Geometry, Sorting, Heap (Priority Queue), Quickselect
 *
 * Given an array of points where points[i] = [xi, yi] represents a point on the X-Y plane and an integer k, return the k closest points to the origin (0, 0).
 * The distance between two points on the X-Y plane is the Euclidean distance (i.e., sqrt((x1 - x2)^2 + (y1 - y2)^2)).
 * You may return the answer in any order. The answer is guaranteed to be unique (except for the order that it is in).
 *
 * Example 1:
 *     Input: points = [[1,3],[-2,2]], k = 1
 *     Output: [[-2,2]]
 *     Explanation:
 *     The distance between (1, 3) and the origin is sqrt(10).
 *     The distance between (-2, 2) and the origin is sqrt(8).
 *     Since sqrt(8) < sqrt(10), (-2, 2) is closer to the origin.
 *     We only want the closest k = 1 points from the origin, so the answer is just [[-2,2]].
 *
 * Example 2:
 *     Input: points = [[3,3],[5,-1],[-2,4]], k = 2
 *     Output: [[3,3],[-2,4]]
 *     Explanation: The answer [[-2,4],[3,3]] would also be accepted.
 *
 * Constraints:
 *     - 1 <= k <= points.length <= 10^4
 *     - -10^4 <= xi, yi <= 10^4
 *
 * Template (python3):
 *     class Solution:
 *         def kClosest(self, points: List[List[int]], k: int) -> List[List[int]]:
 *
 * Hint: Use a max-heap of size k keyed by negative distance squared.
 */

#include "io.h"
#include <stdlib.h>
#include <string.h>

typedef struct { int x, y; } Pt;

static int cmp_dist(const void *a, const void *b)
{
    abort();
}

static int cmp_lex(const void *a, const void *b)
{
    abort();
}

int main(void)
{
    int flat_len;
    int *flat = read_ints(&flat_len);
    int npoints = flat_len / 2;
    Pt *pts = malloc(npoints * sizeof(Pt));
    for (int i = 0; i < npoints; i++) {
        pts[i].x = flat[2 * i];
        pts[i].y = flat[2 * i + 1];
    }
    free(flat);

    int k_len;
    int *k_arr = read_ints(&k_len);
    int k = k_arr[0];
    free(k_arr);

    qsort(pts, npoints, sizeof(Pt), cmp_dist);
    qsort(pts, k, sizeof(Pt), cmp_lex);

    for (int i = 0; i < k; i++) {
        int pt[2] = {pts[i].x, pts[i].y};
        write_ints(pt, 2);
    }

    free(pts);
    return 0;
}
