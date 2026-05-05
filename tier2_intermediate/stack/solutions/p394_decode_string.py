"""P394: Decode String (Medium)

TODO: Implement solve() below.
Hint: Use a stack to handle nested k[encoded] patterns.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase

class Solution(Problem):
    name = "394. Decode String"
    test_cases = [
        TestCase(input="3[a]2[bc]", expected="aaabcbc", label="example 1"),
        TestCase(input="3[a2[c]]", expected="accaccacc", label="nested"),
        TestCase(input="2[abc]3[cd]ef", expected="abcabccdcdcdef", label="multiple segments"),
        TestCase(input="abc", expected="abc", label="no encoding"),
    ]

    def solve(self, s: str) -> str:
        stack: list[tuple[int, str]] = []
        curr_num = 0
        curr_str = ""

        for ch in s:
            if ch.isdigit():
                curr_num = curr_num * 10 + int(ch)
            elif ch == "[":
                stack.append((curr_num, curr_str))
                curr_num = 0
                curr_str = ""
            elif ch == "]":
                repeat, prefix = stack.pop()
                curr_str = prefix + curr_str * repeat
            else:
                curr_str += ch

        return curr_str

if __name__ == "__main__":
    Solution().run()
