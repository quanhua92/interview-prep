/*
 * P452: Minimum Number of Arrows to Burst Balloons [PREMIUM] (Medium)
 * https://leetcode.com/problems/minimum-number-of-arrows-to-burst-balloons/
 * Topics: Array, Greedy, Sorting
 *
 * There are some spherical balloons taped onto a flat wall that represents the XY-plane. The balloons are represented as a 2D integer array points where points[i] = [xstart, xend] denotes a balloon whose horizontal diameter stretches between xstart and xend.
 * Given the array points, return the minimum number of arrows that must be shot to burst all balloons.
 *
 * Example 1:
 *     Input: points = [[10,16],[2,8],[1,6],[7,12]]
 *     Output: 2
 *
 * Example 2:
 *     Input: points = [[1,2],[3,4],[5,6],[7,8]]
 *     Output: 4
 *
 * Example 3:
 *     Input: points = [[1,2],[2,3],[3,4],[4,5]]
 *     Output: 2
 *
 * Constraints:
 *     - 1 <= points.length <= 10^5
 *     - points[i].length == 2
 *     - -2^31 <= xstart < xend <= 2^31 - 1
 *
 * Template (python3):
 *     class Solution:
 *         def findMinArrowShots(self, points: List[List[int]]) -> int:
 */


#include "io.h"
#include <stdlib.h>

typedef long long ll;

int cmp_ll(const void *a, const void *b) {
    ll va = *(const ll *)a, vb = *(const ll *)b;
    return (va > vb) - (va < vb);
}

int findMinArrowShots(int n, ll (*pts)[2]) {
    abort();
}

int main(void) {
    int header_n;
    int *header = read_ints(&header_n);
    free(header);
    static ll pts[100000][2];
    int n = 0;
    while (1) {
        int row_n;
        int *row = read_ints(&row_n);
        if (row_n == 0) { free(row); break; }
        pts[n][0] = (ll)row[0];
        pts[n][1] = (ll)row[1];
        n++;
        free(row);
    }
    int result = findMinArrowShots(n, pts);
    write_int(result);
    return 0;
}
