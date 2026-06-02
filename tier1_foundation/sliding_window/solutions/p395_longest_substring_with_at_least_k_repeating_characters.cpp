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
 *     - 1 <= s.length <= 10^4
 *     - s consists of only lowercase English letters.
 *     - 1 <= k <= 10^5
 *
 * Template (python3):
 *     class Solution:
 *         def longestSubstring(self, s: str, k: int) -> int:
 */

#include "io.h"
#include <string>

int longestSubstring(const std::string &s, int k)
{
    int max_len = 0;
    int len = (int)s.size();
    for (int t = 1; t <= 26; t++) {
        int freq[26] = {};
        int left = 0, unique = 0, at_least_k = 0;
        for (int right = 0; right < len; right++) {
            int idx = s[right] - 'a';
            freq[idx]++;
            if (freq[idx] == 1) unique++;
            if (freq[idx] == k) at_least_k++;
            while (unique > t) {
                int lidx = s[left] - 'a';
                if (freq[lidx] == k) at_least_k--;
                freq[lidx]--;
                if (freq[lidx] == 0) unique--;
                left++;
            }
            if (unique == t && at_least_k == t) {
                int cur = right - left + 1;
                if (cur > max_len) max_len = cur;
            }
        }
    }
    return max_len;
}

int main(void)
{
    std::string s = read_line();
    std::vector<int> k_line = read_ints();
    int k = k_line[0];
    write_int(longestSubstring(s, k));
    return 0;
}
