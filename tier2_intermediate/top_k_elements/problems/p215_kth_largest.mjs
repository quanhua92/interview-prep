/**
 * P215: Kth Largest Element in an Array (Medium)
 * https://leetcode.com/problems/kth-largest-element-in-an-array/
 * Topics: Array, Divide and Conquer, Sorting, Heap (Priority Queue), Quickselect
 *
 * Given an integer array nums and an integer k, return the kth largest element in the array.
 * Note that it is the kth largest element in the sorted order, not the kth distinct element.
 * Can you solve it without sorting?
 *
 * Example 1:
 *     Input: nums = [3,2,1,5,6,4], k = 2
 *     Output: 5
 *
 * Example 2:
 *     Input: nums = [3,2,3,1,2,4,5,5,6], k = 4
 *     Output: 4
 *
 * Constraints:
 *     - 1 <= k <= nums.length <= 105
 *     - -104 <= nums[i] <= 104
 *
 * Template (python3):
 *     class Solution:
 *         def findKthLargest(self, nums: List[int], k: int) -> int:
 *
 * Hint: Use a min-heap of size k to efficiently find the kth largest element.
 */

function solve(nums, k) {
  throw new Error("NotImplementedError");
}

const tests = [
  { label: "example 1", input: [[3, 2, 1, 5, 6, 4], 2], expected: 5 },
  { label: "example 2", input: [[3, 2, 3, 1, 2, 4, 5, 5, 6], 4], expected: 4 },
  { label: "single element", input: [[1], 1], expected: 1 },
  { label: "negative numbers", input: [[-1, -2, -3], 1], expected: -1 },
  { label: "all duplicates", input: [[5, 5, 5, 5], 2], expected: 5 },
  { label: "k equals length", input: [[1, 2, 3], 3], expected: 1 },
  { label: "mixed negatives and zero", input: [[-100, 0, 100], 2], expected: 0 },
  { label: "100 elements k=50", input: [Array.from({ length: 100 }, (_, i) => i + 1), 50], expected: 51 },
  { label: "all negative duplicates", input: [[-1, -1, -1, -1], 3], expected: -1 },
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
