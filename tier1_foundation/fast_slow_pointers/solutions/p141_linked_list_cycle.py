"""
P141: Linked List Cycle (Easy)
https://leetcode.com/problems/linked-list-cycle/
Topics: Hash Table, Linked List, Two Pointers

Given head, the head of a linked list, determine if the linked list has a cycle in it.
There is a cycle in a linked list if there is some node in the list that can be reached again by continuously following the next pointer. Internally, pos is used to denote the index of the node that tail's next pointer is connected to. Note that pos is not passed as a parameter.
Return true if there is a cycle in the linked list. Otherwise, return false.

Example 1:
    Input: head = [3,2,0,-4], pos = 1
    Output: true
    Explanation: There is a cycle in the linked list, where the tail connects to the 1st node (0-indexed).

Example 2:
    Input: head = [1,2], pos = 0
    Output: true
    Explanation: There is a cycle in the linked list, where the tail connects to the 0th node.

Example 3:
    Input: head = [1], pos = -1
    Output: false
    Explanation: There is no cycle in the linked list.

Constraints:
    - The number of the nodes in the list is in the range [0, 104].
    - -105 <= Node.val <= 105
    - pos is -1 or a valid index in the linked-list.

Follow up:
    - Can you solve it using O(1) (i.e. constant) memory?

Template (python3):
    # Definition for singly-linked list.
    # class ListNode:
    #     def __init__(self, x):
    #         self.val = x
    #         self.next = None

    class Solution:
        def hasCycle(self, head: Optional[ListNode]) -> bool:

Hint: Use Floyd's cycle-finding algorithm with fast and slow pointers.
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase, ListNode


class Solution(Problem):
    name = "141. Linked List Cycle"
    test_cases = [
        TestCase(
            input=(ListNode.from_list([3, 2, 0, -4]), 1),
            expected=True,
            label="example 1",
        ),
        TestCase(
            input=(ListNode.from_list([1, 2]), 0), expected=True, label="example 2"
        ),
        TestCase(
            input=(ListNode.from_list([1]), -1), expected=False, label="example 3"
        ),
    ]

    def solve(self, head: ListNode | None, pos: int) -> bool:
        if not head or not head.next:
            return False
        # Create cycle if pos >= 0
        if pos >= 0:
            tail = head
            while tail.next:
                tail = tail.next
            cycle_node = head
            for _ in range(pos):
                cycle_node = cycle_node.next
            tail.next = cycle_node
        slow, fast = head, head
        while fast and fast.next:
            slow = slow.next  # type: ignore[union-attr]
            fast = fast.next.next  # type: ignore[union-attr]
            if slow is fast:
                return True
        return False


if __name__ == "__main__":
    Solution().run()
