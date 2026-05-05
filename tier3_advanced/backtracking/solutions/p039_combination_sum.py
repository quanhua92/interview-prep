"""P039: Combination Sum (Medium)

TODO: Implement solve() below.
Hint: Use backtracking with early pruning when the remaining sum goes negative.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase

class Solution(Problem):
    name = "39. Combination Sum"
    test_cases = [
        TestCase(input=([2,3,6,7], 7), expected=[[2,2,3],[7]], label="example 1"),
        TestCase(input=([2,3,5], 8), expected=[[2,2,2,2],[2,3,3],[3,5]], label="example 2"),
        TestCase(input=([2], 1), expected=[], label="no solution"),
    ]

    def solve(self, candidates: list[int], target: int) -> list[list[int]]:
        result: list[list[int]] = []
        candidates.sort()

        def backtrack(start: int, remaining: int, current: list[int]):
            if remaining == 0:
                result.append(current[:])
                return
            for i in range(start, len(candidates)):
                if candidates[i] > remaining:
                    break
                current.append(candidates[i])
                backtrack(i, remaining - candidates[i], current)
                current.pop()

        backtrack(0, target, [])
        return result

if __name__ == "__main__":
    Solution().run()
