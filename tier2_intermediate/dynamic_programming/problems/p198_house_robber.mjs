/**
 * P198: House Robber (Medium)
 * https://leetcode.com/problems/house-robber/
 * Topics: Array, Dynamic Programming
 * 
 * You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed, the only constraint stopping you from robbing each of them is that adjacent houses have security systems connected and it will automatically contact the police if two adjacent houses were broken into on the same night.
 * Given an integer array nums representing the amount of money of each house, return the maximum amount of money you can rob tonight without alerting the police.
 * 
 * Example 1:
 *     Input: nums = [1,2,3,1]
 *     Output: 4
 *     Explanation: Rob house 1 (money = 1) and then rob house 3 (money = 3).
 *     Total amount you can rob = 1 + 3 = 4.
 * 
 * Example 2:
 *     Input: nums = [2,7,9,3,1]
 *     Output: 12
 *     Explanation: Rob house 1 (money = 2), rob house 3 (money = 9) and rob house 5 (money = 1).
 *     Total amount you can rob = 2 + 9 + 1 = 12.
 * 
 * Constraints:
 *     - 1 <= nums.length <= 100
 *     - 0 <= nums[i] <= 400
 * 
 * Template (python3):
 *     class Solution:
 *         def rob(self, nums: List[int]) -> int:
 * 
 * Hint: Use two variables (prev, curr) -- for each house decide to rob or skip.
 */
function solve(nums)
  let prev = 0, curr = 0;
  for (const num of nums)
    const temp = curr;
    curr = Math.max(curr, prev + num);
    prev = temp;
  }
  return curr; {
    throw new Error("NotImplementedError");
}

const tests = [
  { label: "example 1", input: [1, 2, 3, 1], expected: 4 },
  { label: "example 2", input: [2, 7, 9, 3, 1], expected: 12 },
  { label: "single house", input: [1], expected: 1 },
  { label: "no houses", input: [], expected: 0 },
  { label: "alternate houses equal", input: [2, 1, 1, 2], expected: 4 },
  { label: "all zeros", input: [0, 0, 0], expected: 0 },
  { label: "two houses", input: [1, 2], expected: 2 },
  { label: "alternating high low", input: [10, 1, 10, 1, 10], expected: 30 },
  { label: "three peaks", input: [100, 1, 1, 100, 1, 1, 100], expected: 300 },
  { label: "max values large array", input: Array(100).fill(400), expected: 20000 },
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
