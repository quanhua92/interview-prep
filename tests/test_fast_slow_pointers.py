"""Tests for tier1_foundation/fast_slow_pointers"""
import sys
sys.path.insert(0, ".")
from tier1_foundation.fast_slow_pointers.solutions.p202_happy_number import Solution as P202
from tier1_foundation.fast_slow_pointers.solutions.p876_middle_of_linked_list import Solution as P876
from src.utils import ListNode


def create_cycle(values, pos):
    """Create a linked list with a cycle at position pos."""
    if not values:
        return None
    head = ListNode.from_list(values)
    if pos < 0:
        return head
    tail = head
    while tail.next:
        tail = tail.next
    cycle_node = head
    for _ in range(pos):
        cycle_node = cycle_node.next
    tail.next = cycle_node
    return head


def has_cycle(head):
    """Detect cycle in linked list using Floyd's algorithm."""
    if not head or not head.next:
        return False
    slow, fast = head, head
    while fast and fast.next:
        slow = slow.next
        fast = fast.next.next
        if slow is fast:
            return True
    return False


class TestP141LinkedListCycle:
    def test_has_cycle(self):
        head = create_cycle([3, 2, 0, -4], 1)
        assert has_cycle(head) is True

    def test_no_cycle(self):
        head = ListNode.from_list([1, 2, 3, 4])
        assert has_cycle(head) is False

    def test_empty(self):
        assert has_cycle(None) is False

    def test_single_node_cycle(self):
        head = ListNode.from_list([1])
        head.next = head
        assert has_cycle(head) is True


class TestP202HappyNumber:
    def test_example1(self): assert P202().solve(19) == True
    def test_example2(self): assert P202().solve(2) == False
    def test_already_happy(self): assert P202().solve(1) == True

class TestP876MiddleOfLinkedList:
    def test_odd_length(self):
        head = ListNode.from_list([1,2,3,4,5])
        assert P876().solve(head) == [3,4,5]
    def test_even_length(self):
        head = ListNode.from_list([1,2,3,4,5,6])
        assert P876().solve(head) == [4,5,6]
    def test_single(self):
        head = ListNode.from_list([1])
        assert P876().solve(head) == [1]
