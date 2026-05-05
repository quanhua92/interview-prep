"""P084: Largest Rectangle in Histogram (Hard)

TODO: Implement solve() below.
Hint: Use a monotonic increasing stack with a sentinel to compute max rectangle area.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase

class Solution(Problem):
    name = "84. Largest Rectangle in Histogram"
    test_cases = [
        TestCase(input=[2,1,5,6,2,3], expected=10, label="example 1"),
        TestCase(input=[2,4], expected=4, label="example 2"),
    ]

    def solve(self, heights: list[int]) -> int:
        stack: list[int] = []  # indices, heights[stack] is increasing
        max_area = 0
        # Add sentinel
        heights.append(0)
        for i, h in enumerate(heights):
            while stack and h < heights[stack[-1]]:
                height = heights[stack.pop()]
                width = i if not stack else i - stack[-1] - 1
                max_area = max(max_area, height * width)
            stack.append(i)
        heights.pop()
        return max_area

if __name__ == "__main__":
    Solution().run()
