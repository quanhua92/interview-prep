"""Shared data structures used across multiple patterns."""


class ListNode:
    """Singly-linked list node."""

    def __init__(self, val: int = 0, next: "ListNode | None" = None):
        self.val = val
        self.next = next

    def __repr__(self):
        return f"ListNode({self.val})"

    def __eq__(self, other):
        if not isinstance(other, ListNode):
            return False
        a, b = self, other
        while a and b:
            if a.val != b.val:
                return False
            a, b = a.next, b.next
        return a is None and b is None

    @staticmethod
    def from_list(values: list[int]) -> "ListNode | None":
        """Build a linked list from a Python list."""
        if not values:
            return None
        head = ListNode(values[0])
        current = head
        for val in values[1:]:
            current.next = ListNode(val)
            current = current.next
        return head

    def to_list(self) -> list[int]:
        """Convert linked list to a Python list."""
        result = []
        current = self
        while current:
            result.append(current.val)
            current = current.next
        return result


class TreeNode:
    """Binary tree node."""

    def __init__(self, val: int = 0, left: "TreeNode | None" = None,
                 right: "TreeNode | None" = None):
        self.val = val
        self.left = left
        self.right = right

    def __repr__(self):
        return f"TreeNode({self.val})"

    def __eq__(self, other):
        if not isinstance(other, TreeNode):
            return False
        return self.val == other.val and self.left == other.left and self.right == other.right

    @staticmethod
    def from_list(values: list[int | None]) -> "TreeNode | None":
        """Build a binary tree from level-order list (None = no node).

        Example: [3, 9, 20, None, None, 15, 7]
        """
        if not values or values[0] is None:
            return None
        root = TreeNode(int(values[0]))
        queue: list[TreeNode] = [root]
        i = 1
        while queue and i < len(values):
            node = queue.pop(0)
            if i < len(values):
                left_val = values[i]
                if left_val is not None:
                    left = TreeNode(left_val)
                    node.left = left
                    queue.append(left)
            i += 1
            if i < len(values):
                right_val = values[i]
                if right_val is not None:
                    right = TreeNode(right_val)
                    node.right = right
                    queue.append(right)
            i += 1
        return root

    def to_list(self) -> list[int | None]:
        """Convert binary tree to level-order list."""
        if not self:
            return []
        result: list[int | None] = []
        queue: list[TreeNode | None] = [self]
        while queue:
            node = queue.pop(0)
            if node is None:
                result.append(None)
                continue
            result.append(node.val)
            queue.append(node.left)
            queue.append(node.right)
        # Trim trailing Nones
        while result and result[-1] is None:
            result.pop()
        return result
