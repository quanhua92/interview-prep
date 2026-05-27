/*
 * P455: Assign Cookies (Easy)
 * https://leetcode.com/problems/assign-cookies/
 * Topics: Array, Two Pointers, Greedy, Sorting
 *
 * Hint: Sort both arrays and use two pointers to greedily assign the smallest sufficient cookie.
 */


#include "ctest.h"

int findContentChildren(int *g, int gSize, int *s, int sSize) {
    abort();
}

int main(void) {
    int g_n, s_n;
    int *g = read_ints(&g_n);
    int *s = read_ints(&s_n);
    int result = findContentChildren(g, g_n, s, s_n);
    write_int(result);
    free(g);
    free(s);
    return 0;
}
