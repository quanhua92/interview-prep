/*
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
 *     - 1 <= coins[i] <= 2^31 - 1
 *     - 0 <= amount <= 10^4
 *
 * Template (python3):
 *     class Solution:
 *         def coinChange(self, coins: List[int], amount: int) -> int:
 *
 * Hint: Use bottom-up DP where dp[i] is the minimum coins needed for amount i.
 */

use wasm_libs::*;

fn coin_change(coins: &[i32], amount: i32) -> i32 {
    todo!();
}

fn main() {
    let coins = read_ints();
    let amount = read_int();
    write_int(coin_change(&coins, amount));
}
