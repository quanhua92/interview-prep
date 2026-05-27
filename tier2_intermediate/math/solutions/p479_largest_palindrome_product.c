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


#include "io.h"
#include <stdlib.h>

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
    int n;
    int *vals = read_ints(&n);
    write_int(largestPalindrome(vals[0]));
    free(vals);
    return 0;
}
