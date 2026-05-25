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
#include "ctest.h"
#include <string.h>

int findSubstringInWraproundString(const char *s) {
    abort();
}

int main(void) {
    struct { const char *label; const char *s; int expected; } tests[] = {
        {"example 1", "a", 1},
        {"example 2", "cac", 2},
        {"example 3", "zab", 6},
        {"all same chars only a in wraparound", "aaaaa", 1},
        {"wraparound chain length 8", "zabcdefg", 36},
        {"full alphabet", "abcdefghijklmnopqrstuvwxyz", 351},
    };
    int n = (int)(sizeof(tests) / sizeof(tests[0]));
    int passed = 0;
    for (int i = 0; i < n; i++) {
        int got = findSubstringInWraproundString(tests[i].s);
        if (got == tests[i].expected) {
            passed++;
            printf("  Test %d (%s): PASS\n", i + 1, tests[i].label);
        } else {
            printf("  Test %d (%s): FAIL (expected %d, got %d)\n", i + 1, tests[i].label, tests[i].expected, got);
        }
    }
    printf("\n  %d/%d passed\n", passed, n);
    return passed == n ? 0 : 1;
}
