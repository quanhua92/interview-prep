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
        class MinStack:
            def __init__(self):
                self._stack: list[int] = []
                self._min_stack: list[int] = []

            def push(self, val: int) -> None:
                self._stack.append(val)
                min_val = val if not self._min_stack else min(val, self._min_stack[-1])
                self._min_stack.append(min_val)

            def pop(self) -> None:
                self._stack.pop()
                self._min_stack.pop()

            def top(self) -> int:
                return self._stack[-1]

            def get_min(self) -> int:
                return self._min_stack[-1]

        raise NotImplementedError("TODO: Implement solve(self, ops, values) -> list")
        # Hint: instantiate MinStack, iterate ops, collect return values for
        # getMin, top operations. Return the collected list.

if __name__ == "__main__":
    Solution().run()
