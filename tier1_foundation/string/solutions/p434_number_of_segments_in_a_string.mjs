/**
 * P434: Number of Segments in a String [PREMIUM] (Easy)
 * https://leetcode.com/problems/number-of-segments-in-a-string/
 * Topics: String
 *
 * Given a string s, return the number of segments in the string.
 * A segment is defined to be a contiguous sequence of non-space characters.
 * Example 1:
 *     Input: s = "Hello, my name is John"
 *     Output: 5
 *     Explanation: The five segments are ["Hello,", "my", "name", "is", "John"]
 *
 * Example 2:
 *     Input: s = "Hello"
 *     Output: 1
 *
 * Constraints:
 *     - 0 <= s.length <= 300
 *     - s consists of lowercase and uppercase English letters, digits, or one of the following characters "!@#$%^&*()_+-=',.:".
 *     - The only space character in s is ' '.
 *
 * Template (python3):
 *     class Solution:
 *         def countSegments(self, s: str) -> int:
 */

function solve(s) {
  let count = 0;
  let inSegment = false;
  for (const ch of s) {
    if (ch !== " " && !inSegment) {
      count++;
      inSegment = true;
    } else if (ch === " ") {
      inSegment = false;
    }
  }
  return count;
}

const tests = [
  { label: "example 1", input: ["Hello, my name is John"], expected: 5 },
  { label: "example 2", input: ["Hello"], expected: 1 },
  { label: "empty string", input: [""], expected: 0 },
  { label: "only spaces", input: ["   "], expected: 0 },
  { label: "leading/trailing/multiple spaces", input: ["    foo    bar   "], expected: 2 },
  { label: "single char segments", input: ["a b c d e"], expected: 5 },
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
