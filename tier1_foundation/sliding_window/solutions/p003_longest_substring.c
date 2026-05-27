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

#include "io.h"
#include <stdlib.h>
#include <string.h>

static int lengthOfLongestSubstring(const char *s)
{
    int last[128];
    for (int i = 0; i < 128; i++) last[i] = -1;
    int left = 0, max_len = 0;
    for (int i = 0; s[i]; i++) {
        unsigned char c = (unsigned char)s[i];
        if (last[c] >= left)
            left = last[c] + 1;
        last[c] = i;
        if (i - left + 1 > max_len)
            max_len = i - left + 1;
    }
    return max_len;
}

int main(void)
{
    char *s = read_line();
    int result = lengthOfLongestSubstring(s);
    write_int(result);
    free(s);
    return 0;
}
