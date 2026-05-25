/**
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

function solve(m, n, maxMove, startRow, startColumn) {
  const mod = 10 ** 9 + 7;
  const dp = Array.from({ length: maxMove + 1 }, () =>
    Array.from({ length: m }, () => new Array(n).fill(0))
  );
  const dirs = [[-1, 0], [1, 0], [0, -1], [0, 1]];
  dp[0][startRow][startColumn] = 1;
  let result = 0;
  for (let move = 0; move < maxMove; move++) {
    for (let r = 0; r < m; r++) {
      for (let c = 0; c < n; c++) {
        if (dp[move][r][c] === 0) continue;
        for (const [dr, dc] of dirs) {
          const nr = r + dr;
          const nc = c + dc;
          if (nr >= 0 && nr < m && nc >= 0 && nc < n) {
            dp[move + 1][nr][nc] = (dp[move + 1][nr][nc] + dp[move][r][c]) % mod;
          } else {
            result = (result + dp[move][r][c]) % mod;
          }
        }
      }
    }
  }
  return result;
}

const tests = [
  { label: "example 1", input: [2, 2, 2, 0, 0], expected: 6 },
  { label: "example 2", input: [1, 3, 3, 0, 1], expected: 12 },
  { label: "1x1 grid single move", input: [1, 1, 1, 0, 0], expected: 4 },
  { label: "corner 1 move", input: [2, 2, 1, 0, 0], expected: 2 },
  { label: "zero moves", input: [3, 3, 0, 1, 1], expected: 0 },
];
let passed = 0;
for (let i = 0; i < tests.length; i++) {
  const t = tests[i];
  const got = solve(...t.input);
  if (JSON.stringify(got) === JSON.stringify(t.expected)) {
    passed++;
    console.log(`  Test ${i + 1} (${t.label}): PASS`);
  } else {
    console.log(`  Test ${i + 1} (${t.label}): FAIL`);
    console.log(`    Expected: ${JSON.stringify(t.expected)}\n    Got:      ${JSON.stringify(got)}`);
  }
}
console.log(`\n  ${passed}/${tests.length} passed`);
process.exit(passed === tests.length ? 0 : 1);
