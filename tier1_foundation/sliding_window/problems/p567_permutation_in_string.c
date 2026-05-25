/*
 * P567: Permutation in String [PREMIUM] (Medium)
 * https://leetcode.com/problems/permutation-in-string/
 * Topics: Hash Table, Two Pointers, String, Sliding Window
 * 
 * Given two strings s1 and s2, return true if s2 contains a permutation of s1, or false otherwise.
 * In other words, return true if one of s1's permutations is the substring of s2.
 * Example 1:
 *     Input: s1 = "ab", s2 = "eidbaooo"
 *     Output: true
 *     Explanation: s2 contains one permutation of s1 ("ba").
 * 
 * Example 2:
 *     Input: s1 = "ab", s2 = "eidboaoo"
 *     Output: false
 * 
 * Constraints:
 *     - 1 <= s1.length, s2.length <= 104
 *     - s1 and s2 consist of lowercase English letters.
 * 
 * Hint: Obviously, brute force will result in TLE. Think of something else.
 * Hint: How will you check whether one string is a permutation of another string?
 * Hint: One way is to sort the string and then compare. But, Is there a better way?
 * Hint: If one string is a permutation of another string then they must have one common metric. What is that?
 * Hint: Both strings must have same character frequencies, if  one is permutation of another. Which data structure should be used to store frequencies?
 * Hint: What about hash table?  An array of size 26?
 * 
 * Template (python3):
 *     class Solution:
 *         def checkInclusion(self, s1: str, s2: str) -> bool:
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int checkInclusion(const char *s1, const char *s2)
{
    /* TODO: Implement */
    return 0;
}

int main(void)
{
    struct { const char *label; const char *s1; const char *s2; int expected; } tests[] = {
        {"example 1",             "ab", "eidbaooo",       1},
        {"example 2",             "ab", "eidboaoo",       0},
        {"single char match",     "a",  "a",              1},
        {"permutation at end",    "adc","dcda",           1},
        {"no match large string", "abc","ccccbbbbaaaa",   0},
        {"s1 longer than s2",     "ab", "a",              0},
    };
    int n = (int)(sizeof(tests) / sizeof(tests[0]));
    int passed = 0;
    for (int i = 0; i < n; i++) {
        int got = checkInclusion(tests[i].s1, tests[i].s2);
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
