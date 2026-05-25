/*
 * P424: Longest Repeating Character Replacement (Medium)
 * https://leetcode.com/problems/longest-repeating-character-replacement/
 * Topics: Hash Table, String, Sliding Window
 *
 * You are given a string s and an integer k. You can choose any character of the string and change it to any other uppercase English character. You can perform this operation at most k times.
 * Return the length of the longest substring containing the same letter you can get after performing the above operations.
 *
 * Example 1:
 *     Input: s = "ABAB", k = 2
 *     Output: 4
 *     Explanation: Replace the two 'A's with two 'B's or vice versa.
 *
 * Example 2:
 *     Input: s = "AABABBA", k = 1
 *     Output: 4
 *     Explanation: Replace the one 'A' in the middle with 'B' and form "AABBBBA".
 *     The substring "BBBB" has the longest repeating letters, which is 4.
 *     There may exists other ways to achieve this answer too.
 *
 * Constraints:
 *     - 1 <= s.length <= 105
 *     - s consists of only uppercase English letters.
 *     - 0 <= k <= s.length
 *
 * Template (python3):
 *     class Solution:
 *         def characterReplacement(self, s: str, k: int) -> int:
 *
 * Hint: Freq map + max_freq tracker, window valid when len - max_freq <= k. Left only moves right.
 */


#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <algorithm>

static int characterReplacement(const std::string &s, int k)
{
    int freq[26] = {0};
    int max_freq = 0, left = 0, max_len = 0;
    for (int i = 0; i < (int)s.size(); i++) {
        int idx = s[i] - 'A';
        freq[idx]++;
        max_freq = std::max(max_freq, freq[idx]);
        while ((i - left + 1) - max_freq > k) {
            freq[s[left] - 'A']--;
            left++;
        }
        max_len = std::max(max_len, i - left + 1);
    }
    return max_len;
}

int main()
{
    struct { const char *label; const char *input; int k; int expected; } tests[] = {
        {"example 1",              "ABAB",    2, 4},
        {"example 2",              "AABABBA", 1, 4},
        {"no changes needed",      "AAAA",    0, 4},
        {"all unique",             "ABCDE",   1, 2},
        {"single char, k=0",       "A",       0, 1},
        {"single char, k > len",   "A",       5, 1},
        {"no changes, partial run","AAAB",    0, 3},
        {"change middle B to A",   "ABAA",    2, 4},
    };
    int n = (int)(sizeof(tests) / sizeof(tests[0]));
    int passed = 0;
    for (int i = 0; i < n; i++) {
        int got = characterReplacement(tests[i].input, tests[i].k);
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
