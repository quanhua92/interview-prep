/**
 * P322: Coin Change (Medium)
 * https://leetcode.com/problems/coin-change/
 * Topics: Array, Dynamic Programming, Breadth-First Search
 *
 * You are given an integer array coins representing coins of different denominations and an integer amount representing a total amount of money.
 * Return the fewest number of coins that you need to make up that amount. If that amount of money cannot be made up by any combination of the coins, return -1.
 * You may assume that you have an infinite number of each kind of coin.
 *
 * Example 1:
 *     Input: coins = [1,2,5], amount = 11
 *     Output: 3
 *     Explanation: 11 = 5 + 5 + 1
 *
 * Example 2:
 *     Input: coins = [2], amount = 3
 *     Output: -1
 *
 * Example 3:
 *     Input: coins = [1], amount = 0
 *     Output: 0
 *
 * Constraints:
 *     - 1 <= coins.length <= 12
 *     - 1 <= coins[i] <= 231 - 1
 *     - 0 <= amount <= 104
 *
 * Template (python3):
 *     class Solution:
 *         def coinChange(self, coins: List[int], amount: int) -> int:
 *
 * Hint: Use bottom-up DP where dp[i] is the minimum coins needed for amount i.
 */

function solve(coins, amount) {
  throw new Error("NotImplementedError");
}

const tests = [
  { label: "example 1", input: [[1, 2, 5], 11], expected: 3 },
  { label: "example 2", input: [[2], 3], expected: -1 },
  { label: "zero amount", input: [[1], 0], expected: 0 },
  { label: "smallest amount", input: [[1], 1], expected: 1 },
  { label: "suboptimal greedy", input: [[1, 3, 4], 6], expected: 2 },
  { label: "coin larger than amount", input: [[2], 1], expected: -1 },
  { label: "single coin exact match", input: [[7], 7], expected: 1 },
  { label: "large amount", input: [[1, 2, 5], 100], expected: 20 },
  { label: "multiple denominations", input: [[2, 5, 10, 1], 27], expected: 4 },
  { label: "large coin value", input: [[1, 2147483647], 2], expected: 2 },
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
