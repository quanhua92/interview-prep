"""P023: Merge k Sorted Lists (Hard)

TODO: Implement solve() below.
Hint: Use divide & conquer: merge pairs of lists recursively until one remains.
Input is a list of sorted integer lists (simplified from linked lists).
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase

class Solution(Problem):
    name = "23. Merge k Sorted Lists"
    test_cases = [
        TestCase(input=[[1,4,5],[1,3,4],[2,6]], expected=[1,1,2,3,4,4,5,6], label="example 1"),
        TestCase(input=[], expected=[], label="empty input"),
        TestCase(input=[[]], expected=[], label="single empty list"),
        TestCase(input=[[1,2,3]], expected=[1,2,3], label="single list"),
    ]

    def solve(self, lists: list[list[int]]) -> list[int]:
        if not lists:
            return []
        if len(lists) == 1:
            return lists[0][:]

        mid = len(lists) // 2
        left = self.solve(lists[:mid])
        right = self.solve(lists[mid:])

        # Merge two sorted lists
        result: list[int] = []
        i = j = 0
        while i < len(left) and j < len(right):
            if left[i] <= right[j]:
                result.append(left[i])
                i += 1
            else:
                result.append(right[j])
                j += 1
        result.extend(left[i:])
        result.extend(right[j:])
        return result

if __name__ == "__main__":
    Solution().run()
