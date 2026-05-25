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
    if (n == 1) return 9;
    long long upper = 1;
    long long lower = 1;
    for (int i = 0; i < n; i++) { upper *= 10; lower *= 10; }
    upper -= 1;
    lower /= 10;
    for (long long left = upper; left >= lower; left--) {
        long long palindrome = left;
        long long tmp = left;
        while (tmp > 0) {
            palindrome = palindrome * 10 + tmp % 10;
            tmp /= 10;
        }
        for (long long right = upper; right >= lower; right--) {
            if (right * right < palindrome) break;
            if (palindrome % right == 0) return (int)(palindrome % 1337);
        }
    }
    return 0;
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
