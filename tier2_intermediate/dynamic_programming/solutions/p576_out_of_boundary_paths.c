/*
 * P576: Out of Boundary Paths [PREMIUM] (Medium)
 * https://leetcode.com/problems/out-of-boundary-paths/
 * Topics: Dynamic Programming
 *
 * There is an m x n grid with a ball. The ball is initially at the position [startRow, startColumn]. You are allowed to move the ball to one of the four adjacent cells in the grid (possibly out of the grid crossing the grid boundary). You can apply at most maxMove moves to the ball.
 * Given the five integers m, n, maxMove, startRow, startColumn, return the number of paths to move the ball out of the grid boundary. Since the answer can be very large, return it modulo 10^9 + 7.
 * Example 1:
 *     Input: m = 2, n = 2, maxMove = 2, startRow = 0, startColumn = 0
 *     Output: 6
 *
 * Example 2:
 *     Input: m = 1, n = 3, maxMove = 3, startRow = 0, startColumn = 1
 *     Output: 12
 *
 * Constraints:
 *     - 1 <= m, n <= 50
 *     - 0 <= maxMove <= 50
 *     - 0 <= startRow < m
 *     - 0 <= startColumn < n
 *
 * Hint: Is traversing every path feasible? There are many possible paths for a small matrix. Try to optimize it.
 * Hint: Can we use some space to store the number of paths and update them after every move?
 * Hint: One obvious thing: the ball will go out of the boundary only by crossing it. Also, there is only one possible way the ball can go out of the boundary from the boundary cell except for corner cells. From the corner cell, the ball can go out in two different ways.
 *
 * Can you use this thing to solve the problem?
 *
 * Template (python3):
 *     class Solution:
 *         def findPaths(self, m: int, n: int, maxMove: int, startRow: int, startColumn: int) -> int:
 */

#include "io.h"
#include <stdlib.h>
#include <string.h>

int findPaths(int m, int n, int maxMove, int startRow, int startColumn) {
    int mod = 1000000007;
    int *dp = (int *)calloc(m * n, sizeof(int));
    int *next = (int *)calloc(m * n, sizeof(int));
    int dirs[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};
    dp[startRow * n + startColumn] = 1;
    long long result = 0;
    for (int move = 0; move < maxMove; move++) {
        memset(next, 0, m * n * sizeof(int));
        for (int r = 0; r < m; r++) {
            for (int c = 0; c < n; c++) {
                int val = dp[r * n + c];
                if (val == 0) continue;
                for (int d = 0; d < 4; d++) {
                    int nr = r + dirs[d][0];
                    int nc = c + dirs[d][1];
                    if (nr >= 0 && nr < m && nc >= 0 && nc < n) {
                        next[nr * n + nc] = (next[nr * n + nc] + val) % mod;
                    } else {
                        result = (result + val) % mod;
                    }
                }
            }
        }
        int *tmp = dp;
        dp = next;
        next = tmp;
    }
    free(dp);
    free(next);
    return (int)result;
}

int main(void) {
    int c1; int *a1 = read_ints(&c1); int m = a1[0]; free(a1);
    int c2; int *a2 = read_ints(&c2); int n = a2[0]; free(a2);
    int c3; int *a3 = read_ints(&c3); int mm = a3[0]; free(a3);
    int c4; int *a4 = read_ints(&c4); int sr = a4[0]; free(a4);
    int c5; int *a5 = read_ints(&c5); int sc = a5[0]; free(a5);
    write_int(findPaths(m, n, mm, sr, sc));
    return 0;
}
