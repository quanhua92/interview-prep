"""
P488: Zuma Game [PREMIUM] (Hard)
https://leetcode.com/problems/zuma-game/
Topics: String, Dynamic Programming, Stack, Breadth-First Search, Memoization

You are playing a variation of the game Zuma.
In this variation of Zuma, there is a single row of colored balls on a board, where each ball can be colored red 'R', yellow 'Y', blue 'B', green 'G', or white 'W'. You also have several colored balls in your hand.
Your goal is to clear all of the balls from the board. On each turn:
Given a string board, representing the row of balls on the board, and a string hand, representing the balls in your hand, return the minimum number of balls you have to insert to clear all the balls from the board. If you cannot clear all the balls from the board using the balls in your hand, return -1.
Example 1:
    Input: board = "WRRBBW", hand = "RB"
    Output: -1
    Explanation: It is impossible to clear all the balls. The best you can do is:
    - Insert 'R' so the board becomes WRRRBBW. WRRRBBW -> WBBW.
    - Insert 'B' so the board becomes WBBBW. WBBBW -> WW.
    There are still balls remaining on the board, and you are out of balls to insert.

Example 2:
    Input: board = "WWRRBBWW", hand = "WRBRW"
    Output: 2
    Explanation: To make the board empty:
    - Insert 'R' so the board becomes WWRRRBBWW. WWRRRBBWW -> WWBBWW.
    - Insert 'B' so the board becomes WWBBBWW. WWBBBWW -> WWWW -> empty.
    2 balls from your hand were needed to clear the board.

Example 3:
    Input: board = "G", hand = "GGGGG"
    Output: 2
    Explanation: To make the board empty:
    - Insert 'G' so the board becomes GG.
    - Insert 'G' so the board becomes GGG. GGG -> empty.
    2 balls from your hand were needed to clear the board.

Constraints:
    - 1 <= board.length <= 16
    - 1 <= hand.length <= 5
    - board and hand consist of the characters 'R', 'Y', 'B', 'G', and 'W'.
    - The initial row of balls on the board will not have any groups of three or more consecutive balls of the same color.

Template (python3):
    class Solution:
        def findMinStep(self, board: str, hand: str) -> int:
"""

import sys

sys.path.insert(0, ".")
from src.utils import Problem, TestCase


class Solution(Problem):
    name = "488. Zuma Game"
    test_cases = [
        TestCase(input=("WRRBBW", "RB"), expected=-1, label="example 1"),
        TestCase(input=("WWRRBBWW", "WRBRW"), expected=2, label="example 2"),
        TestCase(input=("G", "GGGGG"), expected=2, label="example 3"),
    ]

    def solve(self, board: str, hand: str) -> int:
        def collapse(s: str) -> str:
            changed = True
            while changed:
                changed = False
                i = 0
                while i < len(s):
                    j = i
                    while j < len(s) and s[j] == s[i]:
                        j += 1
                    if j - i >= 3:
                        s = s[:i] + s[j:]
                        changed = True
                    else:
                        i = j
            return s

        memo: dict[tuple[str, tuple[str, ...]], int] = {}

        def dfs(board_str: str, hand_sorted: tuple[str, ...]) -> int:
            board_str = collapse(board_str)
            if not board_str:
                return 0
            if not hand_sorted:
                return -1
            key = (board_str, hand_sorted)
            if key in memo:
                return memo[key]
            min_balls = -1
            for i in range(len(board_str) + 1):
                for hi in range(len(hand_sorted)):
                    if hi > 0 and hand_sorted[hi] == hand_sorted[hi - 1]:
                        continue
                    color = hand_sorted[hi]
                    new_board = board_str[:i] + color + board_str[i:]
                    new_hand = hand_sorted[:hi] + hand_sorted[hi + 1 :]
                    result = dfs(new_board, new_hand)
                    if result != -1:
                        if min_balls == -1 or result + 1 < min_balls:
                            min_balls = result + 1
            memo[key] = min_balls
            return min_balls

        return dfs(board, tuple(sorted(hand)))


if __name__ == "__main__":
    Solution().run()
