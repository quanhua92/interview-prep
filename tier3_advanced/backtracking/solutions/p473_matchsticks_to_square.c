/*
 * P473: Matchsticks to Square [PREMIUM] (Medium)
 * https://leetcode.com/problems/matchsticks-to-square/
 * Topics: Array, Dynamic Programming, Backtracking, Bit Manipulation, Bitmask
 *
 * You are given an integer array matchsticks where matchsticks[i] is the length of the ith matchstick. You want to use all the matchsticks to make one square. You should not break any stick, but you can link them up, and each matchstick must be used exactly one time.
 * Return true if you can make this square and false otherwise.
 * Example 1:
 *     Input: matchsticks = [1,1,2,2,2]
 *     Output: true
 *
 * Example 2:
 *     Input: matchsticks = [3,3,3,3,4]
 *     Output: false
 *
 * Hint: Treat the matchsticks as an array. Can we split the array into 4 equal parts?
 */

#include "io.h"
#include <stdlib.h>
#include <string.h>

static int g_sticks[15];
static int g_n;
static int g_side;
static int g_sides[4];

static int sort_desc(const void *a, const void *b) {
    return *(const int *)b - *(const int *)a;
}

static int bt(int idx) {
    if (idx == g_n) return g_sides[0] == g_side && g_sides[1] == g_side &&
                         g_sides[2] == g_side && g_sides[3] == g_side;
    for (int i = 0; i < 4; i++) {
        if (g_sides[i] + g_sticks[idx] <= g_side) {
            g_sides[i] += g_sticks[idx];
            if (bt(idx + 1)) return 1;
            g_sides[i] -= g_sticks[idx];
            if (g_sides[i] == 0) break;
        }
    }
    return 0;
}

int main(void) {
    int n;
    int *matchsticks = read_ints(&n);
    if (n == 0) { write_bool(0); free(matchsticks); return 0; }
    long long total = 0;
    for (int i = 0; i < n; i++) total += matchsticks[i];
    if (total % 4 != 0) { write_bool(0); free(matchsticks); return 0; }
    g_side = (int)(total / 4);
    memcpy(g_sticks, matchsticks, n * sizeof(int));
    g_n = n;
    qsort(g_sticks, g_n, sizeof(int), sort_desc);
    if (g_sticks[0] > g_side) { write_bool(0); free(matchsticks); return 0; }
    memset(g_sides, 0, sizeof(g_sides));
    int res = bt(0);
    write_bool(res);
    free(matchsticks);
    return 0;
}
