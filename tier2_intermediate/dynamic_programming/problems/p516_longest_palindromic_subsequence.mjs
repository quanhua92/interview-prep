/**
 * P516: Longest Palindromic Subsequence [PREMIUM] (Medium)
 * https://leetcode.com/problems/longest-palindromic-subsequence/
 * Topics: String, Dynamic Programming
 *
 * Given a string s, find the longest palindromic subsequence's length in s.
 * A subsequence is a sequence that can be derived from another sequence by deleting some or no elements without changing the order of the remaining elements.
 * Example 1:
 *     Input: s = "bbbab"
 *     Output: 4
 *     Explanation: One possible longest palindromic subsequence is "bbbb".
 *
 * Example 2:
 *     Input: s = "cbbd"
 *     Output: 2
 *     Explanation: One possible longest palindromic subsequence is "bb".
 *
 * Constraints:
 *     - 1 <= s.length <= 1000
 *     - s consists only of lowercase English letters.
 *
 * Template (python3):
 *     class Solution:
 *         def longestPalindromeSubseq(self, s: str) -> int:
 */

function solve(s) {
  throw new Error("NotImplementedError");
}

const tests = [
  { label: "example 1", input: "bbbab", expected: 4 },
  { label: "example 2", input: "cbbd", expected: 2 },
  { label: "single char", input: "a", expected: 1 },
  { label: "two same chars", input: "aa", expected: 2 },
  { label: "all distinct", input: "abcdef", expected: 1 },
  { label: "full palindrome", input: "aabbaa", expected: 6 },
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
