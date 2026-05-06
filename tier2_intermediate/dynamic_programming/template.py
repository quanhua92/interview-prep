"""Dynamic Programming — 3 Variants

Variant 1: 1D DP (Fibonacci / Climbing Stairs)
Variant 2: 1D DP with full scan (House Robber / Maximum Subarray)
Variant 3: 2D DP (Knapsack / Coin Change)
"""

from __future__ import annotations


# ---------------------------------------------------------------------------
# Variant 1: 1D DP — Fibonacci / Climbing Stairs
# ---------------------------------------------------------------------------


def climb_stairs(n: int) -> int:
    """Return the number of distinct ways to climb *n* stairs.

    At each step you may climb 1 or 2 stairs.

    This is equivalent to computing the (n+1)-th Fibonacci number.
    Uses O(1) space with two variables.

    Args:
        n: Total number of stairs (non-negative integer).

    Returns:
        Number of distinct ways to reach the top.
    """
    if n <= 2:
        return max(n, 1)
    a: int = 1  # f(1)
    b: int = 2  # f(2)
    for _ in range(3, n + 1):
        a, b = b, a + b
    return b


def fibonacci(n: int) -> int:
    """Return the n-th Fibonacci number (0-indexed: fib(0)=0, fib(1)=1).

    Args:
        n: Index of the Fibonacci number.

    Returns:
        The n-th Fibonacci number.
    """
    if n <= 0:
        return 0
    a: int = 0
    b: int = 1
    for _ in range(2, n + 1):
        a, b = b, a + b
    return b


# ---------------------------------------------------------------------------
# Variant 2: 1D DP with full scan — House Robber
# ---------------------------------------------------------------------------


def house_robber(nums: list[int]) -> int:
    """Return the maximum amount that can be robbed without alerting police.

    Constraint: adjacent houses cannot both be robbed.

    Args:
        nums: List of non-negative integers representing money at each house.

    Returns:
        Maximum amount of money that can be robbed.
    """
    if not nums:
        return 0
    if len(nums) == 1:
        return nums[0]

    # dp[i] = max money robbing houses[0..i]
    prev2: int = 0  # dp[i-2]
    prev1: int = nums[0]  # dp[i-1]

    for i in range(1, len(nums)):
        current = max(prev1, prev2 + nums[i])
        prev2, prev1 = prev1, current

    return prev1


# ---------------------------------------------------------------------------
# Variant 3: 2D DP — Coin Change
# ---------------------------------------------------------------------------


def coin_change(coins: list[int], amount: int) -> int:
    """Return the fewest coins needed to make *amount*, or -1 if impossible.

    Uses a 1D DP array where ``dp[i]`` is the minimum number of coins needed
    to make amount *i*.

    Args:
        coins: List of distinct positive coin denominations.
        amount: Target amount (non-negative integer).

    Returns:
        Minimum number of coins, or -1 if the amount cannot be formed.
    """
    if amount < 0:
        return -1
    # dp[i] = minimum coins to make amount i
    INF = amount + 1  # sentinel larger than any possible answer
    dp: list[int] = [INF] * (amount + 1)
    dp[0] = 0

    for i in range(1, amount + 1):
        for coin in coins:
            if coin <= i:
                dp[i] = min(dp[i], dp[i - coin] + 1)

    return dp[amount] if dp[amount] != INF else -1


def coin_change_combinations(coins: list[int], amount: int) -> int:
    """Return the **number** of ways to make *amount* with the given coins.

    Each coin denomination may be used an unlimited number of times.

    Args:
        coins: List of distinct positive coin denominations.
        amount: Target amount.

    Returns:
        Number of combinations that sum to *amount*.
    """
    dp: list[int] = [0] * (amount + 1)
    dp[0] = 1  # one way to make 0: use no coins

    for coin in coins:
        for i in range(coin, amount + 1):
            dp[i] += dp[i - coin]

    return dp[amount]
