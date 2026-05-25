/**
 * P424: Longest Repeating Character Replacement (Medium)
 * https://leetcode.com/problems/longest-repeating-character-replacement/
 * Topics: Hash Table, String, Sliding Window
 *
 * You are given a string s and an integer k. You can choose any character of the string and change it to any other uppercase English character. You can perform this operation at most k times.
 * Return the length of the longest substring containing the same letter you can get after performing the above operations.
 *
 * Example 1:
 *     Input: s = "ABAB", k = 2
 *     Output: 4
 *     Explanation: Replace the two 'A's with two 'B's or vice versa.
 *
 * Example 2:
 *     Input: s = "AABABBA", k = 1
 *     Output: 4
 *     Explanation: Replace the one 'A' in the middle with 'B' and form "AABBBBA".
 *     The substring "BBBB" has the longest repeating letters, which is 4.
 *     There may exists other ways to achieve this answer too.
 *
 * Constraints:
 *     - 1 <= s.length <= 105
 *     - s consists of only uppercase English letters.
 *     - 0 <= k <= s.length
 *
 * Template (python3):
 *     class Solution:
 *         def characterReplacement(self, s: str, k: int) -> int:
 *
 * Hint: Freq map + max_freq tracker, window valid when len - max_freq <= k. Left only moves right.
 */

function solve(s, k) {
  const freq = new Map();
  let maxFreq = 0;
  let left = 0;
  let maxLen = 0;
  for (let right = 0; right < s.length; right++) {
    const ch = s[right];
    freq.set(ch, (freq.get(ch) || 0) + 1);
    maxFreq = Math.max(maxFreq, freq.get(ch));
    while ((right - left + 1) - maxFreq > k) {
      freq.set(s[left], freq.get(s[left]) - 1);
      left++;
    }
    maxLen = Math.max(maxLen, right - left + 1);
  }
  return maxLen;
}

const tests = [
  { label: "example 1", input: ["ABAB", 2], expected: 4 },
  { label: "example 2", input: ["AABABBA", 1], expected: 4 },
  { label: "no changes needed", input: ["AAAA", 0], expected: 4 },
  { label: "all unique", input: ["ABCDE", 1], expected: 2 },
  { label: "single char, k=0", input: ["A", 0], expected: 1 },
  { label: "single char, k > len", input: ["A", 5], expected: 1 },
  { label: "no changes, partial run", input: ["AAAB", 0], expected: 3 },
  { label: "change middle B to A", input: ["ABAA", 2], expected: 4 },
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
