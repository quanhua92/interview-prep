"""P090: Subsets II (Medium)

TODO: Implement solve() below.
Hint: Sort first, then skip duplicates at the same recursion level during backtracking.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase

class Solution(Problem):
    name = "90. Subsets II"
    test_cases = [
        TestCase(input=[1,2,2], expected=[[],[1],[1,2],[1,2,2],[2],[2,2]], label="example 1"),
        TestCase(input=[0], expected=[[],[0]], label="example 2"),
    ]

    def solve(self, nums: list[int]) -> list[list[int]]:
        result: list[list[int]] = []
        nums.sort()

        def backtrack(start: int, current: list[int]):
            result.append(current[:])
            for i in range(start, len(nums)):
                if i > start and nums[i] == nums[i - 1]:
                    continue
                current.append(nums[i])
                backtrack(i + 1, current)
                current.pop()

        backtrack(0, [])
        return result

if __name__ == "__main__":
    Solution().run()
