"""P480: Sliding Window Median (Hard)

TODO: Implement solve() below.
Hint: Use a max-heap for the small half and a min-heap for the large half with lazy deletion.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase
import heapq


class Solution(Problem):
    name = "480. Sliding Window Median"
    test_cases = [
        TestCase(input=([1,3,-1,-3,5,3,6,7], 3), expected=[1.0,-1.0,-1.0,3.0,5.0,6.0], label="example 1"),
        TestCase(input=([1,2], 1), expected=[1.0,2.0], label="window size 1"),
    ]

    def solve(self, nums: list[int], k: int) -> list[float]:
        # small is a max-heap (negated values), large is a min-heap
        small: list[tuple[int, int]] = []  # (-value, index)
        large: list[tuple[int, int]] = []  # (value, index)
        delayed: dict[int, int] = {}  # index -> count of lazy deletions
        small_size = 0  # effective size of small (excluding delayed)
        large_size = 0  # effective size of large (excluding delayed)

        def prune(heap: list[tuple[int, int]]) -> None:
            """Remove top elements that are marked for lazy deletion."""
            while heap:
                _, idx = heap[0]
                if idx in delayed:
                    delayed[idx] -= 1
                    if delayed[idx] == 0:
                        del delayed[idx]
                    heapq.heappop(heap)
                else:
                    break

        def make_balanced() -> None:
            """Rebalance: small_size == large_size or small_size+1 == large_size."""
            nonlocal small_size, large_size
            if small_size > large_size + 1:
                val, idx = heapq.heappop(small)
                heapq.heappush(large, (-val, idx))
                small_size -= 1
                large_size += 1
                prune(small)
            elif small_size < large_size:
                val, idx = heapq.heappop(large)
                heapq.heappush(small, (-val, idx))
                large_size -= 1
                small_size += 1
                prune(large)

        def get_median() -> float:
            if k % 2 == 1:
                return float(-small[0][0])
            else:
                return (-small[0][0] + large[0][0]) / 2.0

        result: list[float] = []

        for i in range(len(nums)):
            # Add nums[i]
            if not small or nums[i] <= -small[0][0]:
                heapq.heappush(small, (-nums[i], i))
                small_size += 1
            else:
                heapq.heappush(large, (nums[i], i))
                large_size += 1

            # Balance
            make_balanced()

            # Remove element leaving the window
            if i >= k:
                out_idx = i - k
                out_val = nums[out_idx]
                delayed[out_idx] = delayed.get(out_idx, 0) + 1
                if out_val <= -small[0][0]:
                    small_size -= 1
                    # Prune small if the top is delayed
                    if small and small[0][1] == out_idx:
                        prune(small)
                else:
                    large_size -= 1
                    # Prune large if the top is delayed
                    if large and large[0][1] == out_idx:
                        prune(large)
                # Rebalance after removal
                make_balanced()

            # Record median
            if i >= k - 1:
                result.append(get_median())

        return result


if __name__ == "__main__":
    Solution().run()
