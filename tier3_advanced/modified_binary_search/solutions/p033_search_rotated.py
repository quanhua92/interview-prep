"""P033: Search in Rotated Sorted Array (Medium)

TODO: Implement solve() below.
Hint: Determine which half is sorted, then check if target lies in that half.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase

class Solution(Problem):
    name = "33. Search in Rotated Sorted Array"
    test_cases = [
        TestCase(input=([4,5,6,7,0,1,2], 0), expected=4, label="example 1"),
        TestCase(input=([4,5,6,7,0,1,2], 3), expected=-1, label="example 2"),
        TestCase(input=([1], 0), expected=-1, label="single element"),
    ]

    def solve(self, nums: list[int], target: int) -> int:
        left, right = 0, len(nums) - 1
        while left <= right:
            mid = left + (right - left) // 2
            if nums[mid] == target:
                return mid
            if nums[left] <= nums[mid]:
                if nums[left] <= target < nums[mid]:
                    right = mid - 1
                else:
                    left = mid + 1
            else:
                if nums[mid] < target <= nums[right]:
                    left = mid + 1
                else:
                    right = mid - 1
        return -1

if __name__ == "__main__":
    Solution().run()
