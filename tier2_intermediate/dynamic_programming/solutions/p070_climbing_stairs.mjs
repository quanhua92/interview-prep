/**
 * P70: Climbing Stairs (Easy)
 * https://leetcode.com/problems/climbing-stairs/
 * Topics: Math, Dynamic Programming, Memoization
 *
 * You are climbing a staircase. It takes n steps to reach the top.
 * Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?
 *
 * Example 1:
 *     Input: n = 2
 *     Output: 2
 *     Explanation: There are two ways to climb to the top.
 *     1. 1 step + 1 step
 *     2. 2 steps
 *
 * Example 2:
 *     Input: n = 3
 *     Output: 3
 *     Explanation: There are three ways to climb to the top.
 *     1. 1 step + 1 step + 1 step
 *     2. 1 step + 2 steps
 *     3. 2 steps + 1 step
 *
 * Constraints:
 *     - 1 <= n <= 45
 *
 * Hints:
 *     - To reach nth step, what could have been your previous steps? (Think about the step sizes)
 *
 * Template (python3):
 *     class Solution:
 *         def climbStairs(self, n: int) -> int:
 *
 * Hint: This is essentially Fibonacci -- each step depends on the two before it.
 */

function solve(n) {
  if (n <= 2) return n;
  let a = 1, b = 2;
  for (let i = 3; i <= n; i++) {
    const temp = b;
    b = a + b;
    a = temp;
  }
  return b;
}

const tests = [
  { label: "example 1", input: 2, expected: 2 },
  { label: "example 2", input: 3, expected: 3 },
  { label: "base case", input: 1, expected: 1 },
  { label: "larger", input: 10, expected: 89 },
  { label: "max constraint", input: 45, expected: 1836311903 },
  { label: "n=4", input: 4, expected: 5 },
  { label: "n=5", input: 5, expected: 8 },
  { label: "n=6", input: 6, expected: 13 },
  { label: "n=20", input: 20, expected: 10946 },
  { label: "near max constraint", input: 44, expected: 1134903170 },
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
