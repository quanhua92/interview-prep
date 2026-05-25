/*
 * P395: Longest Substring with At Least K Repeating Characters [PREMIUM] (Medium)
 * https://leetcode.com/problems/longest-substring-with-at-least-k-repeating-characters/
 * Topics: Hash Table, String, Divide and Conquer, Sliding Window
 * 
 * Given a string s and an integer k, return the length of the longest substring of s such that the frequency of each character in this substring is greater than or equal to k.
 * if no such substring exists, return 0.
 * Example 1:
 *     Input: s = "aaabb", k = 3
 *     Output: 3
 *     Explanation: The longest substring is "aaa", as 'a' is repeated 3 times.
 * 
 * Example 2:
 *     Input: s = "ababbc", k = 2
 *     Output: 5
 *     Explanation: The longest substring is "ababb", as 'a' is repeated 2 times and 'b' is repeated 3 times.
 * 
 * Constraints:
 *     - 1 <= s.length <= 104
 *     - s consists of only lowercase English letters.
 *     - 1 <= k <= 105
 * 
 * Template (python3):
 *     class Solution:
 *         def longestSubstring(self, s: str, k: int) -> int:
 */
#include "cpptest.h"

int longestSubstring(const std::string &s, int k)
{
    /* TODO: Implement */
    return 0;
}

void __attribute__((unused)) _use_harness_fns(void)
{
    /* TODO: Implement */
    return 0;
}

int main()
{
    struct { const char *s; int k; int expected; const char *label; } tests[] = {
        {"aaabb", 3, 3, "example 1"},
        {"ababbc", 2, 5, "example 2"},
        {"ababacb", 3, 0, "no valid substring"},
        {"a", 1, 1, "single char k=1"},
        {"a", 2, 0, "single char k>1"},
        {"bbaaacbd", 3, 3, "multiple runs"},
    };
    int n = sizeof(tests) / sizeof(tests[0]);
    int passed = 0;
    for (int i = 0; i < n; i++) {
        int got = longestSubstring(tests[i].s, tests[i].k);
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
