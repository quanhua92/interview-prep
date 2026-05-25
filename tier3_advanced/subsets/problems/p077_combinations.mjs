/**
 * P77: Combinations (Medium)
 * https://leetcode.com/problems/combinations/
 * Topics: Backtracking
 *
 * Given two integers n and k, return all possible combinations of k numbers chosen from the range [1, n].
 * You may return the answer in any order.
 *
 * Example 1:
 *     Input: n = 4, k = 2
 *     Output: [[1,2],[1,3],[1,4],[2,3],[2,4],[3,4]]
 *     Explanation: There are 4 choose 2 = 6 total combinations.
 *     Note that combinations are unordered, i.e., [1,2] and [2,1] are considered to be the same combination.
 *
 * Example 2:
 *     Input: n = 1, k = 1
 *     Output: [[1]]
 *     Explanation: There is 1 choose 1 = 1 total combination.
 *
 * Constraints:
 *     - 1 <= n <= 20
 *     - 1 <= k <= n
 *
 * Template (python3):
 *     class Solution:
 *         def combine(self, n: int, k: int) -> List[List[int]]:
 *
 * Hint: Use backtracking with a start index to generate all k-length combinations from 1..n.
 */

function solve(n, k) {
  throw new Error("NotImplementedError");
}

const tests = [
  { label: "example 1", input: [4, 2], expected: [[1, 2], [1, 3], [1, 4], [2, 3], [2, 4], [3, 4]] },
  { label: "example 2", input: [1, 1], expected: [[1]] },
  { label: "example 3", input: [3, 1], expected: [[1], [2], [3]] },
  { label: "k equals n", input: [5, 5], expected: [[1, 2, 3, 4, 5]] },
  {
    label: "mid range", input: [5, 3],
    expected: [
      [1, 2, 3], [1, 2, 4], [1, 2, 5], [1, 3, 4], [1, 3, 5], [1, 4, 5],
      [2, 3, 4], [2, 3, 5], [2, 4, 5], [3, 4, 5],
    ],
  },
  { label: "smallest k equals n", input: [2, 2], expected: [[1, 2]] },
  { label: "k equals 1 larger n", input: [6, 1], expected: [[1], [2], [3], [4], [5], [6]] },
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
