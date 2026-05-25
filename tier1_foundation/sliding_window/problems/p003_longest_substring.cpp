/*
 * P3: Longest Substring Without Repeating Characters (Medium)
 * https://leetcode.com/problems/longest-substring-without-repeating-characters/
 * Topics: Hash Table, String, Sliding Window
 * 
 * Given a string s, find the length of the longest substring without duplicate characters.
 * 
 * Example 1:
 *     Input: s = "abcabcbb"
 *     Output: 3
 *     Explanation: The answer is "abc", with the length of 3.
 * 
 * Example 2:
 *     Input: s = "bbbbb"
 *     Output: 1
 *     Explanation: The answer is "b", with the length of 1.
 * 
 * Example 3:
 *     Input: s = "pwwkew"
 *     Output: 3
 *     Explanation: The answer is "wke", with the length of 3.
 *     Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.
 * 
 * Constraints:
 *     - 0 <= s.length <= 5 * 104
 *     - s consists of English letters, digits, symbols and spaces.
 * 
 * Hints:
 *     - Generate all possible substrings & check for each substring if it's valid and keep updating maxLen accordingly.
 * 
 * Template (python3):
 *     class Solution:
 *         def lengthOfLongestSubstring(self, s: str) -> int:
 * 
 * Hint: Use a hash map to track the last index of each character.
 */
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <unordered_map>

static int lengthOfLongestSubstring(const std::string &s)
{
    /* TODO: Implement */
    return 0;
}

int main()
{
    struct { const char *label; const char *input; int expected; } tests[] = {
        {"example 1",                          "abcabcbb", 3},
        {"example 2",                          "bbbbb",    1},
        {"example 3",                          "pwwkew",   3},
        {"empty string",                       "",         0},
        {"single character",                   "a",        1},
        {"single space",                       " ",        1},
        {"two unique chars",                   "au",       2},
        {"reset from duplicate after unique prefix", "dvdf", 3},
        {"char seen before current window",    "tmmzuxt",  5},
    };
    int n = (int)(sizeof(tests) / sizeof(tests[0]));
    int passed = 0;
    for (int i = 0; i < n; i++) {
        int got = lengthOfLongestSubstring(tests[i].input);
        if (got == tests[i].expected) {
            printf("  Test %d (%s): PASS\n", i + 1, tests[i].label);
            passed++;
        } else {
            printf("  Test %d (%s): FAIL\n", i + 1, tests[i].label);
            printf("    Expected: %d\n    Got: %d\n", tests[i].expected, got);
        }
    }
    printf("\n  %d/%d passed\n", passed, n);
    return passed == n ? 0 : 1;
}
