/*
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
#include "ctest.h"
#include <stdlib.h>

int change(int amount, int *coins, int coinsSize) {
    /* TODO: Implement */
    return 0;
}

int main(void) {
    int passed = 0;
    int total = 6;
    struct TC { const char *label; int amount; int coins[300]; int csz; int expected; };
    struct TC tests[] = {
        {"example 1", 5, {1,2,5}, 3, 4},
        {"example 2", 3, {2}, 1, 0},
        {"example 3", 10, {10}, 1, 1},
        {"zero amount", 0, {1,2,5}, 3, 1},
        {"single coin exact amount", 1, {1}, 1, 1},
        {"large amount", 500, {1,2,5}, 3, 12701},
    };
    for (int i = 0; i < total; i++) {
        int got = change(tests[i].amount, tests[i].coins, tests[i].csz);
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
