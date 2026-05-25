/**
 * P684: Redundant Connection (Medium)
 * https://leetcode.com/problems/redundant-connection/
 * Topics: Depth-First Search, Breadth-First Search, Union Find, Graph
 *
 * In this problem, a tree is an undirected graph that is connected and has no cycles.
 * You are given a graph that started as a tree with n nodes labeled from 1 to n, with one additional edge added. The added edge has two different vertices chosen from 1 to n, and was not an edge that already existed. The graph is represented as an array edges of length n where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the graph.
 * Return an edge that can be removed so that the resulting graph is a tree of n nodes. If there are multiple answers, return the answer that occurs last in the input.
 *
 * Example 1:
 *     Input: edges = [[1,2],[1,3],[2,3]]
 *     Output: [2,3]
 *
 * Example 2:
 *     Input: edges = [[1,2],[2,3],[3,4],[1,4],[1,5]]
 *     Output: [1,4]
 *
 * Constraints:
 *     - n == edges.length
 *     - 3 <= n <= 1000
 *     - edges[i].length == 2
 *     - 1 <= ai < bi <= edges.length
 *     - ai != bi
 *     - There are no repeated edges.
 *     - The given graph is connected.
 *
 * Template (python3):
 *     class Solution:
 *         def findRedundantConnection(self, edges: List[List[int]]) -> List[int]:
 *
 * Hint: Use Union-Find to detect the first edge that connects two already-connected nodes.
 */

function solve(edges) {
  throw new Error("NotImplementedError");
}

const tests = [
  { input: [[[1, 2], [1, 3], [2, 3]]], expected: [2, 3], label: "example 1" },
  { input: [[[1, 2], [2, 3], [3, 4], [1, 4], [1, 5]]], expected: [1, 4], label: "example 2" },
  { input: [[[1, 2], [2, 3], [3, 1]]], expected: [3, 1], label: "triangle of 3" },
  { input: [[[1, 2], [1, 3], [1, 4], [1, 5], [2, 3]]], expected: [2, 3], label: "redundant at end star" },
  { input: [[[1, 2], [1, 3], [1, 4], [2, 3]]], expected: [2, 3], label: "last edge closes triangle" },
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
