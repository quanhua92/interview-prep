/*
 * P1091: Shortest Path in Binary Matrix (Medium)
 * https://leetcode.com/problems/shortest-path-in-binary-matrix/
 * Topics: Array, Breadth-First Search, Matrix
 *
 * Given an n x n binary matrix grid, return the length of the shortest clear path in the matrix. If there is no clear path, return -1.
 * A clear path in a binary matrix is a path from the top-left cell (i.e., (0, 0)) to the bottom-right cell (i.e., (n - 1, n - 1)) such that:
 * - All the cells in the binary matrix are either 0 (walkable) or 1 (blocked).
 * - All the visited cells of the path are 0.
 * - All the adjacent cells of the path are 8-directionally connected (i.e., they are different and they share an edge or a corner).
 * The length of a clear path is the number of visited cells of this path.
 *
 * Example 1:
 *     Input: grid = [[0,1],[1,0]]
 *     Output: 2
 *
 * Example 2:
 *     Input: grid = [[0,0,0],[1,1,0],[1,1,0]]
 *     Output: 4
 *
 * Example 3:
 *     Input: grid = [[1,0,0],[1,1,0],[1,1,0]]
 *     Output: -1
 *
 * Constraints:
 *     - n == grid.length
 *     - n == grid[i].length
 *     - 1 <= n <= 100
 *     - grid[i][j] is 0 or 1
 *
 * Hints:
 *     - Do a breadth first search to find the shortest path.
 *
 * Template (python3):
 *     class Solution:
 *         def shortestPathBinaryMatrix(self, grid: List[List[int]]) -> int:
 *
 * Hint: BFS from (0,0) with 8 directions, return distance to (n-1,n-1) or -1.
 */

#include "io.h"
#include <cstdlib>
#include <queue>
#include <tuple>

using namespace std;

static int solve(vector<vector<int>> &grid) {
    int n = (int)grid.size();
    if (grid[0][0] == 1 || grid[n - 1][n - 1] == 1) return -1;
    if (n == 1) return 1;
    queue<tuple<int,int,int>> q;
    q.push({0, 0, 1});
    grid[0][0] = 1;
    int dr[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dc[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    while (!q.empty()) {
        auto [r, c, dist] = q.front();
        q.pop();
        for (int d = 0; d < 8; d++) {
            int nr = r + dr[d];
            int nc = c + dc[d];
            if (nr >= 0 && nr < n && nc >= 0 && nc < n && grid[nr][nc] == 0) {
                if (nr == n - 1 && nc == n - 1) return dist + 1;
                grid[nr][nc] = 1;
                q.push({nr, nc, dist + 1});
            }
        }
    }
    return -1;
}

int main(void)
{
    int n = read_int();
    (void)n;
    vector<vector<int>> grid;
    for (int i = 0; i < n; i++) {
        grid.push_back(read_ints());
    }
    write_int(solve(grid));
    return 0;
}
