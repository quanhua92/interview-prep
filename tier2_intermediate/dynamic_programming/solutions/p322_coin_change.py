"""
P322: Coin Change (Medium)
https://leetcode.com/problems/coin-change/
Topics: Array, Dynamic Programming, Breadth-First Search

You are given an integer array coins representing coins of different denominations and an integer amount representing a total amount of money.
Return the fewest number of coins that you need to make up that amount. If that amount of money cannot be made up by any combination of the coins, return -1.
You may assume that you have an infinite number of each kind of coin.

Example 1:
    Input: coins = [1,2,5], amount = 11
    Output: 3
    Explanation: 11 = 5 + 5 + 1

Example 2:
    Input: coins = [2], amount = 3
    Output: -1

Example 3:
    Input: coins = [1], amount = 0
    Output: 0

Constraints:
    - 1 <= coins.length <= 12
    - 1 <= coins[i] <= 231 - 1
    - 0 <= amount <= 104

Template (python3):
    class Solution:
        def coinChange(self, coins: List[int], amount: int) -> int:

Hint: Use bottom-up DP where dp[i] is the minimum coins needed for amount i.
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "322. Coin Change"
    test_cases = [
        TestCase(input=([1, 2, 5], 11), expected=3, label="example 1"),
        TestCase(input=([2], 3), expected=-1, label="example 2"),
        TestCase(input=([1], 0), expected=0, label="zero amount"),
        TestCase(input=([1], 1), expected=1, label="smallest amount"),
        TestCase(input=([1, 3, 4], 6), expected=2, label="suboptimal greedy"),
        TestCase(input=([2], 1), expected=-1, label="coin larger than amount"),
        TestCase(input=([7], 7), expected=1, label="single coin exact match"),
        TestCase(input=([1, 2, 5], 100), expected=20, label="large amount"),
        TestCase(input=([2, 5, 10, 1], 27), expected=4, label="multiple denominations"),
        TestCase(input=([1, 2147483647], 2), expected=2, label="large coin value"),
    ]

    def solve(self, coins: list[int], amount: int) -> int:
        INF = amount + 1  # use integer sentinel instead of float
        dp = [INF] * (amount + 1)
        dp[0] = 0
        for i in range(1, amount + 1):
            for coin in coins:
                if coin <= i:
                    dp[i] = min(dp[i], dp[i - coin] + 1)
        return dp[amount] if dp[amount] != INF else -1


if __name__ == "__main__":
    Solution().run()
