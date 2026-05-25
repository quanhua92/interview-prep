/*
 * P576: Out of Boundary Paths [PREMIUM] (Medium)
 * https://leetcode.com/problems/out-of-boundary-paths/
 * Topics: Dynamic Programming
 * 
 * There is an m x n grid with a ball. The ball is initially at the position [startRow, startColumn]. You are allowed to move the ball to one of the four adjacent cells in the grid (possibly out of the grid crossing the grid boundary). You can apply at most maxMove moves to the ball.
 * Given the five integers m, n, maxMove, startRow, startColumn, return the number of paths to move the ball out of the grid boundary. Since the answer can be very large, return it modulo 109 + 7.
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
#include "cpptest.h"
#include <vector>
#include <cstring>

int findPaths(int m, int n, int maxMove, int startRow, int startColumn) {
    abort();
}

int main() {
    struct TC { const char *label; int m; int n; int mm; int sr; int sc; int expected; };
    std::vector<TC> tests = {
        {"example 1", 2, 2, 2, 0, 0, 6},
        {"example 2", 1, 3, 3, 0, 1, 12},
        {"1x1 grid single move", 1, 1, 1, 0, 0, 4},
        {"corner 1 move", 2, 2, 1, 0, 0, 2},
        {"zero moves", 3, 3, 0, 1, 1, 0},
    };
    int total = (int)tests.size();
    int passed = 0;
    for (int i = 0; i < total; i++) {
        int got = findPaths(tests[i].m, tests[i].n, tests[i].mm, tests[i].sr, tests[i].sc);
        if (got == tests[i].expected) {
            passed++;
            printf("  Test %d (%s): PASS\n", i + 1, tests[i].label);
        } else {
            printf("  Test %d (%s): FAIL (expected %d, got %d)\n", i + 1, tests[i].label, tests[i].expected, got);
        }
    }
    printf("\n  %d/%d passed\n", passed, total);
    return passed == total ? 0 : 1;
}
