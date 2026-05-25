/*
 * P338: Counting Bits (Easy)
 * https://leetcode.com/problems/counting-bits/
 * Topics: Dynamic Programming, Bit Manipulation
 * 
 * Given an integer n, return an array ans of length n + 1 such that for each i (0 <= i <= n), ans[i] is the number of 1's in the binary representation of i.
 * 
 * Example 1:
 *     Input: n = 2
 *     Output: [0,1,1]
 *     Explanation:
 *     0 --> 0
 *     1 --> 1
 *     2 --> 10
 * 
 * Example 2:
 *     Input: n = 5
 *     Output: [0,1,1,2,1,2]
 *     Explanation:
 *     0 --> 0
 *     1 --> 1
 *     2 --> 10
 *     3 --> 11
 *     4 --> 100
 *     5 --> 101
 * 
 * Constraints:
 *     - 0 <= n <= 105
 * 
 * Hints:
 *     - You should make use of what you have produced already.
 *     - Divide the numbers in ranges like [2-3], [4-7], [8-15] and so on. And try to generate new range from previous.
 *     - Or does the odd/even status of the number help you in calculating the number of 1s?
 * 
 * Template (python3):
 *     class Solution:
 *         def countBits(self, n: int) -> List[int]:
 * 
 * Hint: DP approach: ans[i] = ans[i >> 1] + (i & 1).
 */
#include "ctest.h"
#include <stdlib.h>

static int *countBits(int n, int *returnSize) {
    /* TODO: Implement */
    return 0;
}

int main(void) {
    struct { const char *label; int input; int expected[17]; int expected_n; } tests[] = {
        {"example 1", 2, {0, 1, 1}, 3},
        {"example 2", 5, {0, 1, 1, 2, 1, 2}, 6},
        {"zero", 0, {0}, 1},
        {"one", 1, {0, 1}, 2},
        {"power-of-2 minus 1", 7, {0, 1, 1, 2, 1, 2, 2, 3}, 8},
        {"four bits all", 15, {0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4}, 16},
        {"power of 2", 16, {0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 1}, 17},
    };

    int n = (int)(sizeof(tests) / sizeof(tests[0]));
    int passed = 0;

    printf("\n============================================================\n");
    printf("  338. Counting Bits\n");
    printf("============================================================\n");

    for (int i = 0; i < n; i++) {
        int retSize = 0;
        int *got = countBits(tests[i].input, &retSize);
        if (th_arr_eq(got, retSize, tests[i].expected, tests[i].expected_n)) {
            passed++;
            printf("  Test %d (%s): PASS\n", i + 1, tests[i].label);
        } else {
            printf("  Test %d (%s): FAIL\n", i + 1, tests[i].label);
            printf("    Expected: ");
            th_print_arr(tests[i].expected, tests[i].expected_n);
            printf("\n    Got:      ");
            if (got) th_print_arr(got, retSize);
            else printf("NULL");
            printf("\n");
        }
        free(got);
    }

    printf("\n  %d/%d passed\n", passed, n);
    printf("============================================================\n\n");

    return passed == n ? 0 : 1;
}
