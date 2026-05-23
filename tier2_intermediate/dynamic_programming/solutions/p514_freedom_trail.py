"""
P514: Freedom Trail [PREMIUM] (Hard)
https://leetcode.com/problems/freedom-trail/
Topics: String, Dynamic Programming, Depth-First Search, Breadth-First Search

In the video game Fallout 4, the quest "Road to Freedom" requires players to reach a metal dial called the "Freedom Trail Ring" and use the dial to spell a specific keyword to open the door.
Given a string ring that represents the code engraved on the outer ring and another string key that represents the keyword that needs to be spelled, return the minimum number of steps to spell all the characters in the keyword.
Initially, the first character of the ring is aligned at the "12:00" direction. You should spell all the characters in key one by one by rotating ring clockwise or anticlockwise to make each character of the string key aligned at the "12:00" direction and then by pressing the center button.
At the stage of rotating the ring to spell the key character key[i]:
Example 1:
    Input: ring = "godding", key = "gd"
    Output: 4
    Explanation:
    For the first key character 'g', since it is already in place, we just need 1 step to spell this character.
    For the second key character 'd', we need to rotate the ring "godding" anticlockwise by two steps to make it become "ddinggo".
    Also, we need 1 more step for spelling.
    So the final output is 4.

Example 2:
    Input: ring = "godding", key = "godding"
    Output: 13

Constraints:
    - 1 <= ring.length, key.length <= 100
    - ring and key consist of only lower case English letters.
    - It is guaranteed that key could always be spelled by rotating ring.

Template (python3):
    class Solution:
        def findRotateSteps(self, ring: str, key: str) -> int:
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "514. Freedom Trail"
    test_cases = [
        TestCase(input=("godding", "gd"), expected=4, label="example 1"),
        TestCase(input=("godding", "godding"), expected=13, label="example 2"),
        TestCase(input=("a", "a"), expected=1, label="single char ring and key"),
        TestCase(input=("abc", "cba"), expected=6, label="reverse order key"),
        TestCase(input=("aaaaa", "aaa"), expected=3, label="repeated chars"),
    ]

    def solve(self, ring: str, key: str) -> int:
        from collections import defaultdict

        char_positions: dict[str, list[int]] = defaultdict(list)
        for i, ch in enumerate(ring):
            char_positions[ch].append(i)

        n = len(ring)
        dp = [0] * n

        for ki in range(len(key) - 1, -1, -1):
            new_dp = [float("inf")] * n
            for pos in range(n):
                for target in char_positions[key[ki]]:
                    diff = abs(pos - target)
                    steps = min(diff, n - diff) + 1
                    if ki == len(key) - 1:
                        new_dp[pos] = min(new_dp[pos], steps)
                    else:
                        new_dp[pos] = min(new_dp[pos], steps + dp[target])
            dp = new_dp

        return dp[0]


if __name__ == "__main__":
    Solution().run()
