/*
 * P438: Find All Anagrams in a String (Medium)
 * https://leetcode.com/problems/find-all-anagrams-in-a-string/
 * Topics: Hash Table, String, Sliding Window
 * 
 * Given two strings s and p, return an array of all the start indices of p's anagrams in s. You may return the answer in any order.
 * 
 * Example 1:
 *     Input: s = "cbaebabacd", p = "abc"
 *     Output: [0,6]
 *     Explanation:
 *     The substring with start index = 0 is "cba", which is an anagram of "abc".
 *     The substring with start index = 6 is "bac", which is an anagram of "abc".
 * 
 * Example 2:
 *     Input: s = "abab", p = "ab"
 *     Output: [0,1,2]
 *     Explanation:
 *     The substring with start index = 0 is "ab", which is an anagram of "ab".
 *     The substring with start index = 1 is "ba", which is an anagram of "ab".
 *     The substring with start index = 2 is "ab", which is an anagram of "ab".
 * 
 * Constraints:
 *     - 1 <= s.length, p.length <= 3 * 104
 *     - s and p consist of lowercase English letters.
 * 
 * Template (python3):
 *     class Solution:
 *         def findAnagrams(self, s: str, p: str) -> List[int]:
 * 
 * Hint: Use a sliding window with frequency counters to compare against pattern.
 */
#include "ctest.h"
#include <string.h>

static int *findAnagrams(const char *s, const char *p, int *returnSize)
{
    abort();
}

int main(void)
{
    struct {
        const char *label;
        const char *s;
        const char *p;
        int expected[30];
        int expected_n;
    } tests[] = {
        {"example 1",           "cbaebabacd", "abc", {0, 6}, 2},
        {"example 2",           "abab",       "ab",  {0, 1, 2}, 3},
        {"no anagrams",         "af",         "bf",  {}, 0},
        {"exact match single",  "abc",        "abc", {0}, 1},
        {"all same chars",      "aaaaaaaaaa", "aa",  {0, 1, 2, 3, 4, 5, 6, 7, 8}, 9},
        {"overlapping anagrams","abacbabc",   "abc", {1, 2, 3, 5}, 4},
        {"pattern longer than string", "a",   "aa",  {}, 0},
    };
    int n = (int)(sizeof(tests) / sizeof(tests[0]));
    int passed = 0;
    for (int i = 0; i < n; i++) {
        int ret_size = 0;
        int *got = findAnagrams(tests[i].s, tests[i].p, &ret_size);
        if (th_arr_eq(got, ret_size, tests[i].expected, tests[i].expected_n)) {
            printf("  Test %d (%s): PASS\n", i + 1, tests[i].label);
            passed++;
        } else {
            printf("  Test %d (%s): FAIL\n", i + 1, tests[i].label);
            printf("    Expected: "); th_print_arr(tests[i].expected, tests[i].expected_n);
            printf("\n    Got:      "); th_print_arr(got, ret_size);
            printf("\n");
        }
        free(got);
    }
    printf("\n  %d/%d passed\n", passed, n);
    return passed == n ? 0 : 1;
}
