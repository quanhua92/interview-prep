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

Constraints:
    - -2^31 <= val <= 2^31 - 1
    - Methods pop, top and getMin operations will always be called on non-empty stacks.
    - At most 3 * 10^4 calls will be made to push, pop, top, and getMin.

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

from src.wasm_libs.py.io import *


def solve(ops: list[str], values: list[list[int]]) -> list[int | None]:
    raise NotImplementedError


if __name__ == "__main__":
    n = read_int()
    ops: list[str] = []
    values: list[list[int]] = []
    for _ in range(n):
        op = read_line()
        ops.append(op)
        count = read_int()
        if count > 0:
            values.append(read_ints())
        else:
            values.append([])
    results = solve(ops, values)
    for r in results:
        if r is None:
            write_string("null")
        else:
            write_int(r)
