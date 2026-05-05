"""P0169: Majority Element (Easy)

TODO: Implement solve() below.
Hint: Use Boyer-Moore voting algorithm — maintain a candidate and count.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase

class Solution(Problem):
    name = "169. Majority Element"
    test_cases = [
        TestCase(input=[3,2,3], expected=3, label="example 1"),
        TestCase(input=[2,2,1,1,1,2,2], expected=2, label="example 2"),
        TestCase(input=[1], expected=1, label="single element"),
    ]

    def solve(self, nums: list[int]) -> int:
        candidate = nums[0]
        count = 1
        for num in nums[1:]:
            if count == 0:
                candidate = num
                count = 1
            elif num == candidate:
                count += 1
            else:
                count -= 1
        return candidate

if __name__ == "__main__":
    Solution().run()
