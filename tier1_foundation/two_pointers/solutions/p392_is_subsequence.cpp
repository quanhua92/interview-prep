/*
 * P392: Is Subsequence [PREMIUM] (Easy)
 * https://leetcode.com/problems/is-subsequence/
 * Topics: Two Pointers, String, Dynamic Programming
 *
 * Given two strings s and t, return true if s is a subsequence of t, or false otherwise.
 * A subsequence of a string is a new string that is formed from the original string by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters. (i.e., "ace" is a subsequence of "abcde" while "aec" is not).
 * Example 1:
 *     Input: s = "abc", t = "ahbgdc"
 *     Output: true
 *
 * Example 2:
 *     Input: s = "axc", t = "ahbgdc"
 *     Output: false
 *
 * Constraints:
 *     - 0 <= s.length <= 100
 *     - 0 <= t.length <= 104
 *     - s and t consist only of lowercase English letters.
 *
 * Template (python3):
 *     class Solution:
 *         def isSubsequence(self, s: str, t: str) -> bool:
 */


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#include "cpptest.h"
#pragma GCC diagnostic pop
#include <string>

bool isSubsequence(const std::string &s, const std::string &t)
{
    int i = 0;
    for (char c : t) {
        if (i < (int)s.size() && s[i] == c) i++;
    }
    return i == (int)s.size();
}

int main(void)
{
    struct {
        const char *label;
        const char *s;
        const char *t;
        bool expected;
    } tests[] = {
        {"example 1",              "abc",   "ahbgdc", true},
        {"example 2",              "axc",   "ahbgdc", false},
        {"empty s is subsequence", "",      "ahbgdc", true},
        {"s equals t",             "abc",   "abc",    true},
        {"s longer than t",        "abcd",  "abc",    false},
        {"single char not found",  "z",     "aaaaa",  false},
    };
    int n_tests = sizeof(tests) / sizeof(tests[0]);

    printf("\n============================================================\n");
    printf("  392. Is Subsequence\n");
    printf("============================================================\n");
    int passed = 0;
    for (int i = 0; i < n_tests; i++) {
        bool got = isSubsequence(tests[i].s, tests[i].t);
        if (got == tests[i].expected) {
            passed++;
            printf("  Test %d (%s): PASS\n", i + 1, tests[i].label);
        } else {
            printf("  Test %d (%s): FAIL\n", i + 1, tests[i].label);
            printf("    Expected: %s\n    Got:      %s\n", tests[i].expected ? "true" : "false", got ? "true" : "false");
        }
    }
    printf("\n  %d/%d passed\n", passed, n_tests);
    printf("============================================================\n\n");
    return passed == n_tests ? 0 : 1;
}
