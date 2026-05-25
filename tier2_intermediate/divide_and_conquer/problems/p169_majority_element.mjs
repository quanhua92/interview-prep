/**
 * P169: Majority Element (Easy)
 * https://leetcode.com/problems/majority-element/
 * Topics: Array, Hash Table, Divide and Conquer, Sorting, Counting
 *
 * Given an array nums of size n, return the majority element.
 * The majority element is the element that appears more than ⌊n / 2⌋ times. You may assume that the majority element always exists in the array.
 *
 * Example 1:
 *     Input: nums = [3,2,3]
 *     Output: 3
 *
 * Example 2:
 *     Input: nums = [2,2,1,1,1,2,2]
 *     Output: 2
 *
 * Constraints:
 *     - n == nums.length
 *     - 1 <= n <= 5 * 104
 *     - -109 <= nums[i] <= 109
 *
 * Template (python3):
 *     class Solution:
 *         def majorityElement(self, nums: List[int]) -> int:
 *
 * Hint: Use Boyer-Moore voting algorithm — maintain a candidate and count.
 */

function solve(nums) {
  throw new Error("NotImplementedError");
}

const tests = [
  { label: "example 1", input: [3, 2, 3], expected: 3 },
  { label: "example 2", input: [2, 2, 1, 1, 1, 2, 2], expected: 2 },
  { label: "single element", input: [1], expected: 1 },
  { label: "majority at end", input: [1, 2, 3, 2, 2], expected: 2 },
  { label: "all same", input: [5, 5, 5, 5, 5], expected: 5 },
  { label: "negative majority", input: [-1, -1, 2], expected: -1 },
  { label: "two elements", input: [3, 3], expected: 3 },
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
