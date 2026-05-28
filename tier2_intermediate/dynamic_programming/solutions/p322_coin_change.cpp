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
 *     - 1 <= coins[i] <= 231 - 1
 *     - 0 <= amount <= 104
 *
 * Template (python3):
 *     class Solution:
 *         def coinChange(self, coins: List[int], amount: int) -> int:
 *
 * Hint: Use bottom-up DP where dp[i] is the minimum coins needed for amount i.
 */

#include "io.h"
#include <algorithm>

int coinChange(std::vector<int> coins, int amount) {
    int INF = amount + 1;
    std::vector<int> dp(amount + 1, INF);
    dp[0] = 0;
    for (int i = 1; i <= amount; i++) {
        for (int c : coins) {
            if ((long long)c <= i) {
                dp[i] = std::min(dp[i], dp[i - c] + 1);
            }
        }
    }
    return dp[amount] < INF ? dp[amount] : -1;
}

int main(void) {
    std::vector<int> coins = read_ints();
    int amount = read_ints()[0];
    write_int(coinChange(coins, amount));
    return 0;
}
