"""P278: First Bad Version (Easy)

TODO: Implement solve() below.
Hint: Binary search for the leftmost version where is_bad is True.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "278. First Bad Version"
    test_cases = [
        TestCase(input=(5, 4), expected=4, label="example 1"),
        TestCase(input=(1, 1), expected=1, label="single version, bad"),
        TestCase(input=(3, 3), expected=3, label="last version is bad"),
        TestCase(input=(10, 7), expected=7, label="middle version is bad"),
    ]

    def solve(self, n: int, bad: int) -> int:
        is_bad = lambda v: v >= bad
        left, right = 1, n
        while left < right:
            mid = (left + right) // 2
            if is_bad(mid):
                right = mid
            else:
                left = mid + 1
        return left


if __name__ == "__main__":
    Solution().run()
