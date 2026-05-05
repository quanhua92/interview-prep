"""P215: Kth Largest Element in an Array (Medium)

TODO: Implement solve() below.
Hint: Use a min-heap of size k to efficiently find the kth largest element.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase
import heapq

class Solution(Problem):
    name = "215. Kth Largest Element in an Array"
    test_cases = [
        TestCase(input=([3,2,1,5,6,4], 2), expected=5, label="example 1"),
        TestCase(input=([3,2,3,1,2,4,5,5,6], 4), expected=4, label="example 2"),
        TestCase(input=([1], 1), expected=1, label="single element"),
    ]

    def solve(self, nums: list[int], k: int) -> int:
        return heapq.nlargest(k, nums)[-1]

if __name__ == "__main__":
    Solution().run()
