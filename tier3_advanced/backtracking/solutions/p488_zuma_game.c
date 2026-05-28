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
    unsigned h = 5381;
    while (*s) h = h * 33 + (unsigned char)*s++;
    return h % MAP_SIZE;
}

static int map_get(const char *board, const char *hand) {
    unsigned h = hash_str(board) ^ (hash_str(hand) * 31);
    for (int i = 0; i < MAP_SIZE; i++) {
        int idx = (h + i) % MAP_SIZE;
        if (map[idx].used && strcmp(map[idx].board, board) == 0 && strcmp(map[idx].hand, hand) == 0) {
            return map[idx].val;
        }
    }
    return -2;
}

static void map_put(const char *board, const char *hand, int val) {
    unsigned h = hash_str(board) ^ (hash_str(hand) * 31);
    for (int i = 0; i < MAP_SIZE; i++) {
        int idx = (h + i) % MAP_SIZE;
        if (!map[idx].used) {
            strcpy(map[idx].board, board);
            strcpy(map[idx].hand, hand);
            map[idx].val = val;
            map[idx].used = 1;
            return;
        }
    }
}

static void collapse(char *s) {
    int changed = 1;
    while (changed) {
        changed = 0;
        int len = (int)strlen(s);
        int wr = 0;
        int i = 0;
        while (i < len) {
            int j = i;
            while (j < len && s[j] == s[i]) j++;
            if (j - i >= 3) {
                changed = 1;
            } else {
                for (int k = i; k < j; k++) s[wr++] = s[k];
            }
            i = j;
        }
        s[wr] = '\0';
    }
}

static int dfs(const char *board_str, const char *hand_sorted) {
    char board[MAXBOARD + 1];
    strcpy(board, board_str);
    collapse(board);

    if (board[0] == '\0') return 0;
    if (hand_sorted[0] == '\0') return -1;

    int cached = map_get(board, hand_sorted);
    if (cached != -2) return cached;

    int min_balls = -1;
    int blen = (int)strlen(board);
    int hlen = (int)strlen(hand_sorted);

    for (int i = 0; i <= blen; i++) {
        for (int hi = 0; hi < hlen; hi++) {
            if (hi > 0 && hand_sorted[hi] == hand_sorted[hi - 1]) continue;
            char color = hand_sorted[hi];
            char new_board[MAXBOARD + 1];
            char new_hand[MAXHAND + 1];
            int nb = 0, nh = 0;
            for (int k = 0; k < i; k++) new_board[nb++] = board[k];
            new_board[nb++] = color;
            for (int k = i; k < blen; k++) new_board[nb++] = board[k];
            new_board[nb] = '\0';
            for (int k = 0; k < hlen; k++) {
                if (k != hi) new_hand[nh++] = hand_sorted[k];
            }
            new_hand[nh] = '\0';
            int result = dfs(new_board, new_hand);
            if (result != -1) {
                if (min_balls == -1 || result + 1 < min_balls) {
                    min_balls = result + 1;
                }
            }
        }
    }

    map_put(board, hand_sorted, min_balls);
    return min_balls;
}

static int cmp_char(const void *a, const void *b) {
    return *(const char *)a - *(const char *)b;
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
