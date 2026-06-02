"""
P455: Assign Cookies (Easy)
https://leetcode.com/problems/assign-cookies/
Topics: Array, Two Pointers, Greedy, Sorting

Each child i has a greed factor g[i], and each cookie j has a size s[j].
Return the maximum number of content children.

Constraints:
    - 1 <= g.length <= 3 * 10^4
    - 0 <= s.length <= 3 * 10^4

Hint: Sort both arrays and use two pointers to greedily assign the smallest sufficient cookie.
"""

from src.wasm_libs.py.io import *


def solve(g: list[int], s: list[int]) -> int:
    raise NotImplementedError


if __name__ == "__main__":
    g = read_ints()
    s = read_ints()
    result = solve(g, s)
    write_int(result)
