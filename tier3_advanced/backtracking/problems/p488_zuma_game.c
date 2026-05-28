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
#include <stdlib.h>
#include <string.h>

#define MAXBOARD 32
#define MAXHAND 16
#define MAP_SIZE 65536

typedef struct Entry {
    char board[MAXBOARD + 1];
    char hand[MAXHAND + 1];
    int val;
    int used;
} Entry;

static Entry map[MAP_SIZE];

static unsigned hash_str(const char *s) {
    abort();
}

static int map_get(const char *board, const char *hand) {
    abort();
}

static void map_put(const char *board, const char *hand, int val) {
    abort();
}

static void collapse(char *s) {
    abort();
}

static int dfs(const char *board_str, const char *hand_sorted) {
    abort();
}

static int cmp_char(const void *a, const void *b) {
    abort();
}

int main(void) {
    char *board = read_line();
    char *hand = read_line();
    memset(map, 0, sizeof(map));
    char sorted_hand[MAXHAND + 1];
    strcpy(sorted_hand, hand);
    int hlen = (int)strlen(sorted_hand);
    qsort(sorted_hand, hlen, 1, cmp_char);
    int result = dfs(board, sorted_hand);
    write_int(result);
    free(board);
    free(hand);
    return 0;
}
