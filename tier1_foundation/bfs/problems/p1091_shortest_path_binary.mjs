/**
 * P1091: Shortest Path in Binary Matrix (Medium)
 * https://leetcode.com/problems/shortest-path-in-binary-matrix/
 * Topics: Array, Breadth-First Search, Matrix
 *
 * Given an n x n binary matrix grid, return the length of the shortest clear path in the matrix. If there is no clear path, return -1.
 * A clear path in a binary matrix is a path from the top-left cell (i.e., (0, 0)) to the bottom-right cell (i.e., (n - 1, n - 1)) such that:
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

function solve(input) {
  throw new Error("NotImplementedError");
}

// --- tests ---
const tests = [
  { label: "example 1", input: [[0, 1], [1, 0]], expected: 2 },
  { label: "example 2", input: [[0, 0, 0], [1, 1, 0], [1, 1, 0]], expected: 4 },
  { label: "blocked", input: [[1, 0], [0, 1]], expected: -1 },
  { label: "single cell", input: [[0]], expected: 1 },
  { label: "3x3 all open (diagonal)", input: [[0, 0, 0], [0, 0, 0], [0, 0, 0]], expected: 3 },
  { label: "2x2 all open (diagonal)", input: [[0, 0], [0, 0]], expected: 2 },
  { label: "3x3 only corners open", input: [[0, 1, 1], [1, 1, 1], [1, 1, 0]], expected: -1 },
];
let passed = 0;
for (let i = 0; i < tests.length; i++) {
  const t = tests[i];
  const got = solve(t.input);
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
