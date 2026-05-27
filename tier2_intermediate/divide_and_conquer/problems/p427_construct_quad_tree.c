/*
 * P427: Construct Quad Tree [PREMIUM] (Medium)
 * https://leetcode.com/problems/construct-quad-tree/
 * Topics: Array, Divide and Conquer, Tree, Matrix
 *
 * Given a n * n matrix grid of 0's and 1's only. We want to represent grid with a Quad-Tree.
 * Return the root of the Quad-Tree representing grid.
 *
 * Constraints:
 *     - n == grid.length == grid[i].length
 *     - n == 2x where 0 <= x <= 6
 *
 * Hint: Recursively divide grid into 4 quadrants, make leaf if all same value.
 */

#include "io.h"
#include <stdlib.h>

int main(void)
{
    int cn;
    int *cdata = read_ints(&cn);
    int cols = cdata[0];
    free(cdata);

    int *grid = malloc(cols * cols * sizeof(int));
    for (int i = 0; i < cols; i++) {
        int rn;
        int *row = read_ints(&rn);
        for (int j = 0; j < rn; j++) grid[i * cols + j] = row[j];
        free(row);
    }

    abort();

    free(grid);
    return 0;
}
