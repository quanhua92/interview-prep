"""
P23: Merge k Sorted Lists (Hard)
https://leetcode.com/problems/merge-k-sorted-lists/
Topics: Linked List, Divide and Conquer, Heap (Priority Queue), Merge Sort

You are given an array of k linked-lists lists, each linked-list is sorted in ascending order.
Merge all the linked-lists into one sorted linked-list and return it.

Example 1:
    Input: lists = [[1,4,5],[1,3,4],[2,6]]
    Output: [1,1,2,3,4,4,5,6]
    Explanation: The linked-lists are:
    [
      1->4->5,
      1->3->4,
      2->6
    ]
    merging them into one sorted linked list:
    1->1->2->3->4->4->5->6

Example 2:
    Input: lists = []
    Output: []

Example 3:
    Input: lists = [[]]
    Output: []

Constraints:
    - k == lists.length
    - 0 <= k <= 104
    - 0 <= lists[i].length <= 500
    - -104 <= lists[i][j] <= 104
    - lists[i] is sorted in ascending order.
    - The sum of lists[i].length will not exceed 104.

Template (python3):
    # Definition for singly-linked list.
    # class ListNode:
    #     def __init__(self, val=0, next=None):
    #         self.val = val
    #         self.next = next
    class Solution:
        def mergeKLists(self, lists: List[Optional[ListNode]]) -> Optional[ListNode]:

Hint: Use divide & conquer: merge pairs of lists recursively until one remains.
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "23. Merge k Sorted Lists"
    test_cases = [
        TestCase(
            input=[[1, 4, 5], [1, 3, 4], [2, 6]],
            expected=[1, 1, 2, 3, 4, 4, 5, 6],
            label="example 1",
        ),
        TestCase(input=[], expected=[], label="empty input"),
        TestCase(input=[[]], expected=[], label="single empty list"),
        TestCase(input=[[1, 2, 3]], expected=[1, 2, 3], label="single list"),
        TestCase(input=[[1, 1], [1, 1], [1, 1]], expected=[1, 1, 1, 1, 1, 1], label="all same values"),
        TestCase(input=[[-5, -3], [-4, -2], [-6, 0]], expected=[-6, -5, -4, -3, -2, 0], label="negative values"),
        TestCase(input=[[1, 3], [2, 4]], expected=[1, 2, 3, 4], label="two lists"),
        TestCase(input=[[], [], [1], [], [2]], expected=[1, 2], label="mixed empty and non-empty"),
    ]

    def solve(self, lists: list[list[int]]) -> list[int]:
        raise NotImplementedError(
            "TODO: Implement solve(self, lists: list[list[int]]) -> list[int]"
        )


if __name__ == "__main__":
    Solution().run()
