"""P141: Linked List Cycle (Easy)

TODO: Implement solve() below.
Hint: Use Floyd's cycle-finding algorithm with fast and slow pointers.
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase, ListNode


class Solution(Problem):
    name = "141. Linked List Cycle"
    test_cases = [
        TestCase(input=(ListNode.from_list([3, 2, 0, -4]), 1), expected=True, label="example 1"),
        TestCase(input=(ListNode.from_list([1, 2]), 0), expected=True, label="example 2"),
        TestCase(input=(ListNode.from_list([1]), -1), expected=False, label="example 3"),
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
