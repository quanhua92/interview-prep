"""Fast & Slow Pointers pattern templates.

Three common variants of the fast-slow pointer technique:

1. Cycle detection in a linked list: Floyd's tortoise and hare algorithm.
2. Find the middle of a linked list: Slow stops at midpoint when fast reaches end.
3. Happy number: Detect cycles in a sequence of number transformations.
"""


def has_cycle(head) -> bool:
    """Variant 1: Cycle detection in a linked list.

    Use Floyd's algorithm: slow moves 1 step, fast moves 2 steps.
    If they ever meet, there is a cycle. If fast reaches None, there is no cycle.

    Time:  O(n) -- fast pointer traverses at most 2n nodes
    Space: O(1) -- only two pointer references

    Args:
        head: Head node of a linked list (must have .next attribute).

    Returns:
        True if the linked list has a cycle, False otherwise.

    Example:
        >>> # Create a cycle: 1 -> 2 -> 3 -> 4 -> (back to 2)
        >>> # (See p141_linked_list_cycle.py for full test setup)
    """
    if not head or not head.next:
        return False

    slow = head
    fast = head
    while fast and fast.next:
        slow = slow.next
        fast = fast.next.next
        if slow is fast:
            return True
    return False


def find_middle(head) -> "type(head) | None":
    """Variant 2: Find the middle node of a linked list.

    When fast reaches the end, slow will be at the middle.
    For even-length lists, slow lands on the second of the two middle nodes.
    Use a dummy node if you want the first middle node.

    Time:  O(n) -- fast pointer traverses at most 2n nodes
    Space: O(1) -- only two pointer references

    Args:
        head: Head node of a linked list.

    Returns:
        The middle node, or None if the list is empty.

    Example:
        >>> # 1 -> 2 -> 3 -> 4 -> 5, middle is node with value 3
        >>> # 1 -> 2 -> 3 -> 4, middle is node with value 3 (second of two middles)
    """
    if not head:
        return None

    slow = head
    fast = head
    while fast and fast.next:
        slow = slow.next
        fast = fast.next.next
    return slow


def is_happy(n: int) -> bool:
    """Variant 3: Happy number (number theory cycle detection).

    A number is happy if repeatedly replacing it with the sum of the squares
    of its digits eventually leads to 1. If the process enters a cycle that
    does not include 1, the number is not happy.

    The transformation sequence for any starting number will eventually enter
    a cycle (by the pigeonhole principle, since there are finitely many possible
    values). Use fast/slow pointers to detect whether 1 is in that cycle.

    Time:  O(log n) per step, O(log n * cycle_length) total
    Space: O(1) -- no extra data structures needed

    Args:
        n: A positive integer.

    Returns:
        True if n is a happy number, False otherwise.

    Example:
        >>> is_happy(19)
        True
        >>> is_happy(2)
        False
    """
    def get_next(num: int) -> int:
        """Compute the sum of squares of digits."""
        total = 0
        while num > 0:
            digit = num % 10
            total += digit * digit
            num //= 10
        return total

    slow = n
    fast = get_next(n)
    while fast != 1 and slow != fast:
        slow = get_next(slow)
        fast = get_next(get_next(fast))
    return fast == 1


if __name__ == "__main__":
    # Quick smoke tests
    assert is_happy(19) is True
    assert is_happy(2) is False
    assert is_happy(1) is True
    print("All template smoke tests passed.")
