"""
P135: Candy (Hard)
https://leetcode.com/problems/candy/
Topics: Array, Greedy

There are n children standing in a line. Each child is assigned a rating value given in the integer array ratings.
You are giving candies to these children subjected to the following requirements:
Return the minimum number of candies you need to have to distribute the candies to the children.

Example 1:
    Input: ratings = [1,0,2]
    Output: 5
    Explanation: You can allocate to the first, second and third child with 2, 1, 2 candies respectively.

Example 2:
    Input: ratings = [1,2,2]
    Output: 4
    Explanation: You can allocate to the first, second and third child with 1, 2, 1 candies respectively.
    The third child gets 1 candy because it satisfies the above two conditions.

Constraints:
    - n == ratings.length
    - 1 <= n <= 2 * 104
    - 0 <= ratings[i] <= 2 * 104

Template (python3):
    class Solution:
        def candy(self, ratings: List[int]) -> int:

Hint: Two-pass greedy: left-to-right then right-to-left, taking the max of both passes.
"""

from src.wasm_libs.py.io import *


def solve(ratings: list[int]) -> int:
    n = len(ratings)
    if n == 1:
        return 1

    candies = [1] * n

    for i in range(1, n):
        if ratings[i] > ratings[i - 1]:
            candies[i] = candies[i - 1] + 1

    for i in range(n - 2, -1, -1):
        if ratings[i] > ratings[i + 1]:
            candies[i] = max(candies[i], candies[i + 1] + 1)

    return sum(candies)


if __name__ == "__main__":
    ratings = read_ints()
    result = solve(ratings)
    write_int(result)
