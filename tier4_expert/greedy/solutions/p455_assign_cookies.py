"""P455: Assign Cookies (Easy)

TODO: Implement solve() below.
Hint: Sort both arrays and use two pointers to greedily assign the smallest sufficient cookie.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase

class Solution(Problem):
    name = "455. Assign Cookies"
    test_cases = [
        TestCase(input=([1,2,3], [1,1]), expected=1, label="example 1"),
        TestCase(input=([1,2], [1,2,3]), expected=2, label="example 2"),
        TestCase(input=([], [1,2,3]), expected=0, label="no children"),
    ]

    def solve(self, g: list[int], s: list[int]) -> int:
        g.sort()
        s.sort()
        child = cookie = 0
        while child < len(g) and cookie < len(s):
            if s[cookie] >= g[child]:
                child += 1
            cookie += 1
        return child

if __name__ == "__main__":
    Solution().run()
