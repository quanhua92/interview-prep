/**
 * P3: Longest Substring Without Repeating Characters (Medium)
 * https://leetcode.com/problems/longest-substring-without-repeating-characters/
 * Topics: Hash Table, String, Sliding Window
 *
 * Given a string s, find the length of the longest substring without duplicate characters.
 *
 * Example 1:
 *     Input: s = "abcabcbb"
 *     Output: 3
 *     Explanation: The answer is "abc", with the length of 3.
 *
 * Example 2:
 *     Input: s = "bbbbb"
 *     Output: 1
 *     Explanation: The answer is "b", with the length of 1.
 *
 * Example 3:
 *     Input: s = "pwwkew"
 *     Output: 3
 *     Explanation: The answer is "wke", with the length of 3.
 *     Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.
 *
 * Constraints:
 *     - 0 <= s.length <= 5 * 104
 *     - s consists of English letters, digits, symbols and spaces.
 *
 * Hints:
 *     - Generate all possible substrings & check for each substring if it's valid and keep updating maxLen accordingly.
 *
 * Template (python3):
 *     class Solution:
 *         def lengthOfLongestSubstring(self, s: str) -> int:
 *
 * Hint: Use a hash map to track the last index of each character.
 */

function solve(s) {
  throw new Error("NotImplementedError");
}

const tests = [
  { label: "example 1", input: ["abcabcbb"], expected: 3 },
  { label: "example 2", input: ["bbbbb"], expected: 1 },
  { label: "example 3", input: ["pwwkew"], expected: 3 },
  { label: "empty string", input: [""], expected: 0 },
  { label: "single character", input: ["a"], expected: 1 },
  { label: "single space", input: [" "], expected: 1 },
  { label: "two unique chars", input: ["au"], expected: 2 },
  { label: "reset from duplicate after unique prefix", input: ["dvdf"], expected: 3 },
  { label: "char seen before current window", input: ["tmmzuxt"], expected: 5 },
];
let passed = 0;
for (let i = 0; i < tests.length; i++) {
  const t = tests[i];
  const got = solve(t.input[0]);
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
