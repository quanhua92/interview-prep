/*
 * P455: Assign Cookies (Easy)
 * https://leetcode.com/problems/assign-cookies/
 * Topics: Array, Two Pointers, Greedy, Sorting
 *
 * Each child i has a greed factor g[i], and each cookie j has a size s[j].
 * Return the maximum number of content children.
 *
 * Constraints:
 *     - 1 <= g.length <= 3 * 104
 *     - 0 <= s.length <= 3 * 104
 *
 * Template (python3):
 *     class Solution:
 *         def findContentChildren(self, g: List[int], s: List[int]) -> int:
 */


#include "ctest.h"
#include <stdlib.h>

int cmp_int(const void *a, const void *b) {
    return *(const int *)a - *(const int *)b;
}

int findContentChildren(int *g, int gSize, int *s, int sSize) {
    qsort(g, (size_t)gSize, sizeof(int), cmp_int);
    qsort(s, (size_t)sSize, sizeof(int), cmp_int);
    int child = 0, cookie = 0;
    while (child < gSize && cookie < sSize) {
        if (s[cookie] >= g[child]) child++;
        cookie++;
    }
    return child;
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
