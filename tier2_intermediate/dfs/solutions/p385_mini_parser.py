"""
P385: Mini Parser [PREMIUM] (Medium)
https://leetcode.com/problems/mini-parser/
Topics: String, Stack, Depth-First Search

Given a string s represents the serialization of a nested list, implement a parser to deserialize it and return the deserialized NestedInteger.
Each element is either an integer or a list whose elements may also be integers or other lists.
Example 1:
    Input: s = "324"
    Output: 324
    Explanation: You should return a NestedInteger object which contains a single integer 324.

Example 2:
    Input: s = "[123,[456,[789]]]"
    Output: [123,[456,[789]]]
    Explanation: Return a NestedInteger object containing a nested list with 2 elements:
    1. An integer containing value 123.
    2. A nested list containing two elements:
    i.  An integer containing value 456.
    ii. A nested list with one element:
    a. An integer containing value 789

Constraints:
    - 1 <= s.length <= 5 * 10^4
    - s consists of digits, square brackets "[]", negative sign '-', and commas ','.
    - s is the serialization of valid NestedInteger.
    - All the values in the input are in the range [-10^6, 10^6].

Template (python3):
    # '''
    # This is the interface that allows for creating nested lists.
    # You should not implement it, or speculate about its implementation
    # '''
    #class NestedInteger:
    #    def __init__(self, value=None):
    #        '''
    #        If value is not specified, initializes an empty list.
    #        Otherwise initializes a single integer equal to value.
    #        '''
    #
    #    def isInteger(self):
    #        '''
    #        @return True if this NestedInteger holds a single integer, rather than a nested list.
    #        :rtype bool
    #        '''
    #
    #    def add(self, elem):
    #        '''
    #        Set this NestedInteger to hold a nested list and adds a nested integer elem to it.
    #        :rtype void
    #        '''
    #
    #    def setInteger(self, value):
    #        '''
    #        Set this NestedInteger to hold a single integer equal to value.
    #        :rtype void
    #        '''
    #
    #    def getInteger(self):
    #        '''
    #        @return the single integer that this NestedInteger holds, if it holds a single integer
    #        Return None if this NestedInteger holds a nested list
    #        :rtype int
    #        '''
    #
    #    def getList(self):
    #        '''
    #        @return the nested list that this NestedInteger holds, if it holds a nested list
    #        Return None if this NestedInteger holds a single integer
    #        :rtype List[NestedInteger]
    #        '''

    class Solution:
        def deserialize(self, s: str) -> NestedInteger:
"""

import json

from src.wasm_libs.py.io import read_line, write_string


class NestedInteger:
    def __init__(self, value=None):
        if value is None:
            self._list: list[NestedInteger] = []
        else:
            self._integer: int = value
            self._list = None

    def isInteger(self) -> bool:
        return self._list is None

    def add(self, elem: "NestedInteger"):
        self._list.append(elem)

    def _to_python(self):
        if self.isInteger():
            return self.getInteger()
        return [item._to_python() for item in self.getList()]

    def getInteger(self) -> int | None:
        return self._integer if self._list is None else None

    def getList(self) -> list["NestedInteger"] | None:
        return self._list if self._list is not None else None


def _deserialize(s: str) -> NestedInteger:
    if not s.startswith("["):
        return NestedInteger(int(s))
    stack: list[NestedInteger] = []
    current = NestedInteger()
    i = 0
    while i < len(s):
        if s[i] == "[":
            new_ni = NestedInteger()
            if stack:
                stack[-1].add(new_ni)
            stack.append(new_ni)
            current = new_ni
            i += 1
        elif s[i] == "]":
            finished = stack.pop()
            current = finished
            i += 1
        elif s[i] == ",":
            i += 1
        else:
            j = i
            while j < len(s) and (s[j].isdigit() or s[j] == "-"):
                j += 1
            num = NestedInteger(int(s[i:j]))
            if stack:
                stack[-1].add(num)
            else:
                current = num
            i = j
    return current


def solve(s: str) -> str:
    result = _deserialize(s)
    if result.isInteger():
        return str(result.getInteger())
    else:
        return json.dumps(result._to_python())


if __name__ == "__main__":
    s = read_line()
    result = solve(s)
    write_string(result)
