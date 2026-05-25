/**
 * P200: Number of Islands (Medium)
 * https://leetcode.com/problems/number-of-islands/
 * Topics: Array, Depth-First Search, Breadth-First Search, Union Find, Matrix
 * 
 * Given an m x n 2D binary grid grid which represents a map of '1's (land) and '0's (water), return the number of islands.
 * An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.
 * 
 * Example 1:
 *     Input: grid = [
 *       ["1","1","1","1","0"],
 *       ["1","1","0","1","0"],
 *       ["1","1","0","0","0"],
 *       ["0","0","0","0","0"]
 *     ]
 *     Output: 1
 * 
 * Example 2:
 *     Input: grid = [
 *       ["1","1","0","0","0"],
 *       ["1","1","0","0","0"],
 *       ["0","0","1","0","0"],
 *       ["0","0","0","1","1"]
 *     ]
 *     Output: 3
 * 
 * Constraints:
 *     - m == grid.length
 *     - n == grid[i].length
 *     - 1 <= m, n <= 300
 *     - grid[i][j] is '0' or '1'.
 * 
 * Template (python3):
 *     class Solution:
 *         def numIslands(self, grid: List[List[str]]) -> int:
 * 
 * Hint: Use DFS to mark visited land cells, counting each new island.
 */
function solve(grid)
  if (!grid || grid.length === 0 || grid[0].length === 0) return 0;
  const rows = grid.length;
  const cols = grid[0].length;
  let count = 0;

  function dfs(r, c)
    if (r < 0 || r >= rows || c < 0 || c >= cols || grid[r][c] !== "1") return;
    grid[r][c] = "0";
    dfs(r + 1, c);
    dfs(r - 1, c);
    dfs(r, c + 1);
    dfs(r, c - 1);
  }

  for (let r = 0; r < rows; r++)
    for (let c = 0; c < cols; c++)
      if (grid[r][c] === "1")
        count++;
        dfs(r, c);
      }
    }
  }
  return count; {
    throw new Error("NotImplementedError");
}

const tests = [
  {
    label: "example 1",
    input: [
      ["1", "1", "1", "1", "0"],
      ["1", "1", "0", "1", "0"],
      ["1", "1", "0", "0", "0"],
      ["0", "0", "0", "0", "0"],
    ],
    expected: 1,
  },
  {
    label: "example 2",
    input: [
      ["1", "1", "0", "0", "0"],
      ["1", "1", "0", "0", "0"],
      ["0", "0", "1", "0", "0"],
      ["0", "0", "0", "1", "1"],
    ],
    expected: 3,
  },
  { label: "empty grid", input: [[]], expected: 0 },
  { label: "single cell water", input: [["0"]], expected: 0 },
  { label: "single cell land", input: [["1"]], expected: 1 },
  { label: "single row", input: [["1", "0", "1", "0", "1"]], expected: 3 },
  { label: "single column", input: [["1"], ["0"], ["1"], ["0"], ["1"]], expected: 3 },
  {
    label: "all land 3x3",
    input: [
      ["1", "1", "1"],
      ["1", "1", "1"],
      ["1", "1", "1"],
    ],
    expected: 1,
  },
];
let passed = 0;
for (let i = 0; i < tests.length; i++) {
  const t = tests[i];
  const got = solve(t.input.map((row) => [...row]));
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
