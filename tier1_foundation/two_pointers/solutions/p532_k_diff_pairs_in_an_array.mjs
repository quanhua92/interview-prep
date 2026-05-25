/**
 * P532: K-diff Pairs in an Array [PREMIUM] (Medium)
 * https://leetcode.com/problems/k-diff-pairs-in-an-array/
 * Topics: Array, Hash Table, Two Pointers, Binary Search, Sorting
 * 
 * Given an array of integers nums and an integer k, return the number of unique k-diff pairs in the array.
 * A k-diff pair is an integer pair (nums[i], nums[j]), where the following are true:
 * Notice that |val| denotes the absolute value of val.
 * Example 1:
 *     Input: nums = [3,1,4,1,5], k = 2
 *     Output: 2
 *     Explanation: There are two 2-diff pairs in the array, (1, 3) and (3, 5).
 *     Although we have two 1s in the input, we should only return the number of unique pairs.
 * 
 * Example 2:
 *     Input: nums = [1,2,3,4,5], k = 1
 *     Output: 4
 *     Explanation: There are four 1-diff pairs in the array, (1, 2), (2, 3), (3, 4) and (4, 5).
 * 
 * Example 3:
 *     Input: nums = [1,3,1,5,4], k = 0
 *     Output: 1
 *     Explanation: There is one 0-diff pair in the array, (1, 1).
 * 
 * Constraints:
 *     - 1 <= nums.length <= 104
 *     - -107 <= nums[i] <= 107
 *     - 0 <= k <= 107
 */

function solve(nums, k) {
  if (k < 0) return 0;
  nums = [...nums].sort((a, b) => a - b);
  let count = 0;
  let left = 0, right = 1;
  while (right < nums.length) {
    const diff = nums[right] - nums[left];
    if (diff < k) {
      right++;
    } else if (diff > k) {
      left++;
    } else {
      count++;
      const leftVal = nums[left];
      const rightVal = nums[right];
      while (left < nums.length && nums[left] === leftVal) left++;
      while (right < nums.length && nums[right] === rightVal) right++;
    }
    if (left === right) right++;
  }
  return count;
}

// --- tests ---
const tests = [
  { label: "example 1", input: [[3, 1, 4, 1, 5], 2], expected: 2 },
  { label: "example 2", input: [[1, 2, 3, 4, 5], 1], expected: 4 },
  { label: "example 3", input: [[1, 3, 1, 5, 4], 0], expected: 1 },
  { label: "single element", input: [[1], 1], expected: 0 },
  { label: "all same k=0", input: [[1, 1, 1, 1], 0], expected: 1 },
  { label: "k larger than range", input: [[1, 2, 3, 4, 5], 100], expected: 0 },
  { label: "all negatives", input: [[-1, -2, -3, -4, -5], 1], expected: 4 },
];
let passed = 0;
for (let i = 0; i < tests.length; i++) {
  const t = tests[i];
  const got = solve(t.input[0], t.input[1]);
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
