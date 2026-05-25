/**
 * P567: Permutation in String [PREMIUM] (Medium)
 * https://leetcode.com/problems/permutation-in-string/
 * Topics: Hash Table, Two Pointers, String, Sliding Window
 * 
 * Given two strings s1 and s2, return true if s2 contains a permutation of s1, or false otherwise.
 * In other words, return true if one of s1's permutations is the substring of s2.
 * Example 1:
 *     Input: s1 = "ab", s2 = "eidbaooo"
 *     Output: true
 *     Explanation: s2 contains one permutation of s1 ("ba").
 * 
 * Example 2:
 *     Input: s1 = "ab", s2 = "eidboaoo"
 *     Output: false
 * 
 * Constraints:
 *     - 1 <= s1.length, s2.length <= 104
 *     - s1 and s2 consist of lowercase English letters.
 * 
 * Hint: Obviously, brute force will result in TLE. Think of something else.
 * Hint: How will you check whether one string is a permutation of another string?
 * Hint: One way is to sort the string and then compare. But, Is there a better way?
 * Hint: If one string is a permutation of another string then they must have one common metric. What is that?
 * Hint: Both strings must have same character frequencies, if  one is permutation of another. Which data structure should be used to store frequencies?
 * Hint: What about hash table?  An array of size 26?
 */

function solve(s1, s2) {
  throw new Error("NotImplementedError");
}

// --- tests ---
const tests = [
  { label: "example 1", input: ["ab", "eidbaooo"], expected: true },
  { label: "example 2", input: ["ab", "eidboaoo"], expected: false },
  { label: "single char match", input: ["a", "a"], expected: true },
  { label: "permutation at end", input: ["adc", "dcda"], expected: true },
  { label: "no match large string", input: ["abc", "ccccbbbbaaaa"], expected: false },
  { label: "s1 longer than s2", input: ["ab", "a"], expected: false },
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
