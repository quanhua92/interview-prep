"""
P398: Random Pick Index [PREMIUM] (Medium)
https://leetcode.com/problems/random-pick-index/
Topics: Hash Table, Math, Reservoir Sampling, Randomized

Given an integer array nums with possible duplicates, randomly output the index of a given target number. You can assume that the given target number must exist in the array.
Implement the Solution class:
Example 1:
    Input
Example 1:
    ["Solution", "pick", "pick", "pick"]
    [[[1, 2, 3, 3, 3]], [3], [1], [3]]
    Output
    [null, 4, 0, 2]

    Explanation
    Solution solution = new Solution([1, 2, 3, 3, 3]);
    solution.pick(3); // It should return either index 2, 3, or 4 randomly. Each index should have equal probability of returning.
    solution.pick(1); // It should return 0. Since in the array only nums[0] is equal to 1.
    solution.pick(3); // It should return either index 2, 3, or 4 randomly. Each index should have equal probability of returning.

Constraints:
    - 1 <= nums.length <= 2 * 104
    - -231 <= nums[i] <= 231 - 1
    - target is an integer from nums.
    - At most 104 calls will be made to pick.

Template (python3):
    class Solution:

        def __init__(self, nums: List[int]):


        def pick(self, target: int) -> int:



    # Your Solution object will be instantiated and called as such:
    # obj = Solution(nums)
    # param_1 = obj.pick(target)
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase
from collections import defaultdict


class Solution(Problem):
    name = "398. Random Pick Index"
    test_cases = [
        TestCase(
            input=([1, 2, 3, 3, 3], 3),
            expected=[2, 3, 4],
            label="returns valid indices for target 3",
        ),
        TestCase(
            input=([1, 2, 3, 3, 3], 1),
            expected=[0],
            label="returns valid indices for target 1",
        ),
    ]

    def solve(self, nums: list[int], target: int) -> list[int]:

        result = []
        left = 0
        while left < len(nums):
            if nums[left] == target:
                right = left
                while right < len(nums) and nums[right] == target:
                    result.append(right)
                    right += 1
                return result
            left += 1
        return result

    def solve_alternative(self, nums: list[int], target: int) -> list[int]:
        index_map: dict[int, list[int]] = defaultdict(list)
        for i, num in enumerate(nums):
            index_map[num].append(i)
        return index_map.get(target, [])


if __name__ == "__main__":
    Solution().run()
