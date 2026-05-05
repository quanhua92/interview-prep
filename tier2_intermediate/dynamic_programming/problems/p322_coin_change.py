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
        raise NotImplementedError("TODO: Implement solve(self, coins: list[int], amount: int) -> int")

if __name__ == "__main__":
    Solution().run()
