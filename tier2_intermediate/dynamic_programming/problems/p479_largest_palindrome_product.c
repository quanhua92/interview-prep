/*
 * P479: Largest Palindrome Product [PREMIUM] (Hard)
 * https://leetcode.com/problems/largest-palindrome-product/
 * Topics: Math, Enumeration
 * 
 * Given an integer n, return the largest palindromic integer that can be represented as the product of two n-digits integers. Since the answer can be very large, return it modulo 1337.
 * Example 1:
 *     Input: n = 2
 *     Output: 987
 *     Explanation: 99 x 91 = 9009, 9009 % 1337 = 987
 * 
 * Example 2:
 *     Input: n = 1
 *     Output: 9
 * 
 * Constraints:
 *     - 1 <= n <= 8
 * 
 * Template (python3):
 *     class Solution:
 *         def largestPalindrome(self, n: int) -> int:
 */
#include "ctest.h"

int largestPalindrome(int n) {
    abort();
}

int main(void) {
    struct { const char *label; int n; int expected; } tests[] = {
        {"example 1", 2, 987},
        {"example 2", 1, 9},
        {"3 digits", 3, 123},
        {"4 digits", 4, 597},
        {"8 digits (max n)", 8, 475},
    };
    int tn = (int)(sizeof(tests) / sizeof(tests[0]));
    int passed = 0;
    for (int i = 0; i < tn; i++) {
        int got = largestPalindrome(tests[i].n);
        if (got == tests[i].expected) {
            passed++;
            printf("  Test %d (%s): PASS\n", i + 1, tests[i].label);
        } else {
            printf("  Test %d (%s): FAIL (expected %d, got %d)\n", i + 1, tests[i].label, tests[i].expected, got);
        }
    }
    printf("\n  %d/%d passed\n", passed, tn);
    return passed == tn ? 0 : 1;
}
