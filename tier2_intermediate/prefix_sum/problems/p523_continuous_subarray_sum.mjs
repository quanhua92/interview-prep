/**
 * P523: Continuous Subarray Sum [PREMIUM] (Medium)
 * https://leetcode.com/problems/continuous-subarray-sum/
 * Topics: Array, Hash Table, Math, Prefix Sum
 *
 * Given an integer array nums and an integer k, return true if nums has a good subarray or false otherwise.
 * A good subarray is a subarray where:
 * Note that:
 * Example 1:
 *     Input: nums = [23,2,4,6,7], k = 6
 *     Output: true
 *     Explanation: [2, 4] is a continuous subarray of size 2 whose elements sum up to 6.
 *
 * Example 2:
 *     Input: nums = [23,2,6,4,7], k = 6
 *     Output: true
 *     Explanation: [23, 2, 6, 4, 7] is an continuous subarray of size 5 whose elements sum up to 42.
 *     42 is a multiple of 6 because 42 = 7 * 6 and 7 is an integer.
 *
 * Example 3:
 *     Input: nums = [23,2,6,4,7], k = 13
 *     Output: false
 *
 * Constraints:
 *     - 1 <= nums.length <= 105
 *     - 0 <= nums[i] <= 109
 *     - 0 <= sum(nums[i]) <= 231 - 1
 *     - 1 <= k <= 231 - 1
 *
 * Template (python3):
 *     class Solution:
 *         def checkSubarraySum(self, nums: List[int], k: int) -> bool:
 */

function solve(nums, k) {
  throw new Error("NotImplementedError");
}

const tests = [
  { label: "example 1", input: [[23, 2, 4, 6, 7], 6], expected: true },
  { label: "example 2", input: [[23, 2, 6, 4, 7], 6], expected: true },
  { label: "example 3", input: [[23, 2, 6, 4, 7], 13], expected: false },
  { label: "two zeros sum to 0", input: [[5, 0, 0], 3], expected: true },
  { label: "no valid subarray", input: [[1, 2], 4], expected: false },
  { label: "two zeros always valid", input: [[0, 0], 1], expected: true },
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
