/**
 * P55: Jump Game (Medium)
 * https://leetcode.com/problems/jump-game/
 * Topics: Array, Dynamic Programming, Greedy
 *
 * You are given an integer array nums. You are initially positioned at the array's first index, and each element in the array represents your maximum jump length at that position.
 * Return true if you can reach the last index, or false otherwise.
 *
 * Example 1:
 *     Input: nums = [2,3,1,1,4]
 *     Output: true
 *     Explanation: Jump 1 step from index 0 to 1, then 3 steps to the last index.
 *
 * Example 2:
 *     Input: nums = [3,2,1,0,4]
 *     Output: false
 *     Explanation: You will always arrive at index 3 no matter what. Its maximum jump length is 0, which makes it impossible to reach the last index.
 *
 * Constraints:
 *     - 1 <= nums.length <= 104
 *     - 0 <= nums[i] <= 105
 *
 * Template (python3):
 *     class Solution:
 *         def canJump(self, nums: List[int]) -> bool:
 *
 * Hint: Track the farthest reachable index; if you pass it, the end is unreachable.
 */

function solve(nums) {
  let maxReach = 0;
  for (let i = 0; i < nums.length; i++) {
    if (i > maxReach) return false;
    maxReach = Math.max(maxReach, i + nums[i]);
  }
  return true;
}

const tests = [
  { label: "example 1", input: [[2, 3, 1, 1, 4]], expected: true },
  { label: "example 2", input: [[3, 2, 1, 0, 4]], expected: false },
  { label: "single element", input: [[0]], expected: true },
  { label: "all ones", input: [[1, 1, 1, 1, 1]], expected: true },
  { label: "big jump from start", input: [[5, 0, 0, 0, 0]], expected: true },
  { label: "stuck at start", input: [[0, 1]], expected: false },
  { label: "two elements reachable", input: [[2, 0]], expected: true },
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
