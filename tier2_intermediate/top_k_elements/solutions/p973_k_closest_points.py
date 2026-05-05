"""P973: K Closest Points to Origin (Medium)

TODO: Implement solve() below.
Hint: Use a max-heap of size k keyed by negative distance squared.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase
import heapq


class Solution(Problem):
    name = "973. K Closest Points to Origin"
    test_cases = [
        TestCase(input=([[1,3],[-2,2]], 1), expected=[[-2,2]], label="example 1"),
        TestCase(input=([[3,3],[5,-1],[-2,4]], 2), expected=[[-2,4],[3,3]], label="example 2 (sorted)"),
    ]

    def solve(self, points: list[list[int]], k: int) -> list[list[int]]:
        heap: list[tuple[int, list[int]]] = []
        for p in points:
            dist = -(p[0] * p[0] + p[1] * p[1])
            heapq.heappush(heap, (dist, p))
            if len(heap) > k:
                heapq.heappop(heap)
        result = sorted([p for _, p in heap])
        return result


if __name__ == "__main__":
    Solution().run()
