"""Bit Manipulation — 3 Variants

Variant 1: Brian Kernighan's algorithm for counting 1-bits
Variant 2: XOR trick for finding single numbers
Variant 3: DP + bit manipulation for counting bits
"""

from __future__ import annotations


# ---------------------------------------------------------------------------
# Variant 1: Brian Kernighan's algorithm
# ---------------------------------------------------------------------------


def count_bits_kernighan(n: int) -> int:
    """Count the number of 1-bits in an integer using Brian Kernighan's algorithm.

    Repeatedly clears the least significant set bit: n & (n - 1).
    Runs in O(k) time where k is the number of set bits.

    Args:
        n: Non-negative integer.

    Returns:
        Number of 1-bits in n.
    """
    count = 0
    while n:
        n &= n - 1
        count += 1
    return count


# ---------------------------------------------------------------------------
# Variant 2: XOR trick for finding single numbers
# ---------------------------------------------------------------------------


def single_number(nums: list[int]) -> int:
    """Find the element that appears exactly once (all others appear twice).

    Uses XOR: a ^ a = 0, a ^ 0 = a, XOR is commutative.
    Time: O(n), Space: O(1)

    Args:
        nums: List where every element appears twice except for one.

    Returns:
        The element that appears exactly once.
    """
    result = 0
    for num in nums:
        result ^= num
    return result


# ---------------------------------------------------------------------------
# Variant 3: DP + bit manipulation for counting bits
# ---------------------------------------------------------------------------


def count_bits_dp(n: int) -> list[int]:
    """Return an array ans where ans[i] is the number of 1-bits in i.

    Uses DP: ans[i] = ans[i >> 1] + (i & 1).
    Time: O(n), Space: O(n)

    Args:
        n: Non-negative integer upper bound (inclusive).

    Returns:
        List of bit counts for [0, n].
    """
    ans: list[int] = [0] * (n + 1)
    for i in range(1, n + 1):
        ans[i] = ans[i >> 1] + (i & 1)
    return ans
