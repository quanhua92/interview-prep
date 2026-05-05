"""P167: Two Sum II - Input Array Is Sorted (Medium)

TODO: Implement solve() below.
Hint: Use two pointers from both ends of the sorted array.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "167. Two Sum II - Input Array Is Sorted"
    test_cases = [
        TestCase(input=([2, 7, 11, 15], 9), expected=[1, 2], label="example 1"),
        TestCase(input=([2, 3, 4], 6), expected=[1, 3], label="example 2"),
        TestCase(input=([-1, 0], -1), expected=[1, 2], label="example 3"),
    ]

    def solve(self, numbers: list[int], target: int) -> list[int]:
        left, right = 0, len(numbers) - 1
        while left < right:
            current = numbers[left] + numbers[right]
            if current == target:
                return [left + 1, right + 1]
            elif current < target:
                left += 1
            else:
                right -= 1
        return []


if __name__ == "__main__":
    Solution().run()
