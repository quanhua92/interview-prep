/**
 * P438: Find All Anagrams in a String (Medium)
 * https://leetcode.com/problems/find-all-anagrams-in-a-string/
 * Topics: Hash Table, String, Sliding Window
 * 
 * Given two strings s and p, return an array of all the start indices of p's anagrams in s. You may return the answer in any order.
 * 
 * Example 1:
 *     Input: s = "cbaebabacd", p = "abc"
 *     Output: [0,6]
 *     Explanation:
 *     The substring with start index = 0 is "cba", which is an anagram of "abc".
 *     The substring with start index = 6 is "bac", which is an anagram of "abc".
 * 
 * Example 2:
 *     Input: s = "abab", p = "ab"
 *     Output: [0,1,2]
 *     Explanation:
 *     The substring with start index = 0 is "ab", which is an anagram of "ab".
 *     The substring with start index = 1 is "ba", which is an anagram of "ab".
 *     The substring with start index = 2 is "ab", which is an anagram of "ab".
 * 
 * Constraints:
 *     - 1 <= s.length, p.length <= 3 * 104
 *     - s and p consist of lowercase English letters.
 * 
 * Template (python3):
 *     class Solution:
 *         def findAnagrams(self, s: str, p: str) -> List[int]:
 * 
 * Hint: Use a sliding window with frequency counters to compare against pattern.
 */
function solve(s, p)
  if (p.length > s.length) return [];

  const buildCount = (str) =>
    const map = new Map();
    for (const ch of str)
      map.set(ch, (map.get(ch) || 0) + 1);
    }
    return map;
  };

  const countsEqual = (a, b) =>
    if (a.size !== b.size) return false;
    for (const [key, val] of a)
      if (b.get(key) !== val) return false;
    }
    return true;
  };

  const pCount = buildCount(p);
  const sCount = buildCount(s.slice(0, p.length));
  const result = [];

  if (countsEqual(sCount, pCount))
    result.push(0);
  }

  for (let i = p.length; i < s.length; i++)
    sCount.set(s[i], (sCount.get(s[i]) || 0) + 1);
    const leftCh = s[i - p.length];
    sCount.set(leftCh, sCount.get(leftCh) - 1);
    if (sCount.get(leftCh) === 0)
      sCount.delete(leftCh);
    }
    if (countsEqual(sCount, pCount))
      result.push(i - p.length + 1);
    }
  }

  return result; {
    throw new Error("NotImplementedError");
}

const tests = [
  { label: "example 1", input: ["cbaebabacd", "abc"], expected: [0, 6] },
  { label: "example 2", input: ["abab", "ab"], expected: [0, 1, 2] },
  { label: "no anagrams", input: ["af", "bf"], expected: [] },
  { label: "exact match single", input: ["abc", "abc"], expected: [0] },
  { label: "all same chars", input: ["aaaaaaaaaa", "aa"], expected: [0, 1, 2, 3, 4, 5, 6, 7, 8] },
  { label: "overlapping anagrams", input: ["abacbabc", "abc"], expected: [1, 2, 3, 5] },
  { label: "pattern longer than string", input: ["a", "aa"], expected: [] },
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
