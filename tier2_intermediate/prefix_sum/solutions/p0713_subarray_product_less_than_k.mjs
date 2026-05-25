/**
 * P713: Subarray Product Less Than K (Medium)
 * https://leetcode.com/problems/subarray-product-less-than-k/
 * Topics: Array, Binary Search, Sliding Window, Prefix Sum
 *
 * Given an array of integers nums and an integer k, return the number of contiguous subarrays where the product of all the elements in the subarray is strictly less than k.
 *
 * Example 1:
 *     Input: nums = [10,5,2,6], k = 100
 *     Output: 8
 *     Explanation: The 8 subarrays that have product less than 100 are:
 *     [10], [5], [2], [6], [10, 5], [5, 2], [2, 6], [5, 2, 6]
 *     Note that [10, 5, 2] is not included as the product of 100 is not strictly less than k.
 *
 * Example 2:
 *     Input: nums = [1,2,3], k = 0
 *     Output: 0
 *
 * Constraints:
 *     - 1 <= nums.length <= 3 * 104
 *     - 1 <= nums[i] <= 1000
 *     - 0 <= k <= 106
 *
 * Hints:
 *     - For each j, let opt(j) be the smallest i so that nums[i] * nums[i+1] * ... * nums[j] is less than k.  opt is an increasing function.
 *
 * Template (python3):
 *     class Solution:
 *         def numSubarrayProductLessThanK(self, nums: List[int], k: int) -> int:
 *
 * Hint: Use a sliding window where you shrink from the left when product >= k.
 */

function solve(nums, k) {
  if (k <= 1) return 0;

  let count = 0;
  let product = 1;
  let left = 0;

  for (let right = 0; right < nums.length; right++) {
    product *= nums[right];
    while (product >= k) {
      product /= nums[left];
      left++;
    }
    count += right - left + 1;
  }

  return count;
}

const tests = [
  { label: "example 1", input: [[10, 5, 2, 6], 100], expected: 8 },
  { label: "zero k", input: [[1, 2, 3], 0], expected: 0 },
  { label: "all ones", input: [[1, 1, 1], 2], expected: 6 },
  { label: "k equals 0", input: [[1, 2, 3], 0], expected: 0 },
  { label: "k equals 1", input: [[1, 2, 3], 1], expected: 0 },
  { label: "all large numbers", input: [[1000, 1000, 1000], 1000000], expected: 3 },
  { label: "small k many singles", input: [[10, 5, 2, 6], 8], expected: 3 },
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
