"""P1306: Jump Game III (Medium)

TODO: Implement solve() below.
Hint: DFS with a visited set; explore start+arr[start] and start-arr[start], checking bounds and visited.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "1306. Jump Game III"
    test_cases = [
        TestCase(input=([4,2,3,0,3,1,2], 5), expected=True, label="example 1"),
        TestCase(input=([4,2,3,0,3,1,2], 0), expected=True, label="start at index 0"),
        TestCase(input=([3,0,2,1,2], 2), expected=False, label="cannot reach zero"),
    ]

    def solve(self, arr: list[int], start: int) -> bool:
        n = len(arr)
        visited: set[int] = set()

        def dfs(i: int) -> bool:
            if i < 0 or i >= n or i in visited:
                return False
            if arr[i] == 0:
                return True
            visited.add(i)
            jump = arr[i]
            return dfs(i + jump) or dfs(i - jump)

        return dfs(start)


if __name__ == "__main__":
    Solution().run()
