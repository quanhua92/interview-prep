"""P202: Happy Number (Easy)

TODO: Implement solve() below.
Hint: Use fast and slow pointers on the sequence of sum-of-squared-digits.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "202. Happy Number"
    test_cases = [
        TestCase(input=19, expected=True, label="example 1"),
        TestCase(input=2, expected=False, label="example 2"),
        TestCase(input=1, expected=True, label="already happy"),
    ]

    def solve(self, n: int) -> bool:
        def get_next(num: int) -> int:
            total = 0
            while num > 0:
                digit = num % 10
                total += digit * digit
                num //= 10
            return total

        slow, fast = n, get_next(n)
        while fast != 1 and slow != fast:
            slow = get_next(slow)
            fast = get_next(get_next(fast))
        return fast == 1


if __name__ == "__main__":
    Solution().run()
