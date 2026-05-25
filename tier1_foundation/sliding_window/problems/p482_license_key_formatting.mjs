/**
 * P482: License Key Formatting [PREMIUM] (Easy)
 * https://leetcode.com/problems/license-key-formatting/
 * Topics: String
 * 
 * You are given a license key represented as a string s that consists of only alphanumeric characters and dashes. The string is separated into n + 1 groups by n dashes. You are also given an integer k.
 * We want to reformat the string s such that each group contains exactly k characters, except for the first group, which could be shorter than k but still must contain at least one character. Furthermore, there must be a dash inserted between two groups, and you should convert all lowercase letters to uppercase.
 * Return the reformatted license key.
 * Example 1:
 *     Input: s = "5F3Z-2e-9-w", k = 4
 *     Output: "5F3Z-2E9W"
 *     Explanation: The string s has been split into two parts, each part has 4 characters.
 *     Note that the two extra dashes are not needed and can be removed.
 * 
 * Example 2:
 *     Input: s = "2-5g-3-J", k = 2
 *     Output: "2-5G-3J"
 *     Explanation: The string s has been split into three parts, each part has 2 characters except the first part as it could be shorter as mentioned above.
 * 
 * Constraints:
 *     - 1 <= s.length <= 105
 *     - s consists of English letters, digits, and dashes '-'.
 *     - 1 <= k <= 104
 * 
 * Template (python3):
 *     class Solution:
 *         def licenseKeyFormatting(self, s: str, k: int) -> str:
 */
function solve(s, k)
  const cleaned = s.replace(/-/g, "").toUpperCase();
  const firstLen = cleaned.length % k;
  const groups = [];
  if (firstLen > 0)
    groups.push(cleaned.slice(0, firstLen));
  }
  for (let i = firstLen; i < cleaned.length; i += k)
    groups.push(cleaned.slice(i, i + k));
  }
  return groups.join("-"); {
    throw new Error("NotImplementedError");
}

const tests = [
  { label: "example 1", input: ["5F3Z-2e-9-w", 4], expected: "5F3Z-2E9W" },
  { label: "example 2", input: ["2-5g-3-J", 2], expected: "2-5G-3J" },
  { label: "single char no dash", input: ["a", 1], expected: "A" },
  { label: "only dashes", input: ["---", 3], expected: "" },
  { label: "even groups no short first", input: ["2-4A0r7-4k", 4], expected: "24A0-R74K" },
  { label: "k=1", input: ["aa-aa-aa-aa-aa-aa", 1], expected: "A-A-A-A-A-A-A-A-A-A-A-A" },
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
