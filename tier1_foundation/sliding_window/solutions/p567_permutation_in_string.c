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
 *     - 1 <= s1.length, s2.length <= 10^4
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

#include "io.h"
#include <stdlib.h>
#include <string.h>

static int checkInclusion(const char *s1, const char *s2)
{
    int n1 = (int)strlen(s1), n2 = (int)strlen(s2);
    if (n1 > n2) return 0;

    int f1[26] = {0}, f2[26] = {0};
    for (int i = 0; i < n1; i++) {
        f1[s1[i] - 'a']++;
        f2[s2[i] - 'a']++;
    }
    if (memcmp(f1, f2, sizeof(f1)) == 0) return 1;

    for (int i = n1; i < n2; i++) {
        f2[s2[i] - 'a']++;
        f2[s2[i - n1] - 'a']--;
        if (memcmp(f1, f2, sizeof(f1)) == 0) return 1;
    }
    return 0;
}

int main(void)
{
    char *s1 = read_line();
    char *s2 = read_line();
    int result = checkInclusion(s1, s2);
    write_bool(result);
    free(s1);
    free(s2);
    return 0;
}
