/**
 * P463: Island Perimeter [PREMIUM] (Easy)
 * https://leetcode.com/problems/island-perimeter/
 * Topics: Array, Depth-First Search, Breadth-First Search, Matrix
 * 
 * You are given row x col grid representing a map where grid[i][j] = 1 represents land and grid[i][j] = 0 represents water.
 * Grid cells are connected horizontally/vertically (not diagonally). The grid is completely surrounded by water, and there is exactly one island (i.e., one or more connected land cells).
 * The island doesn't have "lakes", meaning the water inside isn't connected to the water around the island. One cell is a square with side length 1. The grid is rectangular, width and height don't exceed 100. Determine the perimeter of the island.
 * Example 1:
 *     Input: grid = [[0,1,0,0],[1,1,1,0],[0,1,0,0],[1,1,0,0]]
 *     Output: 16
 *     Explanation: The perimeter is the 16 yellow stripes in the image above.
 * 
 * Example 2:
 *     Input: grid = [[1]]
 *     Output: 4
 * 
 * Example 3:
 *     Input: grid = [[1,0]]
 *     Output: 4
 * 
 * Constraints:
 *     - row == grid.length
 *     - col == grid[i].length
 *     - 1 <= row, col <= 100
 *     - grid[i][j] is 0 or 1.
 *     - There is exactly one island in grid.
 * 
 * Template (python3):
 *     class Solution:
 *         def islandPerimeter(self, grid: List[List[int]]) -> int:
 */
function islandPerimeter(grid)
  const rows = grid.length;
  const cols = grid[0].length;
  const visited = new Set();
  let perimeter = 0;
  const directions = [[0, 1], [0, -1], [1, 0], [-1, 0]];

  for (let r = 0; r < rows; r++)
    for (let c = 0; c < cols; c++)
      if (grid[r][c] === 1)
        const queue = [[r, c]];
        visited.add(`${r},${c}`);
        while (queue.length > 0)
          const [cr, cc] = queue.shift();
          for (const [dr, dc] of directions)
            const nr = cr + dr;
            const nc = cc + dc;
            if (nr < 0 || nr >= rows || nc < 0 || nc >= cols || grid[nr][nc] === 0)
              perimeter++;
            } else if (!visited.has(`${nr},${nc}`))
              visited.add(`${nr},${nc}`);
              queue.push([nr, nc]);
            }
          }
        }
        return perimeter;
      }
    }
  }
  return 0; {
    throw new Error("NotImplementedError");
}

function solve(input)
  return islandPerimeter(input); {
    throw new Error("NotImplementedError");
}

// --- tests ---
const tests = [
  { label: "example 1", input: [[0, 1, 0, 0], [1, 1, 1, 0], [0, 1, 0, 0], [1, 1, 0, 0]], expected: 16 },
  { label: "example 2", input: [[1]], expected: 4 },
  { label: "example 3", input: [[1, 0]], expected: 4 },
  { label: "horizontal line of 3", input: [[1, 1, 1]], expected: 8 },
  { label: "vertical line of 3", input: [[1], [1], [1]], expected: 8 },
  { label: "2x2 block", input: [[1, 1], [1, 1]], expected: 8 },
  { label: "3x2 block", input: [[1, 1, 1], [1, 1, 1]], expected: 10 },
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
