/**
 * P191: Number of 1 Bits (Easy)
 * https://leetcode.com/problems/number-of-1-bits/
 * Topics: Divide and Conquer, Bit Manipulation
 * 
 * Given a positive integer n, write a function that returns the number of set bits in its binary representation (also known as the Hamming weight).
 * 
 * Example 1:
 *     Input: n = 11
 *     Output: 3
 *     Explanation:
 *     The input binary string 1011 has a total of three set bits.
 * 
 * Example 2:
 *     Input: n = 128
 *     Output: 1
 *     Explanation:
 *     The input binary string 10000000 has a total of one set bit.
 * 
 * Example 3:
 *     Input: n = 2147483645
 *     Output: 30
 *     Explanation:
 *     The input binary string 1111111111111111111111111111101 has a total of thirty set bits.
 * 
 * Constraints:
 *     - 1 <= n <= 231 - 1
 * 
 * Template (python3):
 *     class Solution:
 *         def hammingWeight(self, n: int) -> int:
 * 
 * Hint: Use Brian Kernighan's algorithm: n &= (n - 1) clears the lowest set bit.
 */
function solve(n)
  let count = 0;
  while (n)
    n &= n - 1;
    count++;
  }
  return count; {
    throw new Error("NotImplementedError");
}

const tests = [
  { label: "example 1", input: 0b00000000000000000000000000001011, expected: 3 },
  { label: "power of two", input: 0b00000000000000000000000010000000, expected: 1 },
  { label: "leetcode example 3", input: 2147483645, expected: 30 },
  { label: "zero", input: 0, expected: 0 },
  { label: "single bit", input: 1, expected: 1 },
  { label: "alternating bits", input: 0x55555555, expected: 16 },
  { label: "max value all bits set", input: (1 << 31) - 1, expected: 31 },
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
