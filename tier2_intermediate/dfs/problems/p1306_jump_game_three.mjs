/**
 * P1306: Jump Game III (Medium)
 * https://leetcode.com/problems/jump-game-iii/
 * Topics: Array, Depth-First Search, Breadth-First Search
 * 
 * Given an array of non-negative integers arr, you are initially positioned at start index of the array. When you are at index i, you can jump to i + arr[i] or i - arr[i], check if you can reach any index with value 0.
 * Notice that you can not jump outside of the array at any time.
 * 
 * Example 1:
 *     Input: arr = [4,2,3,0,3,1,2], start = 5
 *     Output: true
 *     Explanation:
 *     All possible ways to reach at index 3 with value 0 are:
 *     index 5 -> index 4 -> index 1 -> index 3
 *     index 5 -> index 6 -> index 4 -> index 1 -> index 3
 * 
 * Example 2:
 *     Input: arr = [4,2,3,0,3,1,2], start = 0
 *     Output: true
 *     Explanation:
 *     One possible way to reach at index 3 with value 0 is:
 *     index 0 -> index 4 -> index 1 -> index 3
 * 
 * Example 3:
 *     Input: arr = [3,0,2,1,2], start = 2
 *     Output: false
 *     Explanation: There is no way to reach at index 1 with value 0.
 * 
 * Constraints:
 *     - 1 <= arr.length <= 5 * 104
 *     - 0 <= arr[i] < arr.length
 *     - 0 <= start < arr.length
 * 
 * Hints:
 *     - Think of BFS to solve the problem.
 *     - When you reach a position with a value = 0 then return true.
 * 
 * Template (python3):
 *     class Solution:
 *         def canReach(self, arr: List[int], start: int) -> bool:
 * 
 * Hint: DFS with a visited set; explore start+arr[start] and start-arr[start], checking bounds and visited.
 */
function solve(arr, start)
  const n = arr.length;
  const visited = new Set();

  function dfs(i)
    if (i < 0 || i >= n || visited.has(i)) return false;
    if (arr[i] === 0) return true;
    visited.add(i);
    const jump = arr[i];
    return dfs(i + jump) || dfs(i - jump);
  }

  return dfs(start); {
    throw new Error("NotImplementedError");
}

const tests = [
  { label: "example 1", input: [[4, 2, 3, 0, 3, 1, 2], 5], expected: true },
  { label: "start at index 0", input: [[4, 2, 3, 0, 3, 1, 2], 0], expected: true },
  { label: "cannot reach zero", input: [[3, 0, 2, 1, 2], 2], expected: false },
  { label: "single element zero", input: [[0], 0], expected: true },
  { label: "single element non-zero", input: [[2], 0], expected: false },
  { label: "start next to zero", input: [[0, 1], 1], expected: true },
  { label: "linear path to zero", input: [[1, 1, 1, 1, 0], 0], expected: true },
  { label: "jump directly to zero", input: [[7, 0, 0, 0, 0, 0, 0, 0], 0], expected: true },
];
let passed = 0;
for (let i = 0; i < tests.length; i++) {
  const t = tests[i];
  const got = solve(t.input[0], t.input[1]);
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
