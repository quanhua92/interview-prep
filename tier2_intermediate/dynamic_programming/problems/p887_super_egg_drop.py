"""
P887: Super Egg Drop (Hard)
https://leetcode.com/problems/super-egg-drop/
Topics: Dynamic Programming, Math, Binary Search

You are given k identical eggs and you have access to a building with n floors numbered from 1 to n.
There exists a critical floor f where 0 <= f <= n. Any egg dropped from a floor higher than f will break, and any egg dropped from floor f or below will survive.
Return the minimum number of moves you need to determine f with certainty.

In each move, you may take an unbroken egg and drop it from any floor x (1 <= x <= n).
If the egg breaks, you cannot drop it again. You can only determine f if you know with certainty that f == x after some number of drops.

Example 1:
    Input: k = 1, n = 2
    Output: 2
    Explanation:
        Drop the egg from floor 1. If it breaks, f = 0.
        If it does not break, drop it from floor 2. If it breaks, f = 1.
        If it does not break, f = 2.

Example 2:
    Input: k = 3, n = 14
    Output: 4

Example 3:
    Input: k = 2, n = 100
    Output: 14

Constraints:
    - 1 <= k <= 100
    - 1 <= n <= 10^4

Hint: Reframe as: given m moves and k eggs, what is the maximum number of floors we can test?
Use dp[m][k] = dp[m-1][k-1] + dp[m-1][k] + 1. Find the smallest m where dp[m][k] >= n.
"""

from src.wasm_libs.py.io import *


def solve(k: int, n: int) -> int:
    raise NotImplementedError


if __name__ == "__main__":
    k, n = read_ints()
    result = solve(k, n)
    write_int(result)
