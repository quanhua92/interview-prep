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
 *     - n is representing an integer in the range [1, 1018 - 1].
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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#include "ctest.h"
#pragma GCC diagnostic pop
#include <stdlib.h>
#include <string.h>

typedef long long ll;

ll pow10(int n) {
    /* TODO: Implement */
    return 0;
}

ll str_to_ll(const char *s) {
    /* TODO: Implement */
    return 0;
}

void ll_to_str(ll v, char *buf) {
    /* TODO: Implement */
    return 0;
}

ll make_palindrome(ll prefix, int total_len) {
    /* TODO: Implement */
    return 0;
}

char *nearestPalindromic(const char *n) {
    /* TODO: Implement */
    return 0;
}

int main(void) {
    printf("\n============================================================\n");
    printf("  564. Find the Closest Palindrome\n");
    printf("============================================================\n");
    struct { const char *label; const char *input; const char *expected; } tests[] = {
        {"example 1", "123", "121"},
        {"example 2", "1", "0"},
        {"edge at 10", "10", "9"},
        {"two same digits", "99", "101"},
        {"power of 10", "100", "99"},
        {"four digit", "1283", "1331"},
    };
    int tc = (int)(sizeof(tests) / sizeof(tests[0]));
    int passed = 0;
    for (int i = 0; i < tc; i++) {
        char *got = nearestPalindromic(tests[i].input);
        if (strcmp(got, tests[i].expected) == 0) {
            passed++;
            printf("  Test %d (%s): PASS\n", i + 1, tests[i].label);
        } else {
            printf("  Test %d (%s): FAIL\n", i + 1, tests[i].label);
            printf("    Expected: %s, Got: %s\n", tests[i].expected, got);
        }
    }
    printf("\n  %d/%d passed\n", passed, tc);
    printf("============================================================\n\n");
    return passed == tc ? 0 : 1;
}
