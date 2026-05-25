/*
 * P455: Assign Cookies (Easy)
 * https://leetcode.com/problems/assign-cookies/
 * Topics: Array, Two Pointers, Greedy, Sorting
 *
 * Assume you are an awesome parent and want to give your children some cookies. But, you should give each child at most one cookie.
 * Each child i has a greed factor g[i], which is the minimum size of a cookie that the child will be content with; and each cookie j has a size s[j]. If s[j] >= g[i], we can assign the cookie j to the child i, and the child i will be content. Your goal is to maximize the number of your content children and output the maximum number.
 *
 * Example 1:
 *     Input: g = [1,2,3], s = [1,1]
 *     Output: 1
 *     Explanation: You have 3 children and 2 cookies. The greed factors of 3 children are 1, 2, 3.
 *     And even though you have 2 cookies, since their size is both 1, you could only make the child whose greed factor is 1 content.
 *     You need to output 1.
 *
 * Example 2:
 *     Input: g = [1,2], s = [1,2,3]
 *     Output: 2
 *     Explanation: You have 2 children and 3 cookies. The greed factors of 2 children are 1, 2.
 *     You have 3 cookies and their sizes are big enough to gratify all of the children,
 *     You need to output 2.
 *
 * Constraints:
 *     - 1 <= g.length <= 3 * 104
 *     - 0 <= s.length <= 3 * 104
 *     - 1 <= g[i], s[j] <= 231 - 1
 *
 * Template (python3):
 *     class Solution:
 *         def findContentChildren(self, g: List[int], s: List[int]) -> int:
 *
 * Hint: Sort both arrays and use two pointers to greedily assign the smallest sufficient cookie.
 */


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#include "ctest.h"
#pragma GCC diagnostic pop
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
    printf("\n============================================================\n");
    printf("  455. Assign Cookies\n");
    printf("============================================================\n");
    struct { const char *label; int g[10]; int gn; int s[10]; int sn; int expected; } tests[] = {
        {"example 1", {1,2,3}, 3, {1,1}, 2, 1},
        {"example 2", {1,2}, 2, {1,2,3}, 3, 2},
        {"no children", {0}, 0, {1,2,3}, 3, 0},
        {"no cookies", {1,2}, 2, {0}, 0, 0},
        {"all cookies too small", {10,11}, 2, {1,2,3}, 3, 0},
        {"all satisfied", {1,2,3}, 3, {3,3,3}, 3, 3},
        {"exact match", {5}, 1, {5}, 1, 1},
    };
    int tc = (int)(sizeof(tests) / sizeof(tests[0]));
    int passed = 0;
    for (int i = 0; i < tc; i++) {
        int got = findContentChildren(tests[i].g, tests[i].gn, tests[i].s, tests[i].sn);
        if (got == tests[i].expected) {
            passed++;
            printf("  Test %d (%s): PASS\n", i + 1, tests[i].label);
        } else {
            printf("  Test %d (%s): FAIL\n", i + 1, tests[i].label);
            printf("    Expected: %d, Got: %d\n", tests[i].expected, got);
        }
    }
    printf("\n  %d/%d passed\n", passed, tc);
    printf("============================================================\n\n");
    return passed == tc ? 0 : 1;
}
