/**
 * P564: Find the Closest Palindrome [PREMIUM] (Hard)
 * https://leetcode.com/problems/find-the-closest-palindrome/
 * Topics: Math, String
 * 
 * Given a string n representing an integer, return the closest integer (not including itself), which is a palindrome. If there is a tie, return the smaller one.
 * The closest is defined as the absolute difference minimized between two integers.
 * Example 1:
 *     Input: n = "123"
 *     Output: "121"
 * 
 * Example 2:
 *     Input: n = "1"
 *     Output: "0"
 *     Explanation: 0 and 2 are the closest palindromes but we return the smallest which is 0.
 * 
 * Constraints:
 *     - 1 <= n.length <= 18
 *     - n consists of only digits.
 *     - n does not have leading zeros.
 *     - n is representing an integer in the range [1, 1018 - 1].
 * 
 * Hint: Will brute force work for this problem? Think of something else.
 * Hint: Take some examples like 1234, 999,1000, etc and check their closest palindromes. How many different cases are possible?
 * Hint: Do we have to consider only left half or right half of the string or both?
 * Hint: Try to find the closest palindrome of these numbers- 12932, 99800, 12120. Did you observe something?
 * 
 * Template (python3):
 *     class Solution:
 *         def nearestPalindromic(self, n: str) -> str:
 */
function solve(n)
  const num = parseInt(n, 10);
  if (num <= 10) return String(num - 1);

  const candidates = new Set();
  const length = n.length;
  const prefix = parseInt(n.substring(0, Math.ceil(length / 2)), 10);

  for (const p of [prefix - 1, prefix, prefix + 1])
    const pStr = String(p);
    let candidate;
    if (length % 2 === 0)
      candidate = parseInt(pStr + pStr.split("").reverse().join(""), 10);
    } else
      candidate = parseInt(pStr + pStr.slice(0, -1).split("").reverse().join(""), 10);
    }
    candidates.add(candidate);
  }

  candidates.add(10 ** (length - 1) - 1);
  candidates.add(10 ** length + 1);
  candidates.delete(num);

  let best = null;
  let bestDiff = Infinity;
  for (const c of candidates)
    const diff = Math.abs(c - num);
    if (diff < bestDiff || (diff === bestDiff && c < best))
      bestDiff = diff;
      best = c;
    }
  }
  return String(best); {
    throw new Error("NotImplementedError");
}

const tests = [
  { label: "example 1", input: ["123"], expected: "121" },
  { label: "example 2", input: ["1"], expected: "0" },
  { label: "edge at 10", input: ["10"], expected: "9" },
  { label: "two same digits", input: ["99"], expected: "101" },
  { label: "power of 10", input: ["100"], expected: "99" },
  { label: "four digit", input: ["1283"], expected: "1331" },
];
let passed = 0;
for (let i = 0; i < tests.length; i++) {
  const t = tests[i];
  const got = solve(...t.input);
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
