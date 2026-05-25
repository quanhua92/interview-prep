/**
 * P518: Coin Change II [PREMIUM] (Medium)
 * https://leetcode.com/problems/coin-change-ii/
 * Topics: Array, Dynamic Programming
 *
 * You are given an integer array coins representing coins of different denominations and an integer amount representing a total amount of money.
 * Return the number of combinations that make up that amount. If that amount of money cannot be made up by any combination of the coins, return 0.
 * You may assume that you have an infinite number of each kind of coin.
 * The answer is guaranteed to fit into a signed 32-bit integer.
 * Example 1:
 *     Input: amount = 5, coins = [1,2,5]
 *     Output: 4
 *     Explanation: there are four ways to make up the amount:
 *     5=5
 *     5=2+2+1
 *     5=2+1+1+1
 *     5=1+1+1+1+1
 *
 * Example 2:
 *     Input: amount = 3, coins = [2]
 *     Output: 0
 *     Explanation: the amount of 3 cannot be made up just with coins of 2.
 *
 * Example 3:
 *     Input: amount = 10, coins = [10]
 *     Output: 1
 *
 * Constraints:
 *     - 1 <= coins.length <= 300
 *     - 1 <= coins[i] <= 5000
 *     - All the values of coins are unique.
 *     - 0 <= amount <= 5000
 *
 * Template (python3):
 *     class Solution:
 *         def change(self, amount: int, coins: List[int]) -> int:
 */

function solve(amount, coins) {
  const dp = new Array(amount + 1).fill(0);
  dp[0] = 1;
  for (const coin of coins) {
    for (let a = coin; a <= amount; a++) {
      dp[a] += dp[a - coin];
    }
  }
  return dp[amount];
}

const tests = [
  { label: "example 1", input: [5, [1, 2, 5]], expected: 4 },
  { label: "example 2", input: [3, [2]], expected: 0 },
  { label: "example 3", input: [10, [10]], expected: 1 },
  { label: "zero amount", input: [0, [1, 2, 5]], expected: 1 },
  { label: "single coin exact amount", input: [1, [1]], expected: 1 },
  { label: "large amount", input: [500, [1, 2, 5]], expected: 12701 },
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
