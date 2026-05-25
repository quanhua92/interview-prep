/**
 * P90: Subsets II (Medium)
 * https://leetcode.com/problems/subsets-ii/
 * Topics: Array, Backtracking, Bit Manipulation
 *
 * Given an integer array nums that may contain duplicates, return all possible subsets (the power set).
 * The solution set must not contain duplicate subsets. Return the solution in any order.
 *
 * Example 1:
 *     Input: nums = [1,2,2]
 *     Output: [[],[1],[1,2],[1,2,2],[2],[2,2]]
 *
 * Example 2:
 *     Input: nums = [0]
 *     Output: [[],[0]]
 *
 * Constraints:
 *     - 1 <= nums.length <= 10
 *     - -10 <= nums[i] <= 10
 *
 * Template (python3):
 *     class Solution:
 *         def subsetsWithDup(self, nums: List[int]) -> List[List[int]]:
 *
 * Hint: Sort first, then skip duplicates at the same recursion level during backtracking.
 */

function solve(nums) {
  throw new Error("NotImplementedError");
}

const tests = [
  { label: "example 1", input: [[1, 2, 2]], expected: [[], [1], [1, 2], [1, 2, 2], [2], [2, 2]] },
  { label: "example 2", input: [[0]], expected: [[], [0]] },
  { label: "all duplicates", input: [[2, 2, 2]], expected: [[], [2], [2, 2], [2, 2, 2]] },
  { label: "multiple duplicates", input: [[1, 1, 2, 2]], expected: [[], [1], [1, 1], [1, 1, 2], [1, 1, 2, 2], [1, 2], [1, 2, 2], [2], [2, 2]] },
  { label: "negative duplicates", input: [[-1, -1, 0]], expected: [[], [-1], [-1, -1], [-1, -1, 0], [-1, 0], [0]] },
  { label: "all same element", input: [[1, 1, 1, 1]], expected: [[], [1], [1, 1], [1, 1, 1], [1, 1, 1, 1]] },
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
