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

#include "io.h"
#include <stdlib.h>
#include <string.h>

static int *findAnagrams(const char *s, const char *p, int *returnSize)
{
    int slen = (int)strlen(s);
    int plen = (int)strlen(p);
    int *result = malloc(slen * sizeof(int));
    *returnSize = 0;

    if (plen > slen)
        return result;

    int pf[26] = {0}, sf[26] = {0};
    for (int i = 0; i < plen; i++) {
        pf[p[i] - 'a']++;
        sf[s[i] - 'a']++;
    }

    if (memcmp(pf, sf, sizeof(pf)) == 0)
        result[(*returnSize)++] = 0;

    for (int i = plen; i < slen; i++) {
        sf[s[i] - 'a']++;
        sf[s[i - plen] - 'a']--;
        if (memcmp(pf, sf, sizeof(pf)) == 0)
            result[(*returnSize)++] = i - plen + 1;
    }

    return result;
}

int main(void)
{
    char *s = read_line();
    char *p = read_line();
    int returnSize;
    int *result = findAnagrams(s, p, &returnSize);
    write_ints(result, returnSize);
    free(s);
    free(p);
    free(result);
    return 0;
}
