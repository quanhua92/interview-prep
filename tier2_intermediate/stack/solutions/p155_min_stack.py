"""P155: Min Stack (Medium)

TODO: Implement solve() below.
Hint: The solve method receives a list of operations and returns a list of outputs.
Operations: ["MinStack","push","push","push","getMin","pop","top","getMin"]
Values follow operations that take arguments.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase

class Solution(Problem):
    name = "155. Min Stack"
    test_cases = [
        TestCase(
            input=[
                ["MinStack","push","push","push","getMin","pop","top","getMin"],
                [[],[5],[-2],[3],[],[],[],[]],
            ],
            expected=[None,None,None,None,-2,None,-2,-2],
            label="example 1",
        ),
        TestCase(
            input=[
                ["MinStack","push","push","getMin","getMin","push","getMin","top","getMin","pop","getMin"],
                [[],[0],[1],[],[],[-3],[],[],[],[],[]],
            ],
            expected=[None,None,None,0,0,None,-3,-3,-3,None,0],
            label="negative values",
        ),
    ]

    def solve(self, ops: list[str], values: list[list[int]]) -> list[int | None]:
        stack: list[int] = []
        min_stack: list[int] = []
        result: list[int | None] = []

        for op, val in zip(ops, values):
            if op == "MinStack":
                result.append(None)
            elif op == "push":
                stack.append(val[0])
                min_val = val[0] if not min_stack else min(val[0], min_stack[-1])
                min_stack.append(min_val)
                result.append(None)
            elif op == "pop":
                stack.pop()
                min_stack.pop()
                result.append(None)
            elif op == "top":
                result.append(stack[-1])
            elif op == "getMin":
                result.append(min_stack[-1])

        return result

if __name__ == "__main__":
    Solution().run()
