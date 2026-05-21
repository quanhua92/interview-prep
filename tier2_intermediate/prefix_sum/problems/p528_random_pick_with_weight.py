"""
P528: Random Pick with Weight [PREMIUM] (Medium)
https://leetcode.com/problems/random-pick-with-weight/
Topics: Array, Math, Binary Search, Prefix Sum, Randomized

You are given a 0-indexed array of positive integers w where w[i] describes the weight of the ith index.
You need to implement the function pickIndex(), which randomly picks an index in the range [0, w.length - 1] (inclusive) and returns it. The probability of picking an index i is w[i] / sum(w).
Example 2:
    Input
Example 1:
    ["Solution","pickIndex"]
    [[[1]],[]]
    Output
    [null,0]

    Explanation
    Solution solution = new Solution([1]);
    solution.pickIndex(); // return 0. The only option is to return 0 since there is only one element in w.

    Input
Example 2:
    ["Solution","pickIndex","pickIndex","pickIndex","pickIndex","pickIndex"]
    [[[1,3]],[],[],[],[],[]]
    Output
    [null,1,1,1,1,0]

    Explanation
    Solution solution = new Solution([1, 3]);
    solution.pickIndex(); // return 1. It is returning the second element (index = 1) that has a probability of 3/4.
    solution.pickIndex(); // return 1
    solution.pickIndex(); // return 1
    solution.pickIndex(); // return 1
    solution.pickIndex(); // return 0. It is returning the first element (index = 0) that has a probability of 1/4.

    Since this is a randomization problem, multiple answers are allowed.
    All of the following outputs can be considered correct:
    [null,1,1,1,1,0]
    [null,1,1,1,1,1]
    [null,1,1,1,0,0]
    [null,1,1,1,0,1]
    [null,1,0,1,0,0]
    ......
    and so on.

Constraints:
    - 1 <= w.length <= 104
    - 1 <= w[i] <= 105
    - pickIndex will be called at most 104 times.

Template (python3):
    class Solution:

        def __init__(self, w: List[int]):


        def pickIndex(self) -> int:



    # Your Solution object will be instantiated and called as such:
    # obj = Solution(w)
    # param_1 = obj.pickIndex()
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase
from typing import Any


class Solution(Problem):
    name = "528. Random Pick with Weight"
    test_cases = [
        TestCase(
            input=[1],
            expected=[1],
            label="prefix sum for [1]",
        ),
        TestCase(
            input=[1, 3],
            expected=[1, 4],
            label="prefix sum for [1, 3]",
        ),
        TestCase(
            input=[3, 14, 1, 7],
            expected=[3, 17, 18, 25],
            label="prefix sum for [3, 14, 1, 7]",
        ),
    ]

    def solve(self, w: list[int]) -> list[int]:
        raise NotImplementedError("TODO: Implement solve(self, w: list[int]) -> list[int]")


if __name__ == "__main__":
    Solution().run()
