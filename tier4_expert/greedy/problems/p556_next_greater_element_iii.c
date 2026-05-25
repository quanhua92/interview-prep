/*
 * P556: Next Greater Element III [PREMIUM] (Medium)
 * https://leetcode.com/problems/next-greater-element-iii/
 * Topics: Math, Two Pointers, String
 * 
 * Given a positive integer n, find the smallest integer which has exactly the same digits existing in the integer n and is greater in value than n. If no such positive integer exists, return -1.
 * Note that the returned integer should fit in 32-bit integer, if there is a valid answer but it does not fit in 32-bit integer, return -1.
 * Example 1:
 *     Input: n = 12
 *     Output: 21
 * 
 * Example 2:
 *     Input: n = 21
 *     Output: -1
 * 
 * Constraints:
 *     - 1 <= n <= 231 - 1
 * 
 * Template (python3):
 *     class Solution:
 *         def nextGreaterElement(self, n: int) -> int:
 */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#include "ctest.h"
#pragma GCC diagnostic pop
#include <stdlib.h>
#include <string.h>

int nextGreaterElement(int n) {
    /* TODO: Implement */
    return 0;
}

int main(void) {
    printf("\n============================================================\n");
    printf("  556. Next Greater Element III\n");
    printf("============================================================\n");
    struct { const char *label; int input; int expected; } tests[] = {
        {"example 1", 12, 21},
        {"example 2", 21, -1},
        {"single digit", 1, -1},
        {"all same digits", 11, -1},
        {"classic example", 230241, 230412},
        {"max 32-bit int", 2147483647, -1},
    };
    int tc = (int)(sizeof(tests) / sizeof(tests[0]));
    int passed = 0;
    for (int i = 0; i < tc; i++) {
        int got = nextGreaterElement(tests[i].input);
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
