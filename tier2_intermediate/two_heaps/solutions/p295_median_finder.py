"""P295: Find Median from Data Stream (Hard)

TODO: Implement solve() below.
Hint: Use a max-heap for the lower half and a min-heap for the upper half.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase
import heapq

class Solution(Problem):
    name = "295. Find Median from Data Stream"
    test_cases = [
        TestCase(input=([5,15,1,3], "median"), expected=[5.0, 10.0, 5.0, 4.0], label="stream median"),
        TestCase(input=([1,2], "median"), expected=[1.0, 1.5], label="two elements"),
    ]

    def solve(self, stream: list[int], _unused: str) -> list[float]:
        import heapq
        small: list[int] = []  # max-heap (negated values)
        large: list[int] = []  # min-heap
        medians: list[float] = []

        for num in stream:
            heapq.heappush(small, -num)
            heapq.heappush(large, -heapq.heappop(small))
            if len(large) > len(small):
                heapq.heappush(small, -heapq.heappop(large))

            if len(small) > len(large):
                medians.append(float(-small[0]))
            elif len(large) > len(small):
                medians.append(float(large[0]))
            else:
                medians.append((-small[0] + large[0]) / 2.0)
        return medians

if __name__ == "__main__":
    Solution().run()
