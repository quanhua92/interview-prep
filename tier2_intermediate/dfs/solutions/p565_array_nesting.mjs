/**
 * P565: Array Nesting [PREMIUM] (Medium)
 * https://leetcode.com/problems/array-nesting/
 * Topics: Array, Depth-First Search
 *
 * You are given an integer array nums of length n where nums is a permutation of the numbers in the range [0, n - 1].
 * You should build a set s[k] = {nums[k], nums[nums[k]], nums[nums[nums[k]]], ... } subjected to the following rule:
 * Return the longest length of a set s[k].
 * Example 1:
 *     Input: nums = [5,4,0,3,1,6,2]
 *     Output: 4
 *     Explanation:
 *     nums[0] = 5, nums[1] = 4, nums[2] = 0, nums[3] = 3, nums[4] = 1, nums[5] = 6, nums[6] = 2.
 *     One of the longest sets s[k]:
 *     s[0] = {nums[0], nums[5], nums[6], nums[2]} = {5, 6, 2, 0}
 *
 * Example 2:
 *     Input: nums = [0,1,2]
 *     Output: 1
 *
 * Constraints:
 *     - 1 <= nums.length <= 105
 *     - 0 <= nums[i] < nums.length
 *     - All the values of nums are unique.
 *
 * Template (python3):
 *     class Solution:
 *         def arrayNesting(self, nums: List[int]) -> int:
 */

function solve(nums) {
  let maxLen = 0;
  const visited = new Array(nums.length).fill(false);
  for (let i = 0; i < nums.length; i++) {
    if (!visited[i]) {
      let count = 0;
      let j = i;
      while (!visited[j]) {
        visited[j] = true;
        j = nums[j];
        count++;
      }
      if (count > maxLen) maxLen = count;
    }
  }
  return maxLen;
}

const tests = [
  { label: "example 1", input: [5, 4, 0, 3, 1, 6, 2], expected: 4 },
  { label: "example 2", input: [0, 1, 2], expected: 1 },
  { label: "single element", input: [0], expected: 1 },
  { label: "two element cycle", input: [1, 0], expected: 2 },
  { label: "full single cycle", input: [2, 0, 1], expected: 3 },
  { label: "two separate cycles", input: [0, 2, 1], expected: 2 },
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
