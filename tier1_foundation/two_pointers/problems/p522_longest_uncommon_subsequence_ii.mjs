/**
 * P522: Longest Uncommon Subsequence II [PREMIUM] (Medium)
 * https://leetcode.com/problems/longest-uncommon-subsequence-ii/
 * Topics: Array, Hash Table, Two Pointers, String, Sorting
 * 
 * Given an array of strings strs, return the length of the longest uncommon subsequence between them. If the longest uncommon subsequence does not exist, return -1.
 * An uncommon subsequence between an array of strings is a string that is a subsequence of one string but not the others.
 * A subsequence of a string s is a string that can be obtained after deleting any number of characters from s.
 * Example 1:
 *     Input: strs = ["aba","cdc","eae"]
 *     Output: 3
 * 
 * Example 2:
 *     Input: strs = ["aaa","aaa","aa"]
 *     Output: -1
 * 
 * Constraints:
 *     - 2 <= strs.length <= 50
 *     - 1 <= strs[i].length <= 10
 *     - strs[i] consists of lowercase English letters.
 */

function solve(strs) {
  throw new Error("NotImplementedError");
}

// --- tests ---
const tests = [
  { label: "example 1", input: [["aba", "cdc", "eae"]], expected: 3 },
  { label: "example 2", input: [["aaa", "aaa", "aa"]], expected: -1 },
  { label: "all length 1 different", input: [["a", "b", "c", "d"]], expected: 1 },
  { label: "all identical", input: [["abc", "abc", "abc"]], expected: -1 },
  { label: "one string longer than rest", input: [["a", "a", "ab", "abc"]], expected: 3 },
  { label: "same length different chars", input: [["abc", "abd", "abe"]], expected: 3 },
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
