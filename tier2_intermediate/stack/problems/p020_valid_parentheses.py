"""P020: Valid Parentheses (Easy)

TODO: Implement solve() below.
Hint: Use a stack to match opening and closing brackets.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase

class Solution(Problem):
    name = "20. Valid Parentheses"
    test_cases = [
        TestCase(input="()", expected=True, label="simple pair"),
        TestCase(input="()[]{}", expected=True, label="mixed brackets"),
        TestCase(input="(]", expected=False, label="mismatched"),
        TestCase(input="([)]", expected=False, label="interleaved"),
        TestCase(input="{[]}", expected=True, label="nested"),
    ]

    def solve(self, s: str) -> bool:
        raise NotImplementedError("TODO: Implement solve(self, s: str) -> bool")

if __name__ == "__main__":
    Solution().run()
