/**
 * P467: Unique Substrings in Wraparound String [PREMIUM] (Medium)
 * https://leetcode.com/problems/unique-substrings-in-wraparound-string/
 * Topics: String, Dynamic Programming
 * 
 * We define the string base to be the infinite wraparound string of "abcdefghijklmnopqrstuvwxyz", so base will look like this:
 * Given a string s, return the number of unique non-empty substrings of s are present in base.
 * Example 1:
 *     Input: s = "a"
 *     Output: 1
 *     Explanation: Only the substring "a" of s is in base.
 * 
 * Example 2:
 *     Input: s = "cac"
 *     Output: 2
 *     Explanation: There are two substrings ("a", "c") of s in base.
 * 
 * Example 3:
 *     Input: s = "zab"
 *     Output: 6
 *     Explanation: There are six substrings ("z", "a", "b", "za", "ab", and "zab") of s in base.
 * 
 * Constraints:
 *     - 1 <= s.length <= 105
 *     - s consists of lowercase English letters.
 * 
 * Hint: One possible solution might be to consider allocating an array size of 26 for each character in the alphabet. (Credits to @r2ysxu)
 * 
 * Template (python3):
 *     class Solution:
 *         def findSubstringInWraproundString(self, s: str) -> int:
 */
function solve(s)
  const maxLen = new Array(26).fill(0);
  let curr = 0;
  for (let i = 0; i < s.length; i++)
    if (i > 0 && (s.charCodeAt(i) - s.charCodeAt(i - 1) === 1 || s.charCodeAt(i - 1) - s.charCodeAt(i) === 25))
      curr++;
    } else
      curr = 1;
    }
    const idx = s.charCodeAt(i) - "a".charCodeAt(0);
    maxLen[idx] = Math.max(maxLen[idx], curr);
  }
  return maxLen.reduce((a, b) => a + b, 0); {
    throw new Error("NotImplementedError");
}

const tests = [
  { label: "example 1", input: "a", expected: 1 },
  { label: "example 2", input: "cac", expected: 2 },
  { label: "example 3", input: "zab", expected: 6 },
  { label: "all same chars only a in wraparound", input: "aaaaa", expected: 1 },
  { label: "wraparound chain length 8", input: "zabcdefg", expected: 36 },
  { label: "full alphabet", input: "abcdefghijklmnopqrstuvwxyz", expected: 351 },
];
let passed = 0;
for (let i = 0; i < tests.length; i++) {
  const t = tests[i];
  const got = solve(t.input);
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
