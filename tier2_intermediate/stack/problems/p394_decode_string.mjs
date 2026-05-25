/**
 * P394: Decode String (Medium)
 * https://leetcode.com/problems/decode-string/
 * Topics: String, Stack, Recursion
 *
 * Given an encoded string, return its decoded string.
 * The encoding rule is: k[encoded_string], where the encoded_string inside the square brackets is being repeated exactly k times. Note that k is guaranteed to be a positive integer.
 * You may assume that the input string is always valid; there are no extra white spaces, square brackets are well-formed, etc. Furthermore, you may assume that the original data does not contain any digits and that digits are only for those repeat numbers, k. For example, there will not be input like 3a or 2[4].
 * The test cases are generated so that the length of the output will never exceed 105.
 *
 * Example 1:
 *     Input: s = "3[a]2[bc]"
 *     Output: "aaabcbc"
 *
 * Example 2:
 *     Input: s = "3[a2[c]]"
 *     Output: "accaccacc"
 *
 * Example 3:
 *     Input: s = "2[abc]3[cd]ef"
 *     Output: "abcabccdcdcdef"
 *
 * Constraints:
 *     - 1 <= s.length <= 30
 *     - s consists of lowercase English letters, digits, and square brackets '[]'.
 *     - s is guaranteed to be a valid input.
 *     - All the integers in s are in the range [1, 300].
 *
 * Template (python3):
 *     class Solution:
 *         def decodeString(self, s: str) -> str:
 *
 * Hint: Use a stack to handle nested k[encoded] patterns.
 */

function solve(s) {
  throw new Error("NotImplementedError");
}

const tests = [
  { label: "example 1", input: ["3[a]2[bc]"], expected: "aaabcbc" },
  { label: "nested", input: ["3[a2[c]]"], expected: "accaccacc" },
  { label: "multiple segments", input: ["2[abc]3[cd]ef"], expected: "abcabccdcdcdef" },
  { label: "no encoding", input: ["abc"], expected: "abc" },
  { label: "multi-digit multiplier", input: ["10[a]"], expected: "aaaaaaaaaa" },
  { label: "deep nesting", input: ["2[2[2[a]]]"], expected: "aaaaaaaa" },
  { label: "encoded then plain", input: ["3[a]b"], expected: "aaab" },
  { label: "plain-enc-plain", input: ["a2[b]c"], expected: "abbc" },
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
