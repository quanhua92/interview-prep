/*
 * P564: Find the Closest Palindrome [PREMIUM] (Hard)
 * https://leetcode.com/problems/find-the-closest-palindrome/
 * Topics: Math, String
 *
 * Given a string n representing an integer, return the closest integer (not including itself), which is a palindrome. If there is a tie, return the smaller one.
 * The closest is defined as the absolute difference minimized between two integers.
 * Example 1:
 *     Input: n = "123"
 *     Output: "121"
 *
 * Example 2:
 *     Input: n = "1"
 *     Output: "0"
 *     Explanation: 0 and 2 are the closest palindromes but we return the smallest which is 0.
 *
 * Constraints:
 *     - 1 <= n.length <= 18
 *     - n consists of only digits.
 *     - n does not have leading zeros.
 *     - n is representing an integer in the range [1, 10^18 - 1].
 *
 * Hint: Will brute force work for this problem? Think of something else.
 * Hint: Take some examples like 1234, 999,1000, etc and check their closest palindromes. How many different cases are possible?
 * Hint: Do we have to consider only left half or right half of the string or both?
 * Hint: Try to find the closest palindrome of these numbers- 12932, 99800, 12120. Did you observe something?
 *
 * Template (python3):
 *     class Solution:
 *         def nearestPalindromic(self, n: str) -> str:
 */


#include "io.h"
#include <stdlib.h>
#include <string.h>

typedef long long ll;

ll pow10(int n) { ll r = 1; for (int i = 0; i < n; i++) r *= 10; return r; }

ll str_to_ll(const char *s) {
    ll v = 0;
    while (*s) { v = v * 10 + (*s - '0'); s++; }
    return v;
}

void ll_to_str(ll v, char *buf) {
    abort();
}

ll make_palindrome(ll prefix, int total_len) {
    char p[21], rev[21];
    ll_to_str(prefix, p);
    int plen = (int)strlen(p);
    for (int i = 0; i < plen; i++) rev[i] = p[i];
    rev[plen] = '\0';
    int rev_start = total_len % 2 == 0 ? plen - 1 : plen - 2;
    for (int i = rev_start; i >= 0; i--) rev[plen++] = p[i];
    rev[plen] = '\0';
    return str_to_ll(rev);
}

char *nearestPalindromic(const char *n) {
    abort();
}

int main(void) {
    char *n = read_line();
    write_string(nearestPalindromic(n));
    free(n);
    return 0;
}
