/**
 * P46: Permutations (Medium)
 * https://leetcode.com/problems/permutations/
 * Topics: Array, Backtracking
 *
 * Given an array nums of distinct integers, return all the possible permutations. You can return the answer in any order.
 *
 * Example 1:
 *     Input: nums = [1,2,3]
 *     Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
 *
 * Example 2:
 *     Input: nums = [0,1]
 *     Output: [[0,1],[1,0]]
 *
 * Example 3:
 *     Input: nums = [1]
 *     Output: [[1]]
 *
 * Constraints:
 *     - 1 <= nums.length <= 6
 *     - -10 <= nums[i] <= 10
 *     - All the integers of nums are unique.
 *
 * Template (python3):
 *     class Solution:
 *         def permute(self, nums: List[int]) -> List[List[int]]:
 *
 * Hint: Use backtracking with swapping to generate all permutations in-place.
 */

function solve(nums) {
  throw new Error("NotImplementedError");
}

const tests = [
  { label: "example 1", input: [[1, 2, 3]], expected: [[1, 2, 3], [1, 3, 2], [2, 1, 3], [2, 3, 1], [3, 1, 2], [3, 2, 1]] },
  { label: "example 2", input: [[0, 1]], expected: [[0, 1], [1, 0]] },
  { label: "single element", input: [[1]], expected: [[1]] },
  { label: "negative and zero mix", input: [[-1, 0, 1]], expected: [[-1, 0, 1], [-1, 1, 0], [0, -1, 1], [0, 1, -1], [1, -1, 0], [1, 0, -1]] },
  { label: "two negative elements", input: [[-3, -1]], expected: [[-3, -1], [-1, -3]] },
  {
    label: "four elements", input: [[1, 2, 3, 4]],
    expected: [
      [1, 2, 3, 4], [1, 2, 4, 3], [1, 3, 2, 4], [1, 3, 4, 2], [1, 4, 2, 3], [1, 4, 3, 2],
      [2, 1, 3, 4], [2, 1, 4, 3], [2, 3, 1, 4], [2, 3, 4, 1], [2, 4, 1, 3], [2, 4, 3, 1],
      [3, 1, 2, 4], [3, 1, 4, 2], [3, 2, 1, 4], [3, 2, 4, 1], [3, 4, 1, 2], [3, 4, 2, 1],
      [4, 1, 2, 3], [4, 1, 3, 2], [4, 2, 1, 3], [4, 2, 3, 1], [4, 3, 1, 2], [4, 3, 2, 1],
    ],
  },
  { label: "single negative element", input: [[-5]], expected: [[-5]] },
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
