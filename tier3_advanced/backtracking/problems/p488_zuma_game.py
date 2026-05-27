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

Example 2:
    Input: board = "WWRRBBWW", hand = "WRBRW"
    Output: 2

Example 3:
    Input: board = "G", hand = "GGGGG"
    Output: 2

Constraints:
    - 1 <= board.length <= 16
    - 1 <= hand.length <= 5
    - board and hand consist of the characters 'R', 'Y', 'B', 'G', and 'W'.

Template (python3):
    class Solution:
        def findMinStep(self, board: str, hand: str) -> int:
"""

from src.wasm_libs.py.io import *


def solve(board: str, hand: str) -> int:
    raise NotImplementedError


if __name__ == "__main__":
    board = read_line()
    hand = read_line()
    result = solve(board, hand)
    write_int(result)
