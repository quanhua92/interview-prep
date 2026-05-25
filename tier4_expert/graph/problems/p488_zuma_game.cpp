/*
 * P488: Zuma Game [PREMIUM] (Hard)
 * https://leetcode.com/problems/zuma-game/
 * Topics: String, Dynamic Programming, Stack, Breadth-First Search, Memoization
 * 
 * You are playing a variation of the game Zuma.
 * In this variation of Zuma, there is a single row of colored balls on a board, where each ball can be colored red 'R', yellow 'Y', blue 'B', green 'G', or white 'W'. You also have several colored balls in your hand.
 * Your goal is to clear all of the balls from the board. On each turn:
 * Given a string board, representing the row of balls on the board, and a string hand, representing the balls in your hand, return the minimum number of balls you have to insert to clear all the balls from the board. If you cannot clear all the balls from the board using the balls in your hand, return -1.
 * Example 1:
 *     Input: board = "WRRBBW", hand = "RB"
 *     Output: -1
 *     Explanation: It is impossible to clear all the balls. The best you can do is:
 *     - Insert 'R' so the board becomes WRRRBBW. WRRRBBW -> WBBW.
 *     - Insert 'B' so the board becomes WBBBW. WBBBW -> WW.
 *     There are still balls remaining on the board, and you are out of balls to insert.
 * 
 * Example 2:
 *     Input: board = "WWRRBBWW", hand = "WRBRW"
 *     Output: 2
 *     Explanation: To make the board empty:
 *     - Insert 'R' so the board becomes WWRRRBBWW. WWRRRBBWW -> WWBBWW.
 *     - Insert 'B' so the board becomes WWBBBWW. WWBBBWW -> WWWW -> empty.
 *     2 balls from your hand were needed to clear the board.
 * 
 * Example 3:
 *     Input: board = "G", hand = "GGGGG"
 *     Output: 2
 *     Explanation: To make the board empty:
 *     - Insert 'G' so the board becomes GG.
 *     - Insert 'G' so the board becomes GGG. GGG -> empty.
 *     2 balls from your hand were needed to clear the board.
 * 
 * Constraints:
 *     - 1 <= board.length <= 16
 *     - 1 <= hand.length <= 5
 *     - board and hand consist of the characters 'R', 'Y', 'B', 'G', and 'W'.
 *     - The initial row of balls on the board will not have any groups of three or more consecutive balls of the same color.
 * 
 * Template (python3):
 *     class Solution:
 *         def findMinStep(self, board: str, hand: str) -> int:
 */
#include "cpptest.h"
#include <map>
#include <algorithm>

static std::string collapse(const std::string &s) {
    /* TODO: Implement */
    return 0;
}

static int dfs(const std::string &board, const std::string &hand,
               std::map<std::pair<std::string, std::string>, int> &memo) {
    /* TODO: Implement */
    return 0;
}

static int findMinStep(const std::string &board, const std::string &hand) {
    /* TODO: Implement */
    return 0;
}

struct TC {
    const char *label;
    const char *board;
    const char *hand;
    int expected;
};

int main(void) {
    (void)print_arr;
    TC tests[] = {
        {"example 1", "WRRBBW", "RB", -1},
        {"example 2", "WWRRBBWW", "WRBRW", 2},
        {"example 3", "G", "GGGGG", 2},
        {"one insertion clears chain reaction", "RBYYBBRR", "YRB", 1},
        {"insert triggers cascade", "RRWWRRBB", "WWB", 2},
        {"insufficient balls single", "R", "R", -1},
        {"pair plus one makes triple", "RR", "RR", 1},
    };
    int nt = (int)(sizeof(tests) / sizeof(tests[0]));
    int passed = 0;
    for (int i = 0; i < nt; i++) {
        int got = findMinStep(tests[i].board, tests[i].hand);
        if (got == tests[i].expected) {
            passed++;
            printf("  Test %d (%s): PASS\n", i + 1, tests[i].label);
        } else {
            printf("  Test %d (%s): FAIL\n", i + 1, tests[i].label);
            printf("    Expected: %d\n    Got:      %d\n", tests[i].expected, got);
        }
    }
    printf("\n  %d/%d passed\n", passed, nt);
    return passed == nt ? 0 : 1;
}
