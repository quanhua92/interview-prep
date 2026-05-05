"""P078: Subsets (Medium)

TODO: Implement solve() below.
Hint: Use backtracking to generate all possible subsets by including/excluding each element.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase

class Solution(Problem):
    name = "78. Subsets"
    test_cases = [
        TestCase(input=[1,2,3], expected=[[],[1],[1,2],[1,2,3],[1,3],[2],[2,3],[3]], label="example 1"),
        TestCase(input=[0], expected=[[],[0]], label="example 2"),
    ]

    def solve(self, nums: list[int]) -> list[list[int]]:
        result: list[list[int]] = []

        def backtrack(start: int, current: list[int]):
            result.append(current[:])
            for i in range(start, len(nums)):
                current.append(nums[i])
                backtrack(i + 1, current)
                current.pop()

        backtrack(0, [])
        return result

if __name__ == "__main__":
    Solution().run()
