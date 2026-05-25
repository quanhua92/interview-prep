/**
 * P323: Number of Connected Components in an Undirected Graph (Medium)
 * https://leetcode.com/problems/number-of-connected-components-in-an-undirected-graph/
 * Topics: Depth-First Search, Breadth-First Search, Union Find, Graph
 *
 * You have a graph of n nodes. You are given an integer n and an array edges where edges[i] = [ai, bi] indicates that there is an edge between ai and bi in the graph.
 * Return the number of connected components in the graph.
 *
 * Example 1:
 *     Input: n = 5, edges = [[0,1],[1,2],[3,4]]
 *     Output: 2
 *
 * Example 2:
 *     Input: n = 5, edges = [[0,1],[1,2],[2,3],[3,4]]
 *     Output: 1
 *
 * Constraints:
 *     - 1 <= n <= 2000
 *     - 1 <= edges.length <= 5000
 *     - edges[i].length == 2
 *     - 0 <= ai <= bi < n
 *     - ai != bi
 *     - There are no repeated edges.
 *
 * Template (python3):
 *     class Solution:
 *         def countComponents(self, n: int, edges: List[List[int]]) -> int:
 *
 * Hint: Use a Union-Find data structure to merge connected nodes and count components.
 */

function solve(n, edges) {
  throw new Error("NotImplementedError");
}

const tests = [
  { input: [5, [[0, 1], [1, 2], [3, 4]]], expected: 2, label: "example" },
  { input: [5, [[0, 1], [1, 2], [2, 3], [3, 4]]], expected: 1, label: "fully connected" },
  { input: [3, []], expected: 3, label: "no edges" },
  { input: [1, []], expected: 1, label: "single node no edges" },
  { input: [4, [[0, 1], [2, 3]]], expected: 2, label: "two disjoint pairs" },
  { input: [6, [[0, 1], [1, 2], [2, 0], [3, 4], [4, 5], [5, 3]]], expected: 2, label: "two triangles" },
  { input: [7, [[0, 1], [1, 2], [3, 4], [5, 6]]], expected: 3, label: "three components with chain and pairs" },
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
