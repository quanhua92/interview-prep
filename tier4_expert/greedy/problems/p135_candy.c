/*
 * P135: Candy (Hard)
 * https://leetcode.com/problems/candy/
 * Topics: Array, Greedy
 * 
 * There are n children standing in a line. Each child is assigned a rating value given in the integer array ratings.
 * You are giving candies to these children subjected to the following requirements:
 * Return the minimum number of candies you need to have to distribute the candies to the children.
 * 
 * Example 1:
 *     Input: ratings = [1,0,2]
 *     Output: 5
 *     Explanation: You can allocate to the first, second and third child with 2, 1, 2 candies respectively.
 * 
 * Example 2:
 *     Input: ratings = [1,2,2]
 *     Output: 4
 *     Explanation: You can allocate to the first, second and third child with 1, 2, 1 candies respectively.
 *     The third child gets 1 candy because it satisfies the above two conditions.
 * 
 * Constraints:
 *     - n == ratings.length
 *     - 1 <= n <= 2 * 104
 *     - 0 <= ratings[i] <= 2 * 104
 * 
 * Template (python3):
 *     class Solution:
 *         def candy(self, ratings: List[int]) -> int:
 * 
 * Hint: Two-pass greedy: left-to-right then right-to-left, taking the max of both passes.
 */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#include "ctest.h"
#pragma GCC diagnostic pop
#include <stdlib.h>

int candy(int *ratings, int ratingsSize) {
    abort();
}

int main(void) {
    printf("\n============================================================\n");
    printf("  135. Candy\n");
    printf("============================================================\n");
    struct { const char *label; int ratings[10]; int n; int expected; } tests[] = {
        {"example 1", {1,0,2}, 3, 5},
        {"example 2", {1,2,2}, 3, 4},
        {"decreasing then flat", {1,3,2,2,1}, 5, 7},
        {"single child", {1}, 1, 1},
        {"all same ratings", {2,2,2,2}, 4, 4},
        {"strictly increasing", {1,2,3,4}, 4, 10},
        {"strictly decreasing", {4,3,2,1}, 4, 10},
        {"increase then drop", {1,3,4,5,2}, 5, 11},
    };
    int tc = (int)(sizeof(tests) / sizeof(tests[0]));
    int passed = 0;
    for (int i = 0; i < tc; i++) {
        int got = candy(tests[i].ratings, tests[i].n);
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
