/**
 * P524: Longest Word in Dictionary through Deleting [PREMIUM] (Medium)
 * https://leetcode.com/problems/longest-word-in-dictionary-through-deleting/
 * Topics: Array, Two Pointers, String, Sorting
 * 
 * Given a string s and a string array dictionary, return the longest string in the dictionary that can be formed by deleting some of the given string characters. If there is more than one possible result, return the longest word with the smallest lexicographical order. If there is no possible result, return the empty string.
 * Example 1:
 *     Input: s = "abpcplea", dictionary = ["ale","apple","monkey","plea"]
 *     Output: "apple"
 * 
 * Example 2:
 *     Input: s = "abpcplea", dictionary = ["a","b","c"]
 *     Output: "a"
 * 
 * Constraints:
 *     - 1 <= s.length <= 1000
 *     - 1 <= dictionary.length <= 1000
 *     - 1 <= dictionary[i].length <= 1000
 *     - s and dictionary[i] consist of lowercase English letters.
 */

function solve(s, dictionary) {
  throw new Error("NotImplementedError");
}

// --- tests ---
const tests = [
  { label: "example 1", input: ["abpcplea", ["ale", "apple", "monkey", "plea"]], expected: "apple" },
  { label: "example 2", input: ["abpcplea", ["a", "b", "c"]], expected: "a" },
  { label: "empty dictionary", input: ["abpcplea", []], expected: "" },
  { label: "no match", input: ["abc", ["xyz", "def"]], expected: "" },
  { label: "same length lexicographical tie", input: ["abpcplea", ["apple", "ale", "abpple"]], expected: "abpple" },
  { label: "longer dict words than s", input: ["a", ["a", "aa", "aaa"]], expected: "a" },
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
