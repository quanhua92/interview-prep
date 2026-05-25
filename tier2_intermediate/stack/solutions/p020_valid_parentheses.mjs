/**
 * P20: Valid Parentheses (Easy)
 * https://leetcode.com/problems/valid-parentheses/
 * Topics: String, Stack
 *
 * Given a string s containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.
 * An input string is valid if:
 *
 * Example 1:
 *     Input: s = "()"
 *     Output: true
 *
 * Example 2:
 *     Input: s = "()[]{}"
 *     Output: true
 *
 * Example 3:
 *     Input: s = "(]"
 *     Output: false
 *
 * Example 4:
 *     Input: s = "([])"
 *     Output: true
 *
 * Example 5:
 *     Input: s = "([)]"
 *     Output: false
 *
 * Constraints:
 *     - 1 <= s.length <= 104
 *     - s consists of parentheses only '()[]{}'.
 *
 * Hints:
 *     - Use a stack of characters.
 *     - When you encounter an opening bracket, push it to the top of the stack.
 *     - When you encounter a closing bracket, check if the top of the stack was the opening for it. If yes, pop it from the stack. Otherwise, return false.
 *
 * Template (python3):
 *     class Solution:
 *         def isValid(self, s: str) -> bool:
 *
 * Hint: Use a stack to match opening and closing brackets.
 */

function solve(s) {
  const mapping = { ")": "(", "]": "[", "}": "{" };
  const stack = [];
  for (const ch of s) {
    if (ch in mapping) {
      if (stack.length === 0 || stack[stack.length - 1] !== mapping[ch]) {
        return false;
      }
      stack.pop();
    } else {
      stack.push(ch);
    }
  }
  return stack.length === 0;
}

const tests = [
  { label: "simple pair", input: ["()"], expected: true },
  { label: "mixed brackets", input: ["()[]{}"], expected: true },
  { label: "mismatched", input: ["(]"], expected: false },
  { label: "interleaved", input: ["([)]"], expected: false },
  { label: "nested", input: ["{[]}"], expected: true },
  { label: "single opening", input: ["("], expected: false },
  { label: "single closing", input: [")"], expected: false },
  { label: "only openings", input: ["(((("], expected: false },
  { label: "only closings", input: ["))))"], expected: false },
  { label: "deeply nested", input: ["((({{{[[[]]]}}})))"], expected: true },
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
