"""P347: Top K Frequent Elements (Medium)

TODO: Implement solve() below.
Hint: Use a frequency counter and a min-heap of size k.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase
from collections import Counter
import heapq

class Solution(Problem):
    name = "347. Top K Frequent Elements"
    test_cases = [
        TestCase(input=([1,1,1,2,2,3], 2), expected=[1,2], label="example 1"),
        TestCase(input=([1], 1), expected=[1], label="example 2"),
    ]

    def solve(self, nums: list[int], k: int) -> list[int]:
        count = Counter(nums)
        return [item for item, _ in heapq.nlargest(k, count.items(), key=lambda x: x[1])]

if __name__ == "__main__":
    Solution().run()
