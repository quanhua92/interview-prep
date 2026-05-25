/**
 * P167: Two Sum II - Input Array Is Sorted (Medium)
 * https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/
 * Topics: Array, Two Pointers, Binary Search
 * 
 * Given a 1-indexed array of integers numbers that is already sorted in non-decreasing order, find two numbers such that they add up to a specific target number. Let these two numbers be numbers[index1] and numbers[index2] where 1 <= index1 < index2 <= numbers.length.
 * Return the indices of the two numbers, index1 and index2, added by one as an integer array [index1, index2] of length 2.
 * The tests are generated such that there is exactly one solution. You may not use the same element twice.
 * Your solution must use only constant extra space.
 * 
 * Example 1:
 *     Input: numbers = [2,7,11,15], target = 9
 *     Output: [1,2]
 *     Explanation: The sum of 2 and 7 is 9. Therefore, index1 = 1, index2 = 2. We return [1, 2].
 * 
 * Example 2:
 *     Input: numbers = [2,3,4], target = 6
 *     Output: [1,3]
 *     Explanation: The sum of 2 and 4 is 6. Therefore index1 = 1, index2 = 3. We return [1, 3].
 * 
 * Example 3:
 *     Input: numbers = [-1,0], target = -1
 *     Output: [1,2]
 *     Explanation: The sum of -1 and 0 is -1. Therefore index1 = 1, index2 = 2. We return [1, 2].
 * 
 * Constraints:
 *     - 2 <= numbers.length <= 3 * 104
 *     - -1000 <= numbers[i] <= 1000
 *     - numbers is sorted in non-decreasing order.
 *     - -1000 <= target <= 1000
 *     - The tests are generated such that there is exactly one solution.
 * 
 * Hint: Use two pointers from both ends of the sorted array.
 */

function solve(numbers, target) {
  let left = 0, right = numbers.length - 1;
  while (left < right) {
    const current = numbers[left] + numbers[right];
    if (current === target) {
      return [left + 1, right + 1];
    } else if (current < target) {
      left++;
    } else {
      right--;
    }
  }
  return [];
}

// --- tests ---
const tests = [
  { label: "example 1", input: [[2, 7, 11, 15], 9], expected: [1, 2] },
  { label: "example 2", input: [[2, 3, 4], 6], expected: [1, 3] },
  { label: "example 3", input: [[-1, 0], -1], expected: [1, 2] },
  { label: "all negatives", input: [[-10, -6, -4, -2], -10], expected: [2, 3] },
  { label: "exactly two elements", input: [[1, 2], 3], expected: [1, 2] },
  { label: "negative positive cross", input: [[-5, -3, 0, 2, 4, 6], 1], expected: [1, 6] },
  { label: "middle elements", input: [[1, 3, 4, 5, 7, 10, 11], 9], expected: [3, 4] },
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
