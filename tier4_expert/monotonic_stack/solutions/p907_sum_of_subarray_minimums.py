"""P907: Sum of Subarray Minimums (Medium)

TODO: Implement solve() below.
Hint: Use a monotonic stack to find the number of subarrays where each element is the minimum.
For each element, find the previous smaller and next smaller element boundaries.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase

class Solution(Problem):
    name = "907. Sum of Subarray Minimums"
    test_cases = [
        TestCase(input=[3,1,2,4], expected=17, label="example 1"),
        TestCase(input=[11,81,94,43,3], expected=444, label="example 2"),
        TestCase(input=[1], expected=1, label="single element"),
    ]

    def solve(self, arr: list[int]) -> int:
        MOD = 10**9 + 7
        n = len(arr)
        left: list[int] = [-1] * n  # previous smaller element index
        right: list[int] = [n] * n  # next smaller or equal element index

        stack: list[int] = []
        for i in range(n):
            while stack and arr[stack[-1]] >= arr[i]:
                stack.pop()
            left[i] = stack[-1] if stack else -1
            stack.append(i)

        stack.clear()
        for i in range(n - 1, -1, -1):
            while stack and arr[stack[-1]] > arr[i]:
                stack.pop()
            right[i] = stack[-1] if stack else n
            stack.append(i)

        total = 0
        for i in range(n):
            count_left = i - left[i]
            count_right = right[i] - i
            total = (total + arr[i] * count_left * count_right) % MOD

        return total

if __name__ == "__main__":
    Solution().run()
