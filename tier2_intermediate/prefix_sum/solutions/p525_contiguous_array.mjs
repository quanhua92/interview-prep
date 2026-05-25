/**
 * P525: Contiguous Array [PREMIUM] (Medium)
 * https://leetcode.com/problems/contiguous-array/
 * Topics: Array, Hash Table, Prefix Sum
 *
 * Given a binary array nums, return the maximum length of a contiguous subarray with an equal number of 0 and 1.
 * Example 1:
 *     Input: nums = [0,1]
 *     Output: 2
 *     Explanation: [0, 1] is the longest contiguous subarray with an equal number of 0 and 1.
 *
 * Example 2:
 *     Input: nums = [0,1,0]
 *     Output: 2
 *     Explanation: [0, 1] (or [1, 0]) is a longest contiguous subarray with equal number of 0 and 1.
 *
 * Example 3:
 *     Input: nums = [0,1,1,1,1,1,0,0,0]
 *     Output: 6
 *     Explanation: [1,1,1,0,0,0] is the longest contiguous subarray with equal number of 0 and 1.
 *
 * Constraints:
 *     - 1 <= nums.length <= 105
 *     - nums[i] is either 0 or 1.
 *
 * Template (python3):
 *     class Solution:
 *         def findMaxLength(self, nums: List[int]) -> int:
 */

function solve(nums) {
  const firstOccurrence = new Map();
  firstOccurrence.set(0, -1);
  let maxLen = 0;
  let count = 0;
  for (let i = 0; i < nums.length; i++) {
    count += nums[i] === 1 ? 1 : -1;
    if (firstOccurrence.has(count)) {
      maxLen = Math.max(maxLen, i - firstOccurrence.get(count));
    } else {
      firstOccurrence.set(count, i);
    }
  }
  return maxLen;
}

const tests = [
  { label: "example 1", input: [[0, 1]], expected: 2 },
  { label: "example 2", input: [[0, 1, 0]], expected: 2 },
  { label: "example 3", input: [[0, 1, 1, 1, 1, 1, 0, 0, 0]], expected: 6 },
  { label: "single element", input: [[1]], expected: 0 },
  { label: "balanced halves", input: [[0, 0, 0, 0, 1, 1, 1, 1]], expected: 8 },
  { label: "middle balanced", input: [[0, 0, 1, 0, 0, 0, 1, 1]], expected: 6 },
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
