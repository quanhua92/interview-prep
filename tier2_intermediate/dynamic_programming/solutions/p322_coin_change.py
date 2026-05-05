"""P322: Coin Change (Medium)

TODO: Implement solve() below.
Hint: Use bottom-up DP where dp[i] is the minimum coins needed for amount i.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase

class Solution(Problem):
    name = "322. Coin Change"
    test_cases = [
        TestCase(input=([1,2,5], 11), expected=3, label="example 1"),
        TestCase(input=([2], 3), expected=-1, label="example 2"),
        TestCase(input=([1], 0), expected=0, label="zero amount"),
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
