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
    - 1 <= nums.length <= 2 * 10^4
    - -2^31 <= nums[i] <= 2^31 - 1
    - target is an integer from nums.
    - At most 10^4 calls will be made to pick.

Template (python3):
    class Solution:

        def __init__(self, nums: List[int]):


        def pick(self, target: int) -> int:



    # Your Solution object will be instantiated and called as such:
    # obj = Solution(nums)
    # param_1 = obj.pick(target)
"""

import random
from collections import defaultdict

from src.wasm_libs.py.io import *

random.seed(42)


class Solution:
    def __init__(self, nums: list[int]):
        self.idx = defaultdict(list)
        for i, v in enumerate(nums):
            self.idx[v].append(i)

    def pick(self, target: int) -> int:
        return random.choice(self.idx[target])


def solve(nums: list[int], target: int) -> int:
    return Solution(nums).pick(target)


if __name__ == "__main__":
    nums = read_ints()
    target = read_int()
    write_int(solve(nums, target))
