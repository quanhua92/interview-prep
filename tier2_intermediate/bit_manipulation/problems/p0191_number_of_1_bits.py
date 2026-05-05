"""P0191: Number of 1 Bits (Easy)

TODO: Implement solve() below.
Hint: Use Brian Kernighan's algorithm: n &= (n - 1) clears the lowest set bit.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase

class Solution(Problem):
    name = "191. Number of 1 Bits"
    test_cases = [
        TestCase(input=0b00000000000000000000000000001011, expected=3, label="example 1"),
        TestCase(input=0b00000000000000000000000010000000, expected=1, label="power of two"),
        TestCase(input=0b11111111111111111111111111111101, expected=31, label="all but one"),
        TestCase(input=0, expected=0, label="zero"),
    ]

    def solve(self, n: int) -> int:
        raise NotImplementedError("TODO: Implement solve(self, n: int) -> int")

if __name__ == "__main__":
    Solution().run()
