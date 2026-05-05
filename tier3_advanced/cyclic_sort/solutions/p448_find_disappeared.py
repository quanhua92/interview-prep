"""P448: Find All Numbers Disappeared in an Array (Easy)

TODO: Implement solve() below.
Hint: Negate the value at index abs(n)-1 for each number. Indices with positive values are missing.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "448. Find All Numbers Disappeared in an Array"
    test_cases = [
        TestCase(input=[4,3,2,7,8,2,3,1], expected=[5,6], label="example 1"),
        TestCase(input=[1,1], expected=[2], label="example 2"),
        TestCase(input=[2,2], expected=[1], label="example 3"),
    ]

    def solve(self, nums: list[int]) -> list[int]:
        for n in nums:
            index = abs(n) - 1
            if nums[index] > 0:
                nums[index] = -nums[index]

        return [i + 1 for i in range(len(nums)) if nums[i] > 0]


if __name__ == "__main__":
    Solution().run()
