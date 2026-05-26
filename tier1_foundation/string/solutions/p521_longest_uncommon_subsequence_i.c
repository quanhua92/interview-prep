/*
 * P521: Longest Uncommon Subsequence I [PREMIUM] (Easy)
 * https://leetcode.com/problems/longest-uncommon-subsequence-i/
 * Topics: String
 *
 * Given two strings a and b, return the length of the longest uncommon subsequence between a and b. If no such uncommon subsequence exists, return -1.
 * An uncommon subsequence between two strings is a string that is a subsequence of exactly one of them.
 * Example 1:
 *     Input: a = "aba", b = "cdc"
 *     Output: 3
 *     Explanation: One longest uncommon subsequence is "aba" because "aba" is a subsequence of "aba" but not "cdc".
 *     Note that "cdc" is also a longest uncommon subsequence.
 *
 * Example 2:
 *     Input: a = "aaa", b = "bbb"
 *     Output: 3
 *     Explanation: The longest uncommon subsequences are "aaa" and "bbb".
 *
 * Example 3:
 *     Input: a = "aaa", b = "aaa"
 *     Output: -1
 *     Explanation: Every subsequence of string a is also a subsequence of string b. Similarly, every subsequence of string b is also a subsequence of string a. So the answer would be -1.
 *
 * Constraints:
 *     - 1 <= a.length, b.length <= 100
 *     - a and b consist of lower-case English letters.
 *
 * Hint: Think very simple.
 * Hint: If <code>a == b</code>, the answer is -1.
 * Hint: Otherwise, the answer is the string <code>a</code> or the string <code>b</code>.
 *
 * Template (python3):
 *     class Solution:
 *         def findLUSlength(self, a: str, b: str) -> int:
 */


#include "ctest.h"

int findLUSlength(const char *a, const char *b)
{
    int la = (int)strlen(a);
    int lb = (int)strlen(b);
    if (strcmp(a, b) == 0) return -1;
    return la > lb ? la : lb;
}

void __attribute__((unused)) _use_harness_fns(void)
{
    (void)th_print_arr;
    (void)th_arr_eq;
}

int main(void)
{
    struct {
        const char *a;
        const char *b;
        int expected;
        const char *label;
    } tests[] = {
        {"aba", "cdc", 3, "example 1"},
        {"aaa", "bbb", 3, "example 2"},
        {"aaa", "aaa", -1, "example 3"},
        {"a", "b", 1, "single char different"},
        {"a", "aa", 2, "one is subsequence of other"},
        {"abc", "abcde", 5, "one longer than other"},
    };
    int n = sizeof(tests) / sizeof(tests[0]);
    int passed = 0;
    for (int i = 0; i < n; i++) {
        int got = findLUSlength(tests[i].a, tests[i].b);
        if (got == tests[i].expected) {
            passed++;
            printf("  Test %d (%s): PASS\n", i + 1, tests[i].label);
        } else {
            printf("  Test %d (%s): FAIL\n", i + 1, tests[i].label);
            printf("    Expected: %d\n    Got:      %d\n", tests[i].expected, got);
        }
    }
    printf("\n  %d/%d passed\n", passed, n);
    return passed == n ? 0 : 1;
}
