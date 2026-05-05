"""P410: Split Array Largest Sum (Hard)

TODO: Implement solve() below.
Hint: Binary search the answer in [max(nums), sum(nums)] and check feasibility greedily.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "410. Split Array Largest Sum"
    test_cases = [
        TestCase(input=([7,2,5,10,8], 2), expected=18, label="example 1"),
        TestCase(input=([1,2,3,4,5], 2), expected=9, label="example 2"),
        TestCase(input=([1,4,4], 3), expected=4, label="example 3"),
    ]

    def solve(self, nums: list[int], k: int) -> int:
        left, right = max(nums), sum(nums)

        def feasible(max_sum: int) -> bool:
            """Check if we can split nums into <= k subarrays with max sum <= max_sum."""
            count = 1
            current = 0
            for n in nums:
                current += n
                if current > max_sum:
                    count += 1
                    current = n
                    if count > k:
                        return False
            return True

        while left < right:
            mid = left + (right - left) // 2
            if feasible(mid):
                right = mid
            else:
                left = mid + 1
        return left


if __name__ == "__main__":
    Solution().run()
