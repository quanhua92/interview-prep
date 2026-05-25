/**
 * P556: Next Greater Element III [PREMIUM] (Medium)
 * https://leetcode.com/problems/next-greater-element-iii/
 * Topics: Math, Two Pointers, String
 *
 * Given a positive integer n, find the smallest integer which has exactly the same digits existing in the integer n and is greater in value than n. If no such positive integer exists, return -1.
 * Note that the returned integer should fit in 32-bit integer, if there is a valid answer but it does not fit in 32-bit integer, return -1.
 * Example 1:
 *     Input: n = 12
 *     Output: 21
 *
 * Example 2:
 *     Input: n = 21
 *     Output: -1
 *
 * Constraints:
 *     - 1 <= n <= 231 - 1
 *
 * Template (python3):
 *     class Solution:
 *         def nextGreaterElement(self, n: int) -> int:
 */

function solve(n) {
  throw new Error("NotImplementedError");
}

const tests = [
  { label: "example 1", input: [12], expected: 21 },
  { label: "example 2", input: [21], expected: -1 },
  { label: "single digit", input: [1], expected: -1 },
  { label: "all same digits", input: [11], expected: -1 },
  { label: "classic example", input: [230241], expected: 230412 },
  { label: "max 32-bit int", input: [2147483647], expected: -1 },
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
