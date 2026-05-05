"""P338: Counting Bits (Medium)

TODO: Implement solve() below.
Hint: DP approach: ans[i] = ans[i >> 1] + (i & 1).
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase

class Solution(Problem):
    name = "338. Counting Bits"
    test_cases = [
        TestCase(input=2, expected=[0,1,1], label="example 1"),
        TestCase(input=5, expected=[0,1,1,2,1,2], label="example 2"),
        TestCase(input=0, expected=[0], label="zero"),
        TestCase(input=1, expected=[0,1], label="one"),
    ]

    def solve(self, n: int) -> list[int]:
        ans: list[int] = [0] * (n + 1)
        for i in range(1, n + 1):
            ans[i] = ans[i >> 1] + (i & 1)
        return ans

if __name__ == "__main__":
    Solution().run()
