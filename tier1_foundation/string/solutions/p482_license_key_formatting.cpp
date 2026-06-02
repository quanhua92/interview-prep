/*
 * P482: License Key Formatting [PREMIUM] (Easy)
 * https://leetcode.com/problems/license-key-formatting/
 * Topics: String
 *
 * You are given a license key represented as a string s that consists of only alphanumeric characters and dashes. The string is separated into n + 1 groups by n dashes. You are also given an integer k.
 * We want to reformat the string s such that each group contains exactly k characters, except for the first group, which could be shorter than k but still must contain at least one character. Furthermore, there must be a dash inserted between two groups, and you should convert all lowercase letters to uppercase.
 * Return the reformatted license key.
 * Example 1:
 *     Input: s = "5F3Z-2e-9-w", k = 4
 *     Output: "5F3Z-2E9W"
 *     Explanation: The string s has been split into two parts, each part has 4 characters.
 *     Note that the two extra dashes are not needed and can be removed.
 *
 * Example 2:
 *     Input: s = "2-5g-3-J", k = 2
 *     Output: "2-5G-3J"
 *     Explanation: The string s has been split into three parts, each part has 2 characters except the first part as it could be shorter as mentioned above.
 *
 * Constraints:
 *     - 1 <= s.length <= 10^5
 *     - s consists of English letters, digits, and dashes '-'.
 *     - 1 <= k <= 10^4
 *
 * Template (python3):
 *     class Solution:
 *         def licenseKeyFormatting(self, s: str, k: int) -> str:
 */

#include "io.h"
#include <cctype>
#include <string>

std::string licenseKeyFormatting(const std::string &s, int k)
{
    std::string cleaned;
    for (char c : s) {
        if (c != '-') cleaned += (char)toupper((unsigned char)c);
    }
    if (cleaned.empty()) return "";
    int first_len = (int)cleaned.size() % k;
    std::string result;
    if (first_len > 0) {
        result = cleaned.substr(0, first_len);
    }
    for (int i = first_len; i < (int)cleaned.size(); i += k) {
        if (!result.empty()) result += '-';
        result += cleaned.substr(i, k);
    }
    return result;
}

int main(void)
{
    std::string s = read_line();
    std::vector<int> k_arr = read_ints();
    int k = k_arr[0];
    write_string(licenseKeyFormatting(s, k));
    return 0;
}
