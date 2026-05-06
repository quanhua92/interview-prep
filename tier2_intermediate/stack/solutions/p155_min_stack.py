"""
P155: Min Stack (Medium)
https://leetcode.com/problems/min-stack/
Topics: Stack, Design

Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.
Implement the MinStack class:
You must implement a solution with O(1) time complexity for each function.

Example 1:
    Input
    ["MinStack","push","push","push","getMin","pop","top","getMin"]
    [[],[-2],[0],[-3],[],[],[],[]]

    Output
    [null,null,null,null,-3,null,0,-2]

    Explanation
    MinStack minStack = new MinStack();
    minStack.push(-2);
    minStack.push(0);
    minStack.push(-3);
    minStack.getMin(); // return -3
    minStack.pop();
    minStack.top();    // return 0
    minStack.getMin(); // return -2

Constraints:
    - -231 <= val <= 231 - 1
    - Methods pop, top and getMin operations will always be called on non-empty stacks.
    - At most 3 * 104 calls will be made to push, pop, top, and getMin.

Hints:
    - Consider each node in the stack having a minimum value. (Credits to @aakarshmadhavan)

Template (python3):
    class MinStack:

        def __init__(self):


        def push(self, val: int) -> None:


        def pop(self) -> None:


        def top(self) -> int:


        def getMin(self) -> int:



    # Your MinStack object will be instantiated and called as such:
    # obj = MinStack()
    # obj.push(val)
    # obj.pop()
    # param_3 = obj.top()
    # param_4 = obj.getMin()

Hint: The solve method receives a list of operations and returns a list of outputs.
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "155. Min Stack"
    test_cases = [
        TestCase(
            input=[
                ["MinStack", "push", "push", "push", "getMin", "pop", "top", "getMin"],
                [[], [5], [-2], [3], [], [], [], []],
            ],
            expected=[None, None, None, None, -2, None, -2, -2],
            label="example 1",
        ),
        TestCase(
            input=[
                [
                    "MinStack",
                    "push",
                    "push",
                    "getMin",
                    "getMin",
                    "push",
                    "getMin",
                    "top",
                    "getMin",
                    "pop",
                    "getMin",
                ],
                [[], [0], [1], [], [], [-3], [], [], [], [], []],
            ],
            expected=[None, None, None, 0, 0, None, -3, -3, -3, None, 0],
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
