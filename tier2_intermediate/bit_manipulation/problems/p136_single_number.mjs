/**
 * P136: Single Number (Easy)
 * https://leetcode.com/problems/single-number/
 * Topics: Array, Bit Manipulation
 * 
 * Given a non-empty array of integers nums, every element appears twice except for one. Find that single one.
 * You must implement a solution with a linear runtime complexity and use only constant extra space.
 * 
 * Example 1:
 *     Input: nums = [2,2,1]
 *     Output: 1
 * 
 * Example 2:
 *     Input: nums = [4,1,2,1,2]
 *     Output: 4
 * 
 * Example 3:
 *     Input: nums = [1]
 *     Output: 1
 * 
 * Constraints:
 *     - 1 <= nums.length <= 3 * 104
 *     - -3 * 104 <= nums[i] <= 3 * 104
 *     - Each element in the array appears twice except for one element which appears only once.
 * 
 * Hints:
 *     - Think about the XOR (^) operator's property.
 * 
 * Template (python3):
 *     class Solution:
 *         def singleNumber(self, nums: List[int]) -> int:
 * 
 * Hint: XOR all numbers — pairs cancel out, leaving the single number.
 */
function solve(nums)
  let result = 0;
  for (const num of nums)
    result ^= num;
  }
  return result; {
    throw new Error("NotImplementedError");
}

const tests = [
  { label: "example 1", input: [2, 2, 1], expected: 1 },
  { label: "example 2", input: [4, 1, 2, 1, 2], expected: 4 },
  { label: "single element", input: [1], expected: 1 },
  { label: "negative numbers", input: [-1, -1, -2], expected: -2 },
  { label: "zero pairs", input: [0, 0, 1], expected: 1 },
  { label: "single negative", input: [-1], expected: -1 },
  { label: "many pairs", input: [7, 7, 7, 7, 99, 3, 3, 4, 4], expected: 99 },
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
