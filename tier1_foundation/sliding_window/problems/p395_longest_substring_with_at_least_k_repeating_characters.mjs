/**
 * P395: Longest Substring with At Least K Repeating Characters [PREMIUM] (Medium)
 * https://leetcode.com/problems/longest-substring-with-at-least-k-repeating-characters/
 * Topics: Hash Table, String, Divide and Conquer, Sliding Window
 * 
 * Given a string s and an integer k, return the length of the longest substring of s such that the frequency of each character in this substring is greater than or equal to k.
 * if no such substring exists, return 0.
 * Example 1:
 *     Input: s = "aaabb", k = 3
 *     Output: 3
 *     Explanation: The longest substring is "aaa", as 'a' is repeated 3 times.
 * 
 * Example 2:
 *     Input: s = "ababbc", k = 2
 *     Output: 5
 *     Explanation: The longest substring is "ababb", as 'a' is repeated 2 times and 'b' is repeated 3 times.
 * 
 * Constraints:
 *     - 1 <= s.length <= 104
 *     - s consists of only lowercase English letters.
 *     - 1 <= k <= 105
 * 
 * Template (python3):
 *     class Solution:
 *         def longestSubstring(self, s: str, k: int) -> int:
 */
function solve(s, k)
  let maxLen = 0;
  for (let t = 1; t <= 26; t++)
    const freq = new Map();
    let left = 0;
    let unique = 0;
    let atLeastK = 0;
    for (let right = 0; right < s.length; right++)
      const ch = s[right];
      freq.set(ch, (freq.get(ch) || 0) + 1);
      if (freq.get(ch) === 1) unique++;
      if (freq.get(ch) === k) atLeastK++;
      while (unique > t)
        const lc = s[left];
        if (freq.get(lc) === k) atLeastK--;
        freq.set(lc, freq.get(lc) - 1);
        if (freq.get(lc) === 0) unique--;
        left++;
      }
      if (unique === t && atLeastK === t)
        maxLen = Math.max(maxLen, right - left + 1);
      }
    }
  }
  return maxLen; {
    throw new Error("NotImplementedError");
}

const tests = [
  { label: "example 1", input: ["aaabb", 3], expected: 3 },
  { label: "example 2", input: ["ababbc", 2], expected: 5 },
  { label: "no valid substring", input: ["ababacb", 3], expected: 0 },
  { label: "single char k=1", input: ["a", 1], expected: 1 },
  { label: "single char k>1", input: ["a", 2], expected: 0 },
  { label: "multiple runs", input: ["bbaaacbd", 3], expected: 3 },
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
