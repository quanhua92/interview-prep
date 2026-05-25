/**
 * P479: Largest Palindrome Product [PREMIUM] (Hard)
 * https://leetcode.com/problems/largest-palindrome-product/
 * Topics: Math, Enumeration
 * 
 * Given an integer n, return the largest palindromic integer that can be represented as the product of two n-digits integers. Since the answer can be very large, return it modulo 1337.
 * Example 1:
 *     Input: n = 2
 *     Output: 987
 *     Explanation: 99 x 91 = 9009, 9009 % 1337 = 987
 * 
 * Example 2:
 *     Input: n = 1
 *     Output: 9
 * 
 * Constraints:
 *     - 1 <= n <= 8
 * 
 * Template (python3):
 *     class Solution:
 *         def largestPalindrome(self, n: int) -> int:
 */
function solve(n)
  if (n === 1) return 9;
  const upper = 10 ** n - 1;
  const lower = 10 ** (n - 1);
  const MOD = 1337n;
  for (let left = upper; left >= lower; left--)
    const s = String(left);
    const palindrome = BigInt(s + s.split("").reverse().join(""));
    for (let right = upper; right >= lower; right--)
      const rightBig = BigInt(right);
      if (rightBig * rightBig < palindrome) break;
      if (palindrome % rightBig === 0n)
        return Number(palindrome % MOD);
      }
    }
  }
  return 0; {
    throw new Error("NotImplementedError");
}

const tests = [
  { label: "example 1", input: 2, expected: 987 },
  { label: "example 2", input: 1, expected: 9 },
  { label: "3 digits", input: 3, expected: 123 },
  { label: "4 digits", input: 4, expected: 597 },
  { label: "8 digits (max n)", input: 8, expected: 475 },
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
