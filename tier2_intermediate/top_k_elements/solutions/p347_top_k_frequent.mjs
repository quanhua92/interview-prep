/**
 * P347: Top K Frequent Elements (Medium)
 * https://leetcode.com/problems/top-k-frequent-elements/
 * Topics: Array, Hash Table, Divide and Conquer, Sorting, Heap (Priority Queue), Bucket Sort, Counting, Quickselect
 *
 * Given an integer array nums and an integer k, return the k most frequent elements. You may return the answer in any order.
 *
 * Example 1:
 *     Input: nums = [1,1,1,2,2,3], k = 2
 *     Output: [1,2]
 *
 * Example 2:
 *     Input: nums = [1], k = 1
 *     Output: [1]
 *
 * Constraints:
 *     - 1 <= nums.length <= 105
 *     - -104 <= nums[i] <= 104
 *     - k is in the range [1, the number of unique elements in the array].
 *     - It is guaranteed that the answer is unique.
 *
 * Follow up:
 *     - Your algorithm's time complexity must be better than O(n log n), where n is the array's size.
 *
 * Template (python3):
 *     class Solution:
 *         def topKFrequent(self, nums: List[int], k: int) -> List[int]:
 *
 * Hint: Use a frequency counter and a min-heap of size k.
 */

function solve(nums, k) {
  const count = new Map();
  for (const n of nums) {
    count.set(n, (count.get(n) || 0) + 1);
  }
  return [...count.entries()]
    .sort((a, b) => b[1] - a[1] || b[0] - a[0])
    .slice(0, k)
    .map((e) => e[0]);
}

const tests = [
  { label: "example 1", input: [[1, 1, 1, 2, 2, 3], 2], expected: [1, 2] },
  { label: "example 2", input: [[1], 1], expected: [1] },
  { label: "distinct frequencies", input: [[7, 7, 7, 7, 1, 2, 2, 2], 2], expected: [7, 2] },
  { label: "all freq 1", input: [[1, 2, 3, 4, 5, 6], 3], expected: [6, 5, 4] },
  { label: "all same element", input: [[1, 1, 1, 1], 1], expected: [1] },
  { label: "clear frequency ranking", input: [[1, 1, 2, 2, 2, 3, 3, 3, 3], 2], expected: [3, 2] },
  { label: "negative numbers", input: [[-1, -1, -1, 2, 2], 1], expected: [-1] },
  { label: "zero values", input: [[0, 0, 0, 0, 1, 1, 2], 2], expected: [0, 1] },
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
