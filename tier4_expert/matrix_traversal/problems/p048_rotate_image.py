"""P048: Rotate Image (Medium)

TODO: Implement solve() below.
Hint: Transpose the matrix first, then reverse each row.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase

class Solution(Problem):
    name = "48. Rotate Image"
    test_cases = [
        TestCase(
            input=[[1,2,3],[4,5,6],[7,8,9]],
            expected=[[7,4,1],[8,5,2],[9,6,3]],
            label="example 1"
        ),
        TestCase(
            input=[[5,1,9,11],[2,4,8,10],[13,3,6,7],[15,14,12,16]],
            expected=[[15,13,2,5],[14,3,4,1],[12,6,8,9],[16,7,10,11]],
            label="example 2"
        ),
    ]

    def solve(self, matrix: list[list[int]]) -> list[list[int]]:
        raise NotImplementedError("TODO: Implement solve(self, matrix: list[list[int]]) -> list[list[int]]")

if __name__ == "__main__":
    Solution().run()
