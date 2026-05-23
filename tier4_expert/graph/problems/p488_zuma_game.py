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
        TestCase(input=("RBYYBBRR", "YRB"), expected=1, label="one insertion clears chain reaction"),
        TestCase(input=("RRWWRRBB", "WWB"), expected=2, label="insert triggers cascade"),
        TestCase(input=("R", "R"), expected=-1, label="insufficient balls single"),
        TestCase(input=("RR", "RR"), expected=1, label="pair plus one makes triple"),
    ]

    def solve(self, board: str, hand: str) -> int:
        raise NotImplementedError("TODO: Implement solve(self, board, hand) -> int")


if __name__ == "__main__":
    Solution().run()
