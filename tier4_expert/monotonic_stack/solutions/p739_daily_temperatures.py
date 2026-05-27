"""
P739: Daily Temperatures (Medium)
https://leetcode.com/problems/daily-temperatures/
Topics: Array, Stack, Monotonic Stack

Given an array of integers temperatures represents the daily temperatures, return an array answer such that answer[i] is the number of days you have to wait after the ith day to get a warmer temperature. If there is no future day for which this is possible, keep answer[i] == 0 instead.

Example 1:
    Input: temperatures = [73,74,75,71,69,72,76,73]
    Output: [1,1,4,2,1,1,0,0]

Example 2:
    Input: temperatures = [30,40,50,60]
    Output: [1,1,1,0]

Example 3:
    Input: temperatures = [30,60,90]
    Output: [1,1,0]

Constraints:
    - 1 <= temperatures.length <= 105
    - 30 <= temperatures[i] <= 100

Hints:
    - If the temperature is say, 70 today, then in the future a warmer temperature must be either 71, 72, 73, ..., 99, or 100.  We could remember when all of them occur next.

Template (python3):
    class Solution:
        def dailyTemperatures(self, temperatures: List[int]) -> List[int]:

Hint: Use a monotonic decreasing stack to track indices of warmer days.
"""

from src.wasm_libs.py.io import *


def solve(temperatures: list[int]) -> list[int]:
    n = len(temperatures)
    answer = [0] * n
    stack: list[int] = []
    for i in range(n):
        while stack and temperatures[i] > temperatures[stack[-1]]:
            j = stack.pop()
            answer[j] = i - j
        stack.append(i)
    return answer


if __name__ == "__main__":
    temperatures = read_ints()
    result = solve(temperatures)
    write_ints(result)
