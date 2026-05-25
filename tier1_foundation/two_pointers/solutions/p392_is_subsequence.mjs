/**
 * P392: Is Subsequence [PREMIUM] (Easy)
 * https://leetcode.com/problems/is-subsequence/
 * Topics: Two Pointers, String, Dynamic Programming
 * 
 * Given two strings s and t, return true if s is a subsequence of t, or false otherwise.
 * A subsequence of a string is a new string that is formed from the original string by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters. (i.e., "ace" is a subsequence of "abcde" while "aec" is not).
 * Example 1:
 *     Input: s = "abc", t = "ahbgdc"
 *     Output: true
 * 
 * Example 2:
 *     Input: s = "axc", t = "ahbgdc"
 *     Output: false
 * 
 * Constraints:
 *     - 0 <= s.length <= 100
 *     - 0 <= t.length <= 104
 *     - s and t consist only of lowercase English letters.
 */

function solve(s, t) {
  let i = 0;
  for (const ch of t) {
    if (i < s.length && s[i] === ch) {
      i++;
    }
  }
  return i === s.length;
}

// --- tests ---
const tests = [
  { label: "example 1", input: ["abc", "ahbgdc"], expected: true },
  { label: "example 2", input: ["axc", "ahbgdc"], expected: false },
  { label: "empty s is subsequence", input: ["", "ahbgdc"], expected: true },
  { label: "s equals t", input: ["abc", "abc"], expected: true },
  { label: "s longer than t", input: ["abcd", "abc"], expected: false },
  { label: "single char not found", input: ["z", "aaaaa"], expected: false },
];
let passed = 0;
for (let i = 0; i < tests.length; i++) {
  const t = tests[i];
  const got = solve(t.input[0], t.input[1]);
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
