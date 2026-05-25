/**
 * P78: Subsets (Medium)
 * https://leetcode.com/problems/subsets/
 * Topics: Array, Backtracking, Bit Manipulation
 *
 * Given an integer array nums of unique elements, return all possible subsets (the power set).
 * The solution set must not contain duplicate subsets. Return the solution in any order.
 *
 * Example 1:
 *     Input: nums = [1,2,3]
 *     Output: [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
 *
 * Example 2:
 *     Input: nums = [0]
 *     Output: [[],[0]]
 *
 * Constraints:
 *     - 1 <= nums.length <= 10
 *     - -10 <= nums[i] <= 10
 *     - All the numbers of nums are unique.
 *
 * Template (python3):
 *     class Solution:
 *         def subsets(self, nums: List[int]) -> List[List[int]]:
 *
 * Hint: Use backtracking to generate all possible subsets by including/excluding each element.
 */

function solve(nums) {
  throw new Error("NotImplementedError");
}

const tests = [
  { label: "example 1", input: [[1, 2, 3]], expected: [[], [1], [1, 2], [1, 2, 3], [1, 3], [2], [2, 3], [3]] },
  { label: "example 2", input: [[0]], expected: [[], [0]] },
  { label: "two elements", input: [[1, 2]], expected: [[], [1], [1, 2], [2]] },
  { label: "negative numbers", input: [[-1, 0, 1]], expected: [[], [-1], [-1, 0], [-1, 0, 1], [-1, 1], [0], [0, 1], [1]] },
  { label: "four elements", input: [[1, 2, 3, 4]], expected: [[], [1], [1, 2], [1, 2, 3], [1, 2, 3, 4], [1, 2, 4], [1, 3], [1, 3, 4], [1, 4], [2], [2, 3], [2, 3, 4], [2, 4], [3], [3, 4], [4]] },
  { label: "unsorted input", input: [[3, 1]], expected: [[], [3], [3, 1], [1]] },
];
let passed = 0;
for (let i = 0; i < tests.length; i++) {
  const t = tests[i];
  const got = solve(t.input[0]);
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
