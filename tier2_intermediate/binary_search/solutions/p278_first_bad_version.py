"""
P278: First Bad Version (Easy)
https://leetcode.com/problems/first-bad-version/
Topics: Binary Search, Interactive

You are a product manager and currently leading a team to develop a new product. Unfortunately, the latest version of your product fails the quality check. Since each version is developed based on the previous version, all the versions after a bad version are also bad.
Suppose you have n versions [1, 2, ..., n] and you want to find out the first bad one, which causes all the following ones to be bad.
You are given an API bool isBadVersion(version) which returns whether version is bad. Implement a function to find the first bad version. You should minimize the number of calls to the API.

Example 1:
    Input: n = 5, bad = 4
    Output: 4
    Explanation:
    call isBadVersion(3) -> false
    call isBadVersion(5) -> true
    call isBadVersion(4) -> true
    Then 4 is the first bad version.

Example 2:
    Input: n = 1, bad = 1
    Output: 1

Constraints:
    - 1 <= bad <= n <= 231 - 1

Template (python3):
    # The isBadVersion API is already defined for you.
    # def isBadVersion(version: int) -> bool:

    class Solution:
        def firstBadVersion(self, n: int) -> int:

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
        def is_bad(v: int) -> bool:
            return v >= bad

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
