"""Monotonic stack template with three variants.

Variant 1: Next greater element (ascending stack)
Variant 2: Previous smaller element (descending stack)
Variant 3: Sliding window maximum with monotonic deque
"""

from collections import deque


# ── Variant 1: Next greater element (ascending stack) ────────────────────────

def daily_temperatures(temperatures: list[int]) -> list[int]:
    """Find how many days until a warmer temperature for each day.

    Uses an ascending (strictly decreasing) stack of indices.
    When we see a temperature warmer than the stack top, we pop and compute distance.

    Time: O(n), Space: O(n)
    """
    n = len(temperatures)
    answer = [0] * n
    stack: list[int] = []  # indices with decreasing temperatures
    for i in range(n):
        while stack and temperatures[i] > temperatures[stack[-1]]:
            j = stack.pop()
            answer[j] = i - j
        stack.append(i)
    return answer


# ── Variant 2: Previous smaller element (descending stack) ───────────────────

def previous_smaller_element(nums: list[int]) -> list[int]:
    """Find the index of the previous smaller element for each position.

    Uses a descending (strictly increasing) stack of indices.
    Returns -1 if no previous smaller element exists.

    Time: O(n), Space: O(n)
    """
    n = len(nums)
    result: list[int] = [-1] * n
    stack: list[int] = []  # indices with increasing values
    for i in range(n):
        while stack and nums[i] <= nums[stack[-1]]:
            stack.pop()
        if stack:
            result[i] = stack[-1]
        stack.append(i)
    return result


# ── Variant 3: Sliding window maximum (monotonic deque) ─────────────────────

def sliding_window_maximum(nums: list[int], k: int) -> list[int]:
    """Find the maximum in each sliding window of size k.

    Uses a decreasing deque: the front always has the maximum of the current window.
    When the front index is out of the window, pop it from the left.

    Time: O(n), Space: O(k)
    """
    result: list[int] = []
    dq: deque[int] = deque()  # indices with decreasing values

    for i, num in enumerate(nums):
        # Remove indices whose values are less than or equal to current
        while dq and nums[dq[-1]] <= num:
            dq.pop()
        dq.append(i)

        # Remove the front if it's outside the window
        if dq[0] == i - k:
            dq.popleft()

        # Record the maximum for windows that have reached size k
        if i >= k - 1:
            result.append(nums[dq[0]])

    return result
