/*
 * P447: Number of Boomerangs [PREMIUM] (Medium)
 * https://leetcode.com/problems/number-of-boomerangs/
 * Topics: Array, Hash Table, Math
 *
 * You are given n points in the plane that are all distinct, where points[i] = [xi, yi]. A boomerang is a tuple of points (i, j, k) such that the distance between i and j equals the distance between i and k (the order of the tuple matters).
 * Return the number of boomerangs.
 * Example 1:
 *     Input: points = [[0,0],[1,0],[2,0]]
 *     Output: 2
 *     Explanation: The two boomerangs are [[1,0],[0,0],[2,0]] and [[1,0],[2,0],[0,0]].
 *
 * Example 2:
 *     Input: points = [[1,1],[2,2],[3,3]]
 *     Output: 2
 *
 * Example 3:
 *     Input: points = [[1,1]]
 *     Output: 0
 *
 * Constraints:
 *     - n == points.length
 *     - 1 <= n <= 500
 *     - points[i].length == 2
 *     - -10^4 <= xi, yi <= 10^4
 *     - All the points are unique.
 *
 * Template (python3):
 *     class Solution:
 *         def numberOfBoomerangs(self, points: List[List[int]]) -> int:
 */


#include "io.h"
#include <stdlib.h>

static int cmp_int(const void *a, const void *b) { return *(const int *)a - *(const int *)b; }
    abort();
}

static int numberOfBoomerangs(int points[][2], int n)
{
    abort();
}

int main(void)
{
    int cnt;
    int *header = read_ints(&cnt);
    int n = header[0];
    free(header);

    int points[500][2];
    for (int i = 0; i < n; i++) {
        int *row = read_ints(&cnt);
        points[i][0] = row[0];
        points[i][1] = row[1];
        free(row);
    }
    write_int(numberOfBoomerangs(points, n));
    return 0;
}
