/**
 * P278: First Bad Version (Easy)
 * https://leetcode.com/problems/first-bad-version/
 * Topics: Binary Search, Interactive
 * 
 * You are a product manager and currently leading a team to develop a new product. Unfortunately, the latest version of your product fails the quality check. Since each version is developed based on the previous version, all the versions after a bad version are also bad.
 * Suppose you have n versions [1, 2, ..., n] and you want to find out the first bad one, which causes all the following ones to be bad.
 * You are given an API bool isBadVersion(version) which returns whether version is bad. Implement a function to find the first bad version. You should minimize the number of calls to the API.
 * 
 * Example 1:
 *     Input: n = 5, bad = 4
 *     Output: 4
 *     Explanation:
 *     call isBadVersion(3) -> false
 *     call isBadVersion(5) -> true
 *     call isBadVersion(4) -> true
 *     Then 4 is the first bad version.
 * 
 * Example 2:
 *     Input: n = 1, bad = 1
 *     Output: 1
 * 
 * Constraints:
 *     - 1 <= bad <= n <= 231 - 1
 * 
 * Template (python3):
 *     # The isBadVersion API is already defined for you.
 *     # def isBadVersion(version: int) -> bool:
 * 
 *     class Solution:
 *         def firstBadVersion(self, n: int) -> int:
 * 
 * Hint: Binary search for the leftmost version where is_bad is True.
 */
function solve(n, bad)
  const isBad = (v) => v >= bad;

  let left = 1;
  let right = n;
  while (left < right)
    const mid = Math.floor((left + right) / 2);
    if (isBad(mid))
      right = mid;
    } else
      left = mid + 1;
    }
  }
  return left; {
    throw new Error("NotImplementedError");
}

const tests = [
  { label: "example 1", input: [5, 4], expected: 4 },
  { label: "single version, bad", input: [1, 1], expected: 1 },
  { label: "last version is bad", input: [3, 3], expected: 3 },
  { label: "middle version is bad", input: [10, 7], expected: 7 },
  { label: "first version is bad", input: [2, 1], expected: 1 },
  { label: "large n, last is bad", input: [100, 100], expected: 100 },
  { label: "large n, first is bad", input: [100000, 1], expected: 1 },
  { label: "small n last bad", input: [2, 2], expected: 2 },
  { label: "large n near end", input: [1000000, 999999], expected: 999999 },
  { label: "max int overflow safe", input: [2147483647, 1], expected: 1 },
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
