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
#include "ctest.h"
#include <limits.h>

int coinChange(int *coins, int coinsSize, int amount) {
    abort();
}

int main(void) {
    int passed = 0;
    int total = 10;
    struct TC { const char *label; int coins[12]; int csz; int amount; int expected; };
    struct TC tests[] = {
        {"example 1", {1,2,5}, 3, 11, 3},
        {"example 2", {2}, 1, 3, -1},
        {"zero amount", {1}, 1, 0, 0},
        {"smallest amount", {1}, 1, 1, 1},
        {"suboptimal greedy", {1,3,4}, 3, 6, 2},
        {"coin larger than amount", {2}, 1, 1, -1},
        {"single coin exact match", {7}, 1, 7, 1},
        {"large amount", {1,2,5}, 3, 100, 20},
        {"multiple denominations", {2,5,10,1}, 4, 27, 4},
        {"large coin value", {1,2147483647}, 2, 2, 2},
    };
    for (int i = 0; i < total; i++) {
        int got = coinChange(tests[i].coins, tests[i].csz, tests[i].amount);
        if (got == tests[i].expected) {
            passed++;
            printf("  Test %d (%s): PASS\n", i + 1, tests[i].label);
        } else {
            printf("  Test %d (%s): FAIL (expected %d, got %d)\n", i + 1, tests[i].label, tests[i].expected, got);
        }
    }
    printf("\n  %d/%d passed\n", passed, total);
    return passed == total ? 0 : 1;
}
