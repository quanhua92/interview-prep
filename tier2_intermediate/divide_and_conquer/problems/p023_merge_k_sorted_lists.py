"""P023: Merge k Sorted Lists (Hard)

TODO: Implement solve() below.
Hint: Use divide & conquer: merge pairs of lists recursively until one remains.
Input is a list of sorted integer lists (simplified from linked lists).
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase

class Solution(Problem):
    name = "23. Merge k Sorted Lists"
    test_cases = [
        TestCase(input=[[1,4,5],[1,3,4],[2,6]], expected=[1,1,2,3,4,4,5,6], label="example 1"),
        TestCase(input=[], expected=[], label="empty input"),
        TestCase(input=[[]], expected=[], label="single empty list"),
        TestCase(input=[[1,2,3]], expected=[1,2,3], label="single list"),
    ]

    def solve(self, lists: list[list[int]]) -> list[int]:
        raise NotImplementedError("TODO: Implement solve(self, lists: list[list[int]]) -> list[int]")

if __name__ == "__main__":
    Solution().run()
