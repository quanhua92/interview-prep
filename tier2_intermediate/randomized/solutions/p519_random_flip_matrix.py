"""
P519: Random Flip Matrix [PREMIUM] (Medium)
https://leetcode.com/problems/random-flip-matrix/
Topics: Hash Table, Math, Reservoir Sampling, Randomized

There is an m x n binary grid matrix with all the values set 0 initially. Design an algorithm to randomly pick an index (i, j) where matrix[i][j] == 0 and flips it to 1. All the indices (i, j) where matrix[i][j] == 0 should be equally likely to be returned.
Optimize your algorithm to minimize the number of calls made to the built-in random function of your language and optimize the time and space complexity.
Implement the Solution class:
Example 1:
    Input
Example 1:
    ["Solution", "flip", "flip", "flip", "reset", "flip"]
    [[3, 1], [], [], [], [], []]
    Output
    [null, [1, 0], [2, 0], [0, 0], null, [2, 0]]

    Explanation
    Solution solution = new Solution(3, 1);
    solution.flip();  // return [1, 0], [0,0], [1,0], and [2,0] should be equally likely to be returned.
    solution.flip();  // return [2, 0], Since [1,0] was returned, [2,0] and [0,0]
    solution.flip();  // return [0, 0], Based on the previously returned indices, only [0,0] can be returned.
    solution.reset(); // All the values are reset to 0 and can be returned.
    solution.flip();  // return [2, 0], [0,0], [1,0], and [2,0] should be equally likely to be returned.

Constraints:
    - 1 <= m, n <= 104
    - There will be at least one free cell for each call to flip.
    - At most 1000 calls will be made to flip and reset.

Template (python3):
    class Solution:

        def __init__(self, m: int, n: int):


        def flip(self) -> List[int]:


        def reset(self) -> None:



    # Your Solution object will be instantiated and called as such:
    # obj = Solution(m, n)
    # param_1 = obj.flip()
    # obj.reset()
"""

from src.wasm_libs.py.io import *


def solve(m: int, n: int, num_flips: int) -> int:
    import random

    total = m * n
    mapping: dict[int, int] = {}
    results: set[int] = set()
    for _ in range(num_flips):
        r = random.randint(0, total - 1)
        total -= 1
        idx = mapping.get(r, r)
        mapping[r] = mapping.get(total, total)
        results.add(idx)
    return len(results)


if __name__ == "__main__":
    m = read_int()
    n = read_int()
    num_flips = read_int()
    result = solve(m, n, num_flips)
    write_int(result)
