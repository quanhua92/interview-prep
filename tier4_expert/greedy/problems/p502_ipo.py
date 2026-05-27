"""
P502: IPO [PREMIUM] (Hard)
https://leetcode.com/problems/ipo/
Topics: Array, Greedy, Sorting, Heap (Priority Queue)

Given k, w, profits[], capital[], return maximized capital after at most k projects.

Constraints:
    - 1 <= k <= 105
    - 0 <= w <= 109
    - 1 <= n <= 105
"""

from src.wasm_libs.py.io import *


def solve(k: int, w: int, profits: list[int], capital: list[int]) -> int:
    raise NotImplementedError


if __name__ == "__main__":
    k = read_int()
    w = read_int()
    profits = read_ints()
    capital = read_ints()
    result = solve(k, w, profits, capital)
    write_int(result)
