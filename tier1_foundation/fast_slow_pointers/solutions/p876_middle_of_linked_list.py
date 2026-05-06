"""
P876: Middle of the Linked List (Easy)
https://leetcode.com/problems/middle-of-the-linked-list/
Topics: Linked List, Two Pointers

Given the head of a singly linked list, return the middle node of the linked list.
If there are two middle nodes, return the second middle node.

Example 1:
    Input: head = [1,2,3,4,5]
    Output: [3,4,5]
    Explanation: The middle node of the list is node 3.

Example 2:
    Input: head = [1,2,3,4,5,6]
    Output: [4,5,6]
    Explanation: Since the list has two middle nodes with values 3 and 4, we return the second one.

Constraints:
    - The number of nodes in the list is in the range [1, 100].
    - 1 <= Node.val <= 100

Template (python3):
    # Definition for singly-linked list.
    # class ListNode:
    #     def __init__(self, val=0, next=None):
    #         self.val = val
    #         self.next = next
    class Solution:
        def middleNode(self, head: Optional[ListNode]) -> Optional[ListNode]:

Hint: Fast pointer moves 2 steps, slow moves 1, return slow.to_list().
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase, ListNode


class Solution(Problem):
    name = "876. Middle of the Linked List"
    test_cases = [
        TestCase(
            input=(ListNode.from_list([1, 2, 3, 4, 5]),),
            expected=[3, 4, 5],
            label="odd length",
        ),
        TestCase(
            input=(ListNode.from_list([1, 2, 3, 4, 5, 6]),),
            expected=[4, 5, 6],
            label="even length",
        ),
        TestCase(input=(ListNode.from_list([1]),), expected=[1], label="single node"),
    ]

    def solve(self, head: ListNode | None) -> list[int]:
        slow, fast = head, head
        while fast and fast.next:
            slow = slow.next  # type: ignore[union-attr]
            fast = fast.next.next
        return slow.to_list()  # type: ignore[union-attr]


if __name__ == "__main__":
    Solution().run()
