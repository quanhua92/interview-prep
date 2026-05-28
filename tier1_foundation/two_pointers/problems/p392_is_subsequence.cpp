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


#include "io.h"
#include <string>

bool isSubsequence(const std::string &s, const std::string &t)
{
    abort();
}

int main(void)
{
    std::string s = read_line();
    std::string t = read_line();
    write_bool(isSubsequence(s, t));
    return 0;
}
