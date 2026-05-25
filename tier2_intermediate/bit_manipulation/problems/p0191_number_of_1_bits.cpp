/*
 * P191: Number of 1 Bits (Easy)
 * https://leetcode.com/problems/number-of-1-bits/
 * Topics: Divide and Conquer, Bit Manipulation
 * 
 * Given a positive integer n, write a function that returns the number of set bits in its binary representation (also known as the Hamming weight).
 * 
 * Example 1:
 *     Input: n = 11
 *     Output: 3
 *     Explanation:
 *     The input binary string 1011 has a total of three set bits.
 * 
 * Example 2:
 *     Input: n = 128
 *     Output: 1
 *     Explanation:
 *     The input binary string 10000000 has a total of one set bit.
 * 
 * Example 3:
 *     Input: n = 2147483645
 *     Output: 30
 *     Explanation:
 *     The input binary string 1111111111111111111111111111101 has a total of thirty set bits.
 * 
 * Constraints:
 *     - 1 <= n <= 231 - 1
 * 
 * Template (python3):
 *     class Solution:
 *         def hammingWeight(self, n: int) -> int:
 * 
 * Hint: Use Brian Kernighan's algorithm: n &= (n - 1) clears the lowest set bit.
 */
#include "cpptest.h"
#include <cstdint>

static int hammingWeight(uint32_t n) {
    abort();
}

int main() {
    (void)print_arr;

    struct { const char *label; uint32_t input; int expected; } tests[] = {
        {"example 1", 0b00000000000000000000000000001011u, 3},
        {"power of two", 0b00000000000000000000000010000000u, 1},
        {"leetcode example 3", 2147483645u, 30},
        {"zero", 0u, 0},
        {"single bit", 1u, 1},
        {"alternating bits", 0x55555555u, 16},
        {"max value all bits set", 0x7FFFFFFFu, 31},
    };

    int n = (int)(sizeof(tests) / sizeof(tests[0]));
    int passed = 0;

    printf("\n============================================================\n");
    printf("  191. Number of 1 Bits\n");
    printf("============================================================\n");

    for (int i = 0; i < n; i++) {
        int got = hammingWeight(tests[i].input);
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
