"""Prefix Sum — 3 Variants

Variant 1: Standard prefix sum for range sum queries
Variant 2: Prefix sum with hash map for subarray sum counting
Variant 3: Prefix product for product-of-array problems
"""

from __future__ import annotations

from typing import Any


# ---------------------------------------------------------------------------
# Variant 1: Standard prefix sum for range sum queries
# ---------------------------------------------------------------------------

def prefix_sum_array(nums: list[int]) -> list[int]:
    """Build a prefix sum array where prefix[i] = sum(nums[0:i]).

    Args:
        nums: Input list of integers.

    Returns:
        Prefix sum array of length len(nums) + 1, where prefix[0] = 0.
    """
    prefix: list[int] = [0] * (len(nums) + 1)
    for i, val in enumerate(nums):
        prefix[i + 1] = prefix[i] + val
    return prefix


def range_sum(prefix: list[int], left: int, right: int) -> int:
    """Compute sum of nums[left:right] using a prefix sum array.

    Args:
        prefix: Prefix sum array (from prefix_sum_array).
        left: Inclusive start index.
        right: Exclusive end index.

    Returns:
        Sum of elements in the range [left, right).
    """
    return prefix[right] - prefix[left]


# ---------------------------------------------------------------------------
# Variant 2: Prefix sum with hash map for subarray sum counting
# ---------------------------------------------------------------------------

def subarray_sum_equals_k(nums: list[int], k: int) -> int:
    """Count the number of subarrays whose sum equals k.

    Uses a hash map mapping prefix_sum -> frequency to count subarrays
    ending at each position whose sum equals k.

    Args:
        nums: Input list of integers.
        k: Target sum.

    Returns:
        Number of subarrays with sum exactly k.
    """
    from collections import defaultdict

    count: int = 0
    curr_sum: int = 0
    prefix_freq: dict[int, int] = defaultdict(int)
    prefix_freq[0] = 1

    for num in nums:
        curr_sum += num
        count += prefix_freq.get(curr_sum - k, 0)
        prefix_freq[curr_sum] += 1

    return count


# ---------------------------------------------------------------------------
# Variant 3: Prefix product for product-of-array problems
# ---------------------------------------------------------------------------

def product_except_self(nums: list[int]) -> list[int]:
    """Return an array where output[i] is the product of all elements
    except nums[i], without using division and in O(n) time.

    Uses left and right product accumulation passes.

    Args:
        nums: Input list of integers.

    Returns:
        List where each element is the product of all other elements.
    """
    n = len(nums)
    output: list[int] = [1] * n

    # Left pass: output[i] = product of nums[0:i]
    left_product = 1
    for i in range(n):
        output[i] = left_product
        left_product *= nums[i]

    # Right pass: multiply by product of nums[i+1:n]
    right_product = 1
    for i in range(n - 1, -1, -1):
        output[i] *= right_product
        right_product *= nums[i]

    return output
