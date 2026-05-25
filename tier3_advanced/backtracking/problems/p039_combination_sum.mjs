/**
 * P39: Combination Sum (Medium)
 * https://leetcode.com/problems/combination-sum/
 * Topics: Array, Backtracking
 *
 * Given an array of distinct integers candidates and a target integer target, return a list of all unique combinations of candidates where the chosen numbers sum to target. You may return the combinations in any order.
 * The same number may be chosen from candidates an unlimited number of times. Two combinations are unique if the frequency of at least one of the chosen numbers is different.
 * The test cases are generated such that the number of unique combinations that sum up to target is less than 150 combinations for the given input.
 *
 * Example 1:
 *     Input: candidates = [2,3,6,7], target = 7
 *     Output: [[2,2,3],[7]]
 *     Explanation:
 *     2 and 3 are candidates, and 2 + 2 + 3 = 7. Note that 2 can be used multiple times.
 *     7 is a candidate, and 7 = 7.
 *     These are the only two combinations.
 *
 * Example 2:
 *     Input: candidates = [2,3,5], target = 8
 *     Output: [[2,2,2,2],[2,3,3],[3,5]]
 *
 * Example 3:
 *     Input: candidates = [2], target = 1
 *     Output: []
 *
 * Constraints:
 *     - 1 <= candidates.length <= 30
 *     - 2 <= candidates[i] <= 40
 *     - All elements of candidates are distinct.
 *     - 1 <= target <= 40
 *
 * Template (python3):
 *     class Solution:
 *         def combinationSum(self, candidates: List[int], target: int) -> List[List[int]]:
 *
 * Hint: Use backtracking with early pruning when the remaining sum goes negative.
 */

function solve(candidates, target) {
  throw new Error("NotImplementedError");
}

const tests = [
  { label: "example 1", input: [[2, 3, 6, 7], 7], expected: [[2, 2, 3], [7]] },
  { label: "example 2", input: [[2, 3, 5], 8], expected: [[2, 2, 2, 2], [2, 3, 3], [3, 5]] },
  { label: "no solution", input: [[2], 1], expected: [] },
  { label: "single candidate equals target", input: [[5], 5], expected: [[5]] },
  { label: "reuse single candidate", input: [[2], 4], expected: [[2, 2]] },
  { label: "unsorted candidates multiple combos", input: [[8, 7, 4, 3], 11], expected: [[3, 4, 4], [3, 8], [4, 7]] },
  { label: "no valid combination", input: [[3, 5], 7], expected: [] },
  { label: "triple reuse", input: [[3], 9], expected: [[3, 3, 3]] },
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
