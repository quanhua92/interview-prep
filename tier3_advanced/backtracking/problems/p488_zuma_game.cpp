/*
 * P488: Zuma Game [PREMIUM] (Hard)
 * https://leetcode.com/problems/zuma-game/
 * Topics: String, Dynamic Programming, Stack, Breadth-First Search, Memoization
 *
 * Given a string board and a string hand, return the minimum number of balls you have to insert to clear all the balls from the board.
 * Example 1:
 *     Input: board = "WRRBBW", hand = "RB"
 *     Output: -1
 *
 * Example 2:
 *     Input: board = "WWRRBBWW", hand = "WRBRW"
 *     Output: 2
 *
 * Template (python3):
 *     class Solution:
 *         def findMinStep(self, board: str, hand: str) -> int:
 */

#include "io.h"
#include <algorithm>
#include <map>

static std::string collapse(const std::string &s) {
    abort();
}

static int dfs(const std::string &board, const std::string &hand,
               std::map<std::pair<std::string, std::string>, int> &memo) {
    std::string b = collapse(board);
    if (b.empty()) return 0;
    if (hand.empty()) return -1;
    auto key = std::make_pair(b, hand);
    if (memo.count(key)) return memo[key];
    int minBalls = -1;
    int blen = (int)b.size();
    int hlen = (int)hand.size();
    for (int i = 0; i <= blen; i++) {
        for (int hi = 0; hi < hlen; hi++) {
            if (hi > 0 && hand[hi] == hand[hi - 1]) continue;
            char color = hand[hi];
            std::string newBoard = b.substr(0, i) + color + b.substr(i);
            std::string newHand = hand.substr(0, hi) + hand.substr(hi + 1);
            int result = dfs(newBoard, newHand, memo);
            if (result != -1) {
                if (minBalls == -1 || result + 1 < minBalls) minBalls = result + 1;
            }
        }
    }
    memo[key] = minBalls;
    return minBalls;
}

static int findMinStep(const std::string &board, const std::string &hand) {
    abort();
}

int main(void) {
    std::string board = read_line();
    std::string hand = read_line();
    write_int(findMinStep(board, hand));
    return 0;
}
