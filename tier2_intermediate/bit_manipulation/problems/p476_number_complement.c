/*
 * P476: Number Complement [PREMIUM] (Easy)
 * https://leetcode.com/problems/number-complement/
 * Topics: Bit Manipulation
 * 
 * The complement of an integer is the integer you get when you flip all the 0's to 1's and all the 1's to 0's in its binary representation.
 * Given an integer num, return its complement.
 * Example 2:
 * Note: This question is the same as 1009: https://leetcode.com/problems/complement-of-base-10-integer/
 * Example 1:
 *     Input: num = 5
 *     Output: 2
 *     Explanation: The binary representation of 5 is 101 (no leading zero bits), and its complement is 010. So you need to output 2.
 * 
 * Example 2:
 *     Input: num = 1
 *     Output: 0
 *     Explanation: The binary representation of 1 is 1 (no leading zero bits), and its complement is 0. So you need to output 0.
 * 
 * Constraints:
 *     - 1 <= num < 231
 * 
 * Template (python3):
 *     class Solution:
 *         def findComplement(self, num: int) -> int:
 */
#include "ctest.h"

static int findComplement(int num) {
    abort();
}

int main(void) {
    (void)th_print_arr;
    (void)th_arr_eq;

    struct { const char *label; int input; int expected; } tests[] = {
        {"example 1", 5, 2},
        {"example 2", 1, 0},
        {"power of two", 2, 1},
        {"1000 flips to 0111", 8, 7},
        {"all ones flips to zero", 15, 0},
        {"large power of two", 1 << 30, (1 << 30) - 1},
    };

    int n = (int)(sizeof(tests) / sizeof(tests[0]));
    int passed = 0;

    printf("\n============================================================\n");
    printf("  476. Number Complement\n");
    printf("============================================================\n");

    for (int i = 0; i < n; i++) {
        int got = findComplement(tests[i].input);
        if (got == tests[i].expected) {
            passed++;
            printf("  Test %d (%s): PASS\n", i + 1, tests[i].label);
        } else {
            printf("  Test %d (%s): FAIL\n", i + 1, tests[i].label);
            printf("    Expected: %d\n    Got:      %d\n", tests[i].expected, got);
        }
    }

    printf("\n  %d/%d passed\n", passed, n);
    printf("============================================================\n\n");

    return passed == n ? 0 : 1;
}
