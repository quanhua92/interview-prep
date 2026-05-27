/*
 * P467: Unique Substrings in Wraparound String [PREMIUM] (Medium)
 * https://leetcode.com/problems/unique-substrings-in-wraparound-string/
 * Topics: String, Dynamic Programming
 *
 * We define the string base to be the infinite wraparound string of "abcdefghijklmnopqrstuvwxyz", so base will look like this:
 * Given a string s, return the number of unique non-empty substrings of s are present in base.
 * Example 1:
 *     Input: s = "a"
 *     Output: 1
 *     Explanation: Only the substring "a" of s is in base.
 *
 * Example 2:
 *     Input: s = "cac"
 *     Output: 2
 *     Explanation: There are two substrings ("a", "c") of s in base.
 *
 * Example 3:
 *     Input: s = "zab"
 *     Output: 6
 *     Explanation: There are six substrings ("z", "a", "b", "za", "ab", and "zab") of s in base.
 *
 * Constraints:
 *     - 1 <= s.length <= 105
 *     - s consists of lowercase English letters.
 *
 * Hint: One possible solution might be to consider allocating an array size of 26 for each character in the alphabet. (Credits to @r2ysxu)
 *
 * Template (python3):
 *     class Solution:
 *         def findSubstringInWraproundString(self, s: str) -> int:
 */

#include "io.h"
#include <string.h>

int findSubstringInWraproundString(const char *s) {
    int max_len[26] = {0};
    int curr = 0;
    int len = (int)strlen(s);
    for (int i = 0; i < len; i++) {
        if (i > 0 && ((s[i] - s[i - 1] == 1) || (s[i - 1] - s[i] == 25))) {
            curr++;
        } else {
            curr = 1;
        }
        int idx = (unsigned char)s[i] - 'a';
        if (curr > max_len[idx]) max_len[idx] = curr;
    }
    int result = 0;
    for (int i = 0; i < 26; i++) result += max_len[i];
    return result;
}

int main(void) {
    char *s = read_line();
    write_int(findSubstringInWraproundString(s));
    free(s);
    return 0;
}
