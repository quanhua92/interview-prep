"""P0560: Subarray Sum Equals K (Medium)

TODO: Implement solve() below.
Hint: Use a hash map with prefix sums to count subarrays summing to k.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase
from collections import defaultdict

class Solution(Problem):
    name = "560. Subarray Sum Equals K"
    test_cases = [
        TestCase(input=([1,1,1], 2), expected=2, label="example 1"),
        TestCase(input=([1,2,3], 3), expected=2, label="example 2"),
        TestCase(input=([], 0), expected=0, label="empty array"),
    ]

    def solve(self, nums: list[int], k: int) -> int:
        count = 0
        curr_sum = 0
        prefix_freq: dict[int, int] = defaultdict(int)
        prefix_freq[0] = 1

        for num in nums:
            curr_sum += num
            count += prefix_freq.get(curr_sum - k, 0)
            prefix_freq[curr_sum] += 1

        return count

if __name__ == "__main__":
    Solution().run()
