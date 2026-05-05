"""P876: Middle of the Linked List (Easy)

TODO: Implement solve() below.
Hint: Fast pointer moves 2 steps, slow moves 1, return slow.to_list().
"""
import sys
sys.path.insert(0, ".")
from src.utils import Problem, TestCase, ListNode


class Solution(Problem):
    name = "876. Middle of the Linked List"
    test_cases = [
        TestCase(input=(ListNode.from_list([1, 2, 3, 4, 5]),), expected=[3, 4, 5], label="odd length"),
        TestCase(input=(ListNode.from_list([1, 2, 3, 4, 5, 6]),), expected=[4, 5, 6], label="even length"),
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
