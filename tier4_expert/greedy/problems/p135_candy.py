"""
P135: Candy (Hard)
https://leetcode.com/problems/candy/
Topics: Array, Greedy

There are n children standing in a line. Each child is assigned a rating value given in the integer array ratings.
Return the minimum number of candies you need to have to distribute the candies to the children.

Constraints:
    - n == ratings.length
    - 1 <= n <= 2 * 10^4
    - 0 <= ratings[i] <= 2 * 10^4

Hint: Two-pass greedy: left-to-right then right-to-left, taking the max of both passes.
"""

from src.wasm_libs.py.io import *


def solve(ratings: list[int]) -> int:
    raise NotImplementedError


if __name__ == "__main__":
    ratings = read_ints()
    result = solve(ratings)
    write_int(result)
