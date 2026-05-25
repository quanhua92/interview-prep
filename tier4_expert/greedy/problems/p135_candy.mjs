/**
 * P135: Candy (Hard)
 * https://leetcode.com/problems/candy/
 * Topics: Array, Greedy
 *
 * There are n children standing in a line. Each child is assigned a rating value given in the integer array ratings.
 * You are giving candies to these children subjected to the following requirements:
 * Return the minimum number of candies you need to have to distribute the candies to the children.
 *
 * Example 1:
 *     Input: ratings = [1,0,2]
 *     Output: 5
 *     Explanation: You can allocate to the first, second and third child with 2, 1, 2 candies respectively.
 *
 * Example 2:
 *     Input: ratings = [1,2,2]
 *     Output: 4
 *     Explanation: You can allocate to the first, second and third child with 1, 2, 1 candies respectively.
 *     The third child gets 1 candy because it satisfies the above two conditions.
 *
 * Constraints:
 *     - n == ratings.length
 *     - 1 <= n <= 2 * 104
 *     - 0 <= ratings[i] <= 2 * 104
 *
 * Template (python3):
 *     class Solution:
 *         def candy(self, ratings: List[int]) -> int:
 *
 * Hint: Two-pass greedy: left-to-right then right-to-left, taking the max of both passes.
 */

function solve(ratings) {
  throw new Error("NotImplementedError");
}

const tests = [
  { label: "example 1", input: [[1, 0, 2]], expected: 5 },
  { label: "example 2", input: [[1, 2, 2]], expected: 4 },
  { label: "decreasing then flat", input: [[1, 3, 2, 2, 1]], expected: 7 },
  { label: "single child", input: [[1]], expected: 1 },
  { label: "all same ratings", input: [[2, 2, 2, 2]], expected: 4 },
  { label: "strictly increasing", input: [[1, 2, 3, 4]], expected: 10 },
  { label: "strictly decreasing", input: [[4, 3, 2, 1]], expected: 10 },
  { label: "increase then drop", input: [[1, 3, 4, 5, 2]], expected: 11 },
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
