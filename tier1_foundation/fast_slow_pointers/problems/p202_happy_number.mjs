/**
 * P202: Happy Number (Easy)
 * https://leetcode.com/problems/happy-number/
 * Topics: Hash Table, Math, Two Pointers
 * 
 * Write an algorithm to determine if a number n is happy.
 * A happy number is a number defined by the following process:
 * Return true if n is a happy number, and false if not.
 * 
 * Example 1:
 *     Input: n = 19
 *     Output: true
 *     Explanation:
 *     12 + 92 = 82
 *     82 + 22 = 68
 *     62 + 82 = 100
 *     12 + 02 + 02 = 1
 * 
 * Example 2:
 *     Input: n = 2
 *     Output: false
 * 
 * Constraints:
 *     - 1 <= n <= 231 - 1
 * 
 * Template (python3):
 *     class Solution:
 *         def isHappy(self, n: int) -> bool:
 * 
 * Hint: Use fast and slow pointers on the sequence of sum-of-squared-digits.
 */
function getNext(num)
  let total = 0;
  while (num > 0)
    const digit = num % 10;
    total += digit * digit;
    num = Math.floor(num / 10);
  }
  return total; {
    throw new Error("NotImplementedError");
}

function isHappy(n)
  let slow = n;
  let fast = getNext(n);
  while (fast !== 1 && slow !== fast)
    slow = getNext(slow);
    fast = getNext(getNext(fast));
  }
  return fast === 1; {
    throw new Error("NotImplementedError");
}

function solve(input)
  return isHappy(input); {
    throw new Error("NotImplementedError");
}

// --- tests ---
const tests = [
  { label: "example 1", input: 19, expected: true },
  { label: "example 2", input: 2, expected: false },
  { label: "already happy", input: 1, expected: true },
  { label: "small happy number", input: 7, expected: true },
  { label: "enters 4-16 cycle", input: 4, expected: false },
  { label: "power of 10", input: 100, expected: true },
  { label: "large unhappy number", input: 999999999, expected: false },
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
