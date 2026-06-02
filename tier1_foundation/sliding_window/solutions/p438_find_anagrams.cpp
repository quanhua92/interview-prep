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
 *     - 1 <= s.length, p.length <= 3 * 10^4
 *     - s and p consist of lowercase English letters.
 *
 * Template (python3):
 *     class Solution:
 *         def findAnagrams(self, s: str, p: str) -> List[int]:
 *
 * Hint: Use a sliding window with frequency counters to compare against pattern.
 */

#include "io.h"
#include <array>
#include <string>
#include <vector>

static std::vector<int> findAnagrams(const std::string &s, const std::string &p)
{
    std::vector<int> result;
    int slen = (int)s.size(), plen = (int)p.size();
    if (plen > slen) return result;

    std::array<int, 26> pf{}, sf{};
    for (int i = 0; i < plen; i++) {
        pf[p[i] - 'a']++;
        sf[s[i] - 'a']++;
    }

    if (pf == sf) result.push_back(0);

    for (int i = plen; i < slen; i++) {
        sf[s[i] - 'a']++;
        sf[s[i - plen] - 'a']--;
        if (pf == sf) result.push_back(i - plen + 1);
    }

    return result;
}

int main(void)
{
    std::string s = read_line();
    std::string p = read_line();
    write_ints(findAnagrams(s, p));
    return 0;
}
