"""P135: Candy (Hard)

TODO: Implement solve() below.
Hint: Two-pass greedy: left-to-right then right-to-left, taking the max of both passes.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase

class Solution(Problem):
    name = "135. Candy"
    test_cases = [
        TestCase(input=[1,0,2], expected=5, label="example 1"),
        TestCase(input=[1,2,2], expected=4, label="example 2"),
        TestCase(input=[1,3,2,2,1], expected=7, label="decreasing then flat"),
        TestCase(input=[1], expected=1, label="single child"),
    ]

    def solve(self, ratings: list[int]) -> int:
        n = len(ratings)
        if n == 1:
            return 1

        candies = [1] * n

        # Left to right: give more if rating is higher than left neighbor
        for i in range(1, n):
            if ratings[i] > ratings[i - 1]:
                candies[i] = candies[i - 1] + 1

        # Right to left: give more if rating is higher than right neighbor
        for i in range(n - 2, -1, -1):
            if ratings[i] > ratings[i + 1]:
                candies[i] = max(candies[i], candies[i + 1] + 1)

        return sum(candies)

if __name__ == "__main__":
    Solution().run()
