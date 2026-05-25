/*
 * P475: Heaters [PREMIUM] (Medium)
 * https://leetcode.com/problems/heaters/
 * Topics: Array, Two Pointers, Binary Search, Sorting
 * 
 * Winter is coming! During the contest, your first job is to design a standard heater with a fixed warm radius to warm all the houses.
 * Every house can be warmed, as long as the house is within the heater's warm radius range.
 * Given the positions of houses and heaters on a horizontal line, return the minimum radius standard of heaters so that those heaters could cover all houses.
 * Notice that all the heaters follow your radius standard, and the warm radius will the same.
 * Example 1:
 *     Input: houses = [1,2,3], heaters = [2]
 *     Output: 1
 *     Explanation: The only heater was placed in the position 2, and if we use the radius 1 standard, then all the houses can be warmed.
 * 
 * Example 2:
 *     Input: houses = [1,2,3,4], heaters = [1,4]
 *     Output: 1
 *     Explanation: The two heaters were placed at positions 1 and 4. We need to use a radius 1 standard, then all the houses can be warmed.
 * 
 * Example 3:
 *     Input: houses = [1,5], heaters = [2]
 *     Output: 3
 * 
 * Constraints:
 *     - 1 <= houses.length, heaters.length <= 3 * 104
 *     - 1 <= houses[i], heaters[i] <= 109
 * 
 * Template (python3):
 *     class Solution:
 *         def findRadius(self, houses: List[int], heaters: List[int]) -> int:
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int cmp_int(const void *a, const void *b) {
    /* TODO: Implement */
    return 0;
}

static int abs_val(int x) {
    /* TODO: Implement */
    return 0;
}

int findRadius(const int *houses, int hn, const int *heaters, int heatn)
{
    /* TODO: Implement */
    return 0;
}

int main(void)
{
    struct {
        const char *label;
        int houses[8];
        int hn;
        int heaters[8];
        int heatn;
        int expected;
    } tests[] = {
        {"example 1",             {1, 2, 3},       3, {2},            1, 1},
        {"example 2",             {1, 2, 3, 4},    4, {1, 4},         2, 1},
        {"example 3",             {1, 5},          2, {2},            1, 3},
        {"house at heater position", {1},          1, {1},            1, 0},
        {"houses between heaters", {1, 2, 3, 4, 5, 6}, 6, {1, 6},    2, 2},
        {"single heater center",  {10, 20, 30},   3, {15},           1, 15},
        {"all houses before heaters", {1, 2, 3},  3, {4, 5, 6},     3, 3},
    };
    int n_tests = sizeof(tests) / sizeof(tests[0]);

    printf("\n============================================================\n");
    printf("  475. Heaters\n");
    printf("============================================================\n");
    int passed = 0;
    for (int i = 0; i < n_tests; i++) {
        int got = findRadius(tests[i].houses, tests[i].hn, tests[i].heaters, tests[i].heatn);
        if (got == tests[i].expected) {
            passed++;
            printf("  Test %d (%s): PASS\n", i + 1, tests[i].label);
        } else {
            printf("  Test %d (%s): FAIL\n", i + 1, tests[i].label);
            printf("    Expected: %d\n    Got:      %d\n", tests[i].expected, got);
        }
    }
    printf("\n  %d/%d passed\n", passed, n_tests);
    printf("============================================================\n\n");
    return passed == n_tests ? 0 : 1;
}
