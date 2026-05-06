"""Stack — 3 Variants

Variant 1: Matching brackets / valid parentheses
Variant 2: Nested structure decoding
Variant 3: Auxiliary stack for min tracking
"""

from __future__ import annotations


# ---------------------------------------------------------------------------
# Variant 1: Matching brackets
# ---------------------------------------------------------------------------


def is_valid_parentheses(s: str) -> bool:
    """Check if a string of brackets is valid (properly nested and closed).

    Args:
        s: String containing only '()[]{}'.

    Returns:
        True if the string is valid, False otherwise.
    """
    mapping = {")": "(", "]": "[", "}": "{"}
    stack: list[str] = []
    for ch in s:
        if ch in mapping:
            if not stack or stack[-1] != mapping[ch]:
                return False
            stack.pop()
        else:
            stack.append(ch)
    return len(stack) == 0


# ---------------------------------------------------------------------------
# Variant 2: Nested structure decoding
# ---------------------------------------------------------------------------


def decode_string(s: str) -> str:
    """Decode a string encoded with k[encoded_string] pattern.

    Examples:
        "3[a]" -> "aaa"
        "3[a2[c]]" -> "accaccacc"

    Args:
        s: Encoded string.

    Returns:
        Decoded string.
    """
    stack: list[tuple[int, str]] = []  # (repeat_count, prefix_string)
    curr_num: int = 0
    curr_str: str = ""

    for ch in s:
        if ch.isdigit():
            curr_num = curr_num * 10 + int(ch)
        elif ch == "[":
            stack.append((curr_num, curr_str))
            curr_num = 0
            curr_str = ""
        elif ch == "]":
            repeat, prefix = stack.pop()
            curr_str = prefix + curr_str * repeat
        else:
            curr_str += ch

    return curr_str


# ---------------------------------------------------------------------------
# Variant 3: Min stack
# ---------------------------------------------------------------------------


class MinStack:
    """Stack that supports push, pop, top, and retrieving the minimum in O(1)."""

    def __init__(self) -> None:
        self._stack: list[int] = []
        self._min_stack: list[int] = []

    def push(self, val: int) -> None:
        """Push a value onto the stack."""
        self._stack.append(val)
        min_val = val if not self._min_stack else min(val, self._min_stack[-1])
        self._min_stack.append(min_val)

    def pop(self) -> None:
        """Remove the top element from the stack."""
        self._stack.pop()
        self._min_stack.pop()

    def top(self) -> int:
        """Get the top element of the stack."""
        return self._stack[-1]

    def get_min(self) -> int:
        """Get the minimum element in the stack."""
        return self._min_stack[-1]
