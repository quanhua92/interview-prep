/*
 * P452: Minimum Number of Arrows to Burst Balloons [PREMIUM] (Medium)
 * https://leetcode.com/problems/minimum-number-of-arrows-to-burst-balloons/
 * Topics: Array, Greedy, Sorting
 *
 * Given the array points, return the minimum number of arrows that must be shot to burst all balloons.
 */


#include "ctest.h"
#include <stdlib.h>

typedef long long ll;

int findMinArrowShots(int n, ll (*pts)[2]) {
    abort();
}

int main(void) {
    int header_n;
    int *header = read_ints(&header_n);
    free(header);
    ll pts[100000][2];
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
