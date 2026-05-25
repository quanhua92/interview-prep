/**
 * P704: Binary Search (Easy)
 * https://leetcode.com/problems/binary-search/
 * Topics: Array, Binary Search
 *
 * Given an array of integers nums which is sorted in ascending order, and an integer target, write a function to search target in nums. If target exists, then return its index. Otherwise, return -1.
 * You must write an algorithm with O(log n) runtime complexity.
 *
 * Example 1:
 *     Input: nums = [-1,0,3,5,9,12], target = 9
 *     Output: 4
 *     Explanation: 9 exists in nums and its index is 4
 *
 * Example 2:
 *     Input: nums = [-1,0,3,5,9,12], target = 2
 *     Output: -1
 *     Explanation: 2 does not exist in nums so return -1
 *
 * Constraints:
 *     - 1 <= nums.length <= 104
 *     - -104 < nums[i], target < 104
 *     - All the integers in nums are unique.
 *     - nums is sorted in ascending order.
 *
 * Template (python3):
 *     class Solution:
 *         def search(self, nums: List[int], target: int) -> int:
 *
 * Hint: Use the classic binary search pattern with left and right pointers.
 */

function solve(nums, target) {
  let left = 0;
  let right = nums.length - 1;
  while (left <= right) {
    const mid = left + Math.floor((right - left) / 2);
    if (nums[mid] === target) return mid;
    else if (nums[mid] < target) left = mid + 1;
    else right = mid - 1;
  }
  return -1;
}

const tests = [
  { label: "example 1", input: [[-1, 0, 3, 5, 9, 12], 9], expected: 4 },
  { label: "example 2", input: [[-1, 0, 3, 5, 9, 12], 2], expected: -1 },
  { label: "single element", input: [[5], 5], expected: 0 },
  { label: "below range", input: [[-1, 0, 3, 5, 9, 12], -2], expected: -1 },
  { label: "last element", input: [[-1, 0, 3, 5, 9, 12], 12], expected: 5 },
  { label: "two elements first", input: [[1, 2], 1], expected: 0 },
  { label: "two elements last", input: [[1, 2], 2], expected: 1 },
  { label: "large array middle target", input: [Array.from({ length: 10001 }, (_, i) => i - 5000), 0], expected: 5000 },
  { label: "target between elements", input: [[2, 4, 6, 8, 10], 5], expected: -1 },
  { label: "all negative found last", input: [[-3, -2, -1], -1], expected: 2 },
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
