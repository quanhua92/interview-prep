"""Sliding Window pattern templates.

Three common variants of the sliding window technique:

1. Fixed-size window: Find the maximum/minimum over all subarrays of size k.
2. Variable-size window (shrinking): Find the longest/shortest substring meeting a condition.
3. Variable-size window (exact count): Count the number of subarrays that satisfy a condition.
"""

from collections import Counter


def sliding_window_max(nums: list[int], k: int) -> int:
    """Variant 1: Fixed-size window.

    Find the maximum value in every contiguous subarray of size k.

    Uses a monotonic deque to track indices of elements in decreasing order.
    The front of the deque always holds the index of the maximum element
    in the current window.

    Time:  O(n) -- each element is pushed and popped at most once
    Space: O(k) -- the deque holds at most k elements

    Args:
        nums: Input array of integers.
        k: Size of the sliding window.

    Returns:
        List of maximum values for each window position.

    Example:
        >>> sliding_window_max([1,3,-1,-3,5,3,6,7], 3)
        [3, 3, 5, 5, 6, 7]
    """
    from collections import deque

    if not nums or k <= 0:
        return []
    if k == 1:
        return nums[:]

    result: list[int] = []
    dq: deque[int] = deque()  # stores indices, values decreasing

    for i, num in enumerate(nums):
        # Remove indices outside the current window
        while dq and dq[0] < i - k + 1:
            dq.popleft()

        # Remove indices whose values are less than current
        while dq and nums[dq[-1]] < num:
            dq.pop()

        dq.append(i)

        # Record result once the first window is complete
        if i >= k - 1:
            result.append(nums[dq[0]])

    return result


def longest_substring_with_condition(s: str) -> int:
    """Variant 2: Variable-size window with shrinking.

    Find the length of the longest substring without repeating characters.
    The left boundary shrinks whenever a duplicate is found inside the window.

    Time:  O(n) -- each character is visited at most twice (once by right, once by left)
    Space: O(min(n, alphabet_size)) -- the hashmap stores at most one entry per unique character

    Args:
        s: Input string.

    Returns:
        Length of the longest substring with all unique characters.

    Example:
        >>> longest_substring_with_condition("abcabcbb")
        3
    """
    char_index: dict[str, int] = {}
    left = 0
    max_len = 0

    for right, ch in enumerate(s):
        # If ch is already in the window, shrink from the left
        if ch in char_index and char_index[ch] >= left:
            left = char_index[ch] + 1
        char_index[ch] = right
        max_len = max(max_len, right - left + 1)

    return max_len


def count_subarrays_with_exact_sum(nums: list[int], target: int) -> int:
    """Variant 3: Variable-size window with exact condition.

    Count the number of subarrays whose sum equals the target.
    This variant uses a prefix-sum hashmap rather than the classic shrink approach,
    because elements can be negative (making the window non-monotonic).

    Time:  O(n) -- single pass with hashmap lookups
    Space: O(n) -- prefix sum hashmap

    Args:
        nums: Input array of integers (may contain negatives).
        target: The desired subarray sum.

    Returns:
        Number of subarrays whose sum equals target.

    Example:
        >>> count_subarrays_with_exact_sum([1, 1, 1], 2)
        2
    """
    prefix_counts: dict[int, int] = {0: 1}
    current_sum = 0
    count = 0

    for num in nums:
        current_sum += num
        # If (current_sum - target) exists in prefix sums,
        # there are subarrays ending here with sum == target
        count += prefix_counts.get(current_sum - target, 0)
        prefix_counts[current_sum] = prefix_counts.get(current_sum, 0) + 1

    return count


if __name__ == "__main__":
    # Quick smoke tests
    assert sliding_window_max([1, 3, -1, -3, 5, 3, 6, 7], 3) == [3, 3, 5, 5, 6, 7]
    assert longest_substring_with_condition("abcabcbb") == 3
    assert longest_substring_with_condition("bbbbb") == 1
    assert count_subarrays_with_exact_sum([1, 1, 1], 2) == 2
    print("All template smoke tests passed.")
