/*
 * P516: Longest Palindromic Subsequence [PREMIUM] (Medium)
 * https://leetcode.com/problems/longest-palindromic-subsequence/
 * Topics: String, Dynamic Programming
 *
 * Given a string s, find the longest palindromic subsequence's length in s.
 * A subsequence is a sequence that can be derived from another sequence by deleting some or no elements without changing the order of the remaining elements.
 * Example 1:
 *     Input: s = "bbbab"
 *     Output: 4
 *     Explanation: One possible longest palindromic subsequence is "bbbb".
 *
 * Example 2:
 *     Input: s = "cbbd"
 *     Output: 2
 *     Explanation: One possible longest palindromic subsequence is "bb".
 *
 * Constraints:
 *     - 1 <= s.length <= 1000
 *     - s consists only of lowercase English letters.
 *
 * Template (python3):
 *     class Solution:
 *         def longestPalindromeSubseq(self, s: str) -> int:
 */


#include "cpptest.h"
#include <vector>
#include <cstring>
#include <algorithm>

int longestPalindromeSubseq(const std::string &s) {
    int n = (int)s.size();
    std::vector<std::vector<int>> dp(n, std::vector<int>(n, 0));
    for (int i = 0; i < n; i++) dp[i][i] = 1;
    for (int length = 2; length <= n; length++) {
        for (int i = 0; i <= n - length; i++) {
            int j = i + length - 1;
            if (s[i] == s[j]) {
                dp[i][j] = (length == 2) ? 2 : dp[i + 1][j - 1] + 2;
            } else {
                dp[i][j] = std::max(dp[i + 1][j], dp[i][j - 1]);
            }
        }
    }
    return n > 0 ? dp[0][n - 1] : 0;
}

int main() {
    struct { const char *label; std::string s; int expected; } tests[] = {
        {"example 1", "bbbab", 4},
        {"example 2", "cbbd", 2},
        {"single char", "a", 1},
        {"two same chars", "aa", 2},
        {"all distinct", "abcdef", 1},
        {"full palindrome", "aabbaa", 6},
    };
    int tn = sizeof(tests) / sizeof(tests[0]);
    int passed = 0;
    for (int i = 0; i < tn; i++) {
        int got = longestPalindromeSubseq(tests[i].s);
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
