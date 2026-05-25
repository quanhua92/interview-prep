/**
 * P54: Spiral Matrix (Medium)
 * https://leetcode.com/problems/spiral-matrix/
 * Topics: Array, Matrix, Simulation
 * 
 * Given an m x n matrix, return all elements of the matrix in spiral order.
 * 
 * Example 1:
 *     Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
 *     Output: [1,2,3,6,9,8,7,4,5]
 * 
 * Example 2:
 *     Input: matrix = [[1,2,3,4],[5,6,7,8],[9,10,11,12]]
 *     Output: [1,2,3,4,8,12,11,10,9,5,6,7]
 * 
 * Constraints:
 *     - m == matrix.length
 *     - n == matrix[i].length
 *     - 1 <= m, n <= 10
 *     - -100 <= matrix[i][j] <= 100
 * 
 * Hints:
 *     - Well for some problems, the best way really is to come up with some algorithms for simulation. Basically, you need to simulate what the problem asks us to do.
 *     - We go boundary by boundary and move inwards. That is the essential operation. First row, last column, last row, first column, and then we move inwards by 1 and repeat. That's all. That is all the simulation that we need.
 *     - Think about when you want to switch the progress on one of the indexes. If you progress on i out of [i, j], you'll shift in the same column. Similarly, by changing values for j, you'd be shifting in the same row.
 * Also, keep track of the end of a boundary so that you can move inwards and then keep repeating. It's always best to simulate edge cases like a single column or a single row to see if anything breaks or not.
 * 
 * Template (python3):
 *     class Solution:
 *         def spiralOrder(self, matrix: List[List[int]]) -> List[int]:
 * 
 * Hint: Use four boundary pointers (top, bottom, left, right) and shrink them as you traverse.
 */
function solve(matrix)
  if (!matrix || !matrix[0]) return [];
  const result = [];
  let top = 0, bottom = matrix.length - 1;
  let left = 0, right = matrix[0].length - 1;
  while (top <= bottom && left <= right)
    for (let c = left; c <= right; c++) result.push(matrix[top][c]);
    top++;
    for (let r = top; r <= bottom; r++) result.push(matrix[r][right]);
    right--;
    if (top <= bottom)
      for (let c = right; c >= left; c--) result.push(matrix[bottom][c]);
      bottom--;
    }
    if (left <= right)
      for (let r = bottom; r >= top; r--) result.push(matrix[r][left]);
      left++;
    }
  }
  return result; {
    throw new Error("NotImplementedError");
}

const tests = [
  { input: [[1,2,3],[4,5,6],[7,8,9]], expected: [1,2,3,6,9,8,7,4,5], label: "example 1" },
  { input: [[1,2,3,4],[5,6,7,8],[9,10,11,12]], expected: [1,2,3,4,8,12,11,10,9,5,6,7], label: "example 2" },
  { input: [[7]], expected: [7], label: "single element" },
  { input: [[1,2,3,4]], expected: [1,2,3,4], label: "single row" },
  { input: [[1],[2],[3],[4]], expected: [1,2,3,4], label: "single column" },
  { input: [[1,2],[3,4]], expected: [1,2,4,3], label: "2x2 matrix" },
  { input: [[1,2,3,4,5],[6,7,8,9,10]], expected: [1,2,3,4,5,10,9,8,7,6], label: "2 rows many columns" },
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
