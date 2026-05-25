/**
 * P476: Number Complement [PREMIUM] (Easy)
 * https://leetcode.com/problems/number-complement/
 * Topics: Bit Manipulation
 *
 * The complement of an integer is the integer you get when you flip all the 0's to 1's and all the 1's to 0's in its binary representation.
 * Given an integer num, return its complement.
 * Example 2:
 * Note: This question is the same as 1009: https://leetcode.com/problems/complement-of-base-10-integer/
 * Example 1:
 *     Input: num = 5
 *     Output: 2
 *     Explanation: The binary representation of 5 is 101 (no leading zero bits), and its complement is 010. So you need to output 2.
 *
 * Example 2:
 *     Input: num = 1
 *     Output: 0
 *     Explanation: The binary representation of 1 is 1 (no leading zero bits), and its complement is 0. So you need to output 0.
 *
 * Constraints:
 *     - 1 <= num < 231
 *
 * Template (python3):
 *     class Solution:
 *         def findComplement(self, num: int) -> int:
 */

function solve(num) {
  const bitLength = num.toString(2).length;
  const mask = (1 << bitLength) - 1;
  return num ^ mask;
}

const tests = [
  { label: "example 1", input: 5, expected: 2 },
  { label: "example 2", input: 1, expected: 0 },
  { label: "power of two", input: 2, expected: 1 },
  { label: "1000 flips to 0111", input: 8, expected: 7 },
  { label: "all ones flips to zero", input: 15, expected: 0 },
  { label: "large power of two", input: 1 << 30, expected: (1 << 30) - 1 },
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
