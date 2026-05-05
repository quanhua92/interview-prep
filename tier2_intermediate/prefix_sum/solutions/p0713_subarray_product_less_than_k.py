"""P0713: Subarray Product Less Than K (Medium)

TODO: Implement solve() below.
Hint: Use a sliding window where you shrink from the left when product >= k.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase

class Solution(Problem):
    name = "713. Subarray Product Less Than K"
    test_cases = [
        TestCase(input=([10,5,2,6], 100), expected=8, label="example 1"),
        TestCase(input=([1,2,3], 0), expected=0, label="zero k"),
        TestCase(input=([1,1,1], 2), expected=6, label="all ones"),
    ]

    def solve(self, nums: list[int], k: int) -> int:
        if k <= 1:
            return 0

        count = 0
        product = 1
        left = 0

        for right in range(len(nums)):
            product *= nums[right]
            while product >= k:
                product //= nums[left]
                left += 1
            count += right - left + 1

        return count

if __name__ == "__main__":
    Solution().run()
