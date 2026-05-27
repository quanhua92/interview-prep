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
#include <cstdio>
#include <vector>

int main(void)
{
    std::vector<int> header = read_ints();
    int cols = header[0];
    std::vector<std::vector<int>> grid(cols);
    for (int i = 0; i < cols; i++) {
        grid[i] = read_ints();
    }
    abort();
    return 0;
}
