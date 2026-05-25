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
 * 
 * Template (python3):
 *     class Solution:
 *         def checkInclusion(self, s1: str, s2: str) -> bool:
 */
function solve(s1, s2)
  const n1 = s1.length, n2 = s2.length;
  if (n1 > n2) return false;

  const target = new Map();
  for (const ch of s1)
    target.set(ch, (target.get(ch) || 0) + 1);
  }

  const window = new Map();
  for (let i = 0; i < n1; i++)
    const ch = s2[i];
    window.set(ch, (window.get(ch) || 0) + 1);
  }

  if (mapsEqual(window, target)) return true;

  for (let i = n1; i < n2; i++)
    const leftCh = s2[i - n1];
    if (window.get(leftCh) === 1)
      window.delete(leftCh);
    } else
      window.set(leftCh, window.get(leftCh) - 1);
    }
    window.set(s2[i], (window.get(s2[i]) || 0) + 1);
    if (mapsEqual(window, target)) return true;
  }
  return false; {
    throw new Error("NotImplementedError");
}

function mapsEqual(a, b)
  if (a.size !== b.size) return false;
  for (const [k, v] of a)
    if (b.get(k) !== v) return false;
  }
  return true; {
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
