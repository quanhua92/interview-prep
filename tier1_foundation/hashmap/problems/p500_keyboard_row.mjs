/**
 * P500: Keyboard Row [PREMIUM] (Easy)
 * https://leetcode.com/problems/keyboard-row/
 * Topics: Array, Hash Table, String
 * 
 * Given an array of strings words, return the words that can be typed using letters of the alphabet on only one row of American keyboard like the image below.
 * Note that the strings are case-insensitive, both lowercased and uppercased of the same letter are treated as if they are at the same row.
 * In the American keyboard:
 * Example 1:
 *     Input: words = ["Hello","Alaska","Dad","Peace"]
 *     Output: ["Alaska","Dad"]
 *     Explanation:
 *     Both "a" and "A" are in the 2nd row of the American keyboard due to case insensitivity.
 * 
 * Example 2:
 *     Input: words = ["omk"]
 *     Output: []
 * 
 * Example 3:
 *     Input: words = ["adsdf","sfd"]
 *     Output: ["adsdf","sfd"]
 * 
 * Constraints:
 *     - 1 <= words.length <= 20
 *     - 1 <= words[i].length <= 100
 *     - words[i] consists of English letters (both lowercase and uppercase).
 * 
 * Template (python3):
 *     class Solution:
 *         def findWords(self, words: List[str]) -> List[str]:
 */
function solve(words)
  const rows = [
    new Set("qwertyuiop".split("")),
    new Set("asdfghjkl".split("")),
    new Set("zxcvbnm".split("")),
  ];
  const result = [];
  for (const w of words)
    const lower = new Set(w.toLowerCase().split(""));
    if (rows.some(row => [...lower].every(ch => row.has(ch))))
      result.push(w);
    }
  }
  return result; {
    throw new Error("NotImplementedError");
}

const tests = [
  { label: "example 1", input: [["Hello", "Alaska", "Dad", "Peace"]], expected: ["Alaska", "Dad"] },
  { label: "example 2", input: [["omk"]], expected: [] },
  { label: "example 3", input: [["adsdf", "sfd"]], expected: ["adsdf", "sfd"] },
  { label: "single letter words", input: [["a", "b", "c"]], expected: ["a", "b", "c"] },
  { label: "mixed row words", input: [["qz", "asdf", "qzxc"]], expected: ["asdf"] },
  { label: "entire top row word", input: [["typewriter"]], expected: ["typewriter"] },
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
