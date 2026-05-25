/**
 * P338: Counting Bits (Easy)
 * https://leetcode.com/problems/counting-bits/
 * Topics: Dynamic Programming, Bit Manipulation
 *
 * Given an integer n, return an array ans of length n + 1 such that for each i (0 <= i <= n), ans[i] is the number of 1's in the binary representation of i.
 *
 * Example 1:
 *     Input: n = 2
 *     Output: [0,1,1]
 *     Explanation:
 *     0 --> 0
 *     1 --> 1
 *     2 --> 10
 *
 * Example 2:
 *     Input: n = 5
 *     Output: [0,1,1,2,1,2]
 *     Explanation:
 *     0 --> 0
 *     1 --> 1
 *     2 --> 10
 *     3 --> 11
 *     4 --> 100
 *     5 --> 101
 *
 * Constraints:
 *     - 0 <= n <= 105
 *
 * Hints:
 *     - You should make use of what you have produced already.
 *     - Divide the numbers in ranges like [2-3], [4-7], [8-15] and so on. And try to generate new range from previous.
 *     - Or does the odd/even status of the number help you in calculating the number of 1s?
 *
 * Template (python3):
 *     class Solution:
 *         def countBits(self, n: int) -> List[int]:
 *
 * Hint: DP approach: ans[i] = ans[i >> 1] + (i & 1).
 */

function solve(n) {
  const ans = new Array(n + 1).fill(0);
  for (let i = 1; i <= n; i++) {
    ans[i] = ans[i >> 1] + (i & 1);
  }
  return ans;
}

const tests = [
  { label: "example 1", input: 2, expected: [0, 1, 1] },
  { label: "example 2", input: 5, expected: [0, 1, 1, 2, 1, 2] },
  { label: "zero", input: 0, expected: [0] },
  { label: "one", input: 1, expected: [0, 1] },
  { label: "power-of-2 minus 1", input: 7, expected: [0, 1, 1, 2, 1, 2, 2, 3] },
  { label: "four bits all", input: 15, expected: [0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4] },
  { label: "power of 2", input: 16, expected: [0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 1] },
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
