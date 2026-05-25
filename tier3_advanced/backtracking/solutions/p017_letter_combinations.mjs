/**
 * P17: Letter Combinations of a Phone Number (Medium)
 * https://leetcode.com/problems/letter-combinations-of-a-phone-number/
 * Topics: Hash Table, String, Backtracking
 *
 * Given a string containing digits from 2-9 inclusive, return all possible letter combinations that the number could represent. Return the answer in any order.
 * A mapping of digits to letters (just like on the telephone buttons) is given below. Note that 1 does not map to any letters.
 *
 * Example 1:
 *     Input: digits = "23"
 *     Output: ["ad","ae","af","bd","be","bf","cd","ce","cf"]
 *
 * Example 2:
 *     Input: digits = ""
 *     Output: []
 *
 * Example 3:
 *     Input: digits = "2"
 *     Output: ["a","b","c"]
 *
 * Constraints:
 *     - 0 <= digits.length <= 4
 *     - digits[i] is a digit in the range ['2', '9'].
 *
 * Template (python3):
 *     class Solution:
 *         def letterCombinations(self, digits: str) -> List[str]:
 *
 * Hint: Map each digit to its letters and use backtracking to build all combinations.
 */

function solve(digits) {
  if (!digits) return [];

  const phoneMap = {
    "2": "abc", "3": "def", "4": "ghi", "5": "jkl",
    "6": "mno", "7": "pqrs", "8": "tuv", "9": "wxyz",
  };
  const result = [];

  function backtrack(index, path) {
    if (index === digits.length) {
      result.push(path.join(""));
      return;
    }
    for (const letter of phoneMap[digits[index]]) {
      path.push(letter);
      backtrack(index + 1, path);
      path.pop();
    }
  }

  backtrack(0, []);
  return result.sort();
}

const tests = [
  { label: "example 1", input: ["23"], expected: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"] },
  { label: "empty input", input: [""], expected: [] },
  { label: "single digit", input: ["2"], expected: ["a", "b", "c"] },
  { label: "digit with 4 letters", input: ["7"], expected: ["p", "q", "r", "s"] },
  { label: "digit 9", input: ["9"], expected: ["w", "x", "y", "z"] },
  { label: "two 4-letter digits", input: ["79"], expected: ["pw", "px", "py", "pz", "qw", "qx", "qy", "qz", "rw", "rx", "ry", "rz", "sw", "sx", "sy", "sz"] },
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
