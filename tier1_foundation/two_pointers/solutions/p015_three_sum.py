"""P015: 3Sum (Medium)

TODO: Implement solve() below.
Hint: Sort, iterate i, nested two pointers for remaining pair, skip duplicates.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "15. 3Sum"
    test_cases = [
        TestCase(input=[-1, 0, 1, 2, -1, -4], expected=sorted([sorted(t) for t in [[-1, -1, 2], [-1, 0, 1]]]), label="example 1"),
        TestCase(input=[0, 1, 1], expected=[], label="no triplets"),
        TestCase(input=[0, 0, 0], expected=[[0, 0, 0]], label="all zeros"),
        TestCase(input=[], expected=[], label="empty"),
    ]

    def solve(self, nums: list[int]) -> list[list[int]]:
        nums.sort()
        result: list[list[int]] = []
        n = len(nums)
        for i in range(n - 2):
            # Skip duplicates for i
            if i > 0 and nums[i] == nums[i - 1]:
                continue
            left, right = i + 1, n - 1
            while left < right:
                total = nums[i] + nums[left] + nums[right]
                if total < 0:
                    left += 1
                elif total > 0:
                    right -= 1
                else:
                    result.append([nums[i], nums[left], nums[right]])
                    # Skip duplicates for left
                    while left < right and nums[left] == nums[left + 1]:
                        left += 1
                    # Skip duplicates for right
                    while left < right and nums[right] == nums[right - 1]:
                        right -= 1
                    left += 1
                    right -= 1
        return sorted([sorted(t) for t in result])


if __name__ == "__main__":
    Solution().run()
