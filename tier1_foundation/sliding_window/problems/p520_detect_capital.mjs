/**
 * P520: Detect Capital [PREMIUM] (Easy)
 * https://leetcode.com/problems/detect-capital/
 * Topics: String
 * 
 * We define the usage of capitals in a word to be right when one of the following cases holds:
 * Given a string word, return true if the usage of capitals in it is right.
 * Example 1:
 *     Input: word = "USA"
 *     Output: true
 * 
 * Example 2:
 *     Input: word = "FlaG"
 *     Output: false
 * 
 * Constraints:
 *     - 1 <= word.length <= 100
 *     - word consists of lowercase and uppercase English letters.
 * 
 * Template (python3):
 *     class Solution:
 *         def detectCapitalUse(self, word: str) -> bool:
 */
function solve(word)
  return word === word.toUpperCase() || word === word.toLowerCase() || word.slice(1) === word.slice(1).toLowerCase(); {
    throw new Error("NotImplementedError");
}

const tests = [
  { label: "example 1", input: ["USA"], expected: true },
  { label: "example 2", input: ["FlaG"], expected: false },
  { label: "single lowercase", input: ["a"], expected: true },
  { label: "single uppercase", input: ["Z"], expected: true },
  { label: "all lowercase", input: ["leetcode"], expected: true },
  { label: "title case", input: ["Google"], expected: true },
  { label: "lowercase then uppercase", input: ["mL"], expected: false },
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
