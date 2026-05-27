/*
 * P407: Trapping Rain Water II [PREMIUM] (Hard)
 * https://leetcode.com/problems/trapping-rain-water-ii/
 * Topics: Array, Breadth-First Search, Heap (Priority Queue), Matrix
 *
 * Given an m x n integer matrix heightMap representing the height of each unit cell in a 2D elevation map, return the volume of water it can trap after raining.
 * Example 1:
 *     Input: heightMap = [[1,4,3,1,3,2],[3,2,1,3,2,4],[2,3,3,2,3,1]]
 *     Output: 4
 *     Explanation: After the rain, water is trapped between the blocks.
 *     We have two small ponds 1 and 3 units trapped.
 *     The total volume of water trapped is 4.
 *
 * Example 2:
 *     Input: heightMap = [[3,3,3,3,3],[3,2,2,2,3],[3,2,1,2,3],[3,2,2,2,3],[3,3,3,3,3]]
 *     Output: 10
 *
 * Constraints:
 *     - m == heightMap.length
 *     - n == heightMap[i].length
 *     - 1 <= m, n <= 200
 *     - 0 <= heightMap[i][j] <= 2 * 104
 *
 * Template (python3):
 *     class Solution:
 *         def trapRainWater(self, heightMap: List[List[int]]) -> int:
 */

#include "io.h"
#include <stdlib.h>

static int trapRainWater(int *heightMap, int m, int n)
{
    abort();
    return 0;
}

int main(void)
{
    int dims_len;
    int *dims = read_ints(&dims_len);
    int m = dims[0], n = dims[1];
    free(dims);
    int *flat = malloc(m * n * sizeof(int));
    for (int r = 0; r < m; r++) {
        int row_len;
        int *row = read_ints(&row_len);
        for (int c = 0; c < n; c++) flat[r * n + c] = row[c];
        free(row);
    }
    int result = trapRainWater(flat, m, n);
    write_int(result);
    free(flat);
    return 0;
}
