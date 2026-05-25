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
 *     - 1 <= s.length <= 105
 *     - s consists of English letters, digits, and dashes '-'.
 *     - 1 <= k <= 104
 *
 * Template (python3):
 *     class Solution:
 *         def licenseKeyFormatting(self, s: str, k: int) -> str:
 */


#include "cpptest.h"
#include <cctype>

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

void __attribute__((unused)) _use_harness_fns(void)
{
    (void)print_arr;
}

int main()
{
    struct { const char *s; int k; const char *expected; const char *label; } tests[] = {
        {"5F3Z-2e-9-w", 4, "5F3Z-2E9W", "example 1"},
        {"2-5g-3-J", 2, "2-5G-3J", "example 2"},
        {"a", 1, "A", "single char no dash"},
        {"---", 3, "", "only dashes"},
        {"2-4A0r7-4k", 4, "24A0-R74K", "even groups no short first"},
        {"aa-aa-aa-aa-aa-aa", 1, "A-A-A-A-A-A-A-A-A-A-A-A", "k=1"},
    };
    int n = sizeof(tests) / sizeof(tests[0]);
    int passed = 0;
    for (int i = 0; i < n; i++) {
        std::string got = licenseKeyFormatting(tests[i].s, tests[i].k);
        if (got == tests[i].expected) {
            passed++;
            printf("  Test %d (%s): PASS\n", i + 1, tests[i].label);
        } else {
            printf("  Test %d (%s): FAIL\n", i + 1, tests[i].label);
            printf("    Expected: %s\n    Got:      %s\n", tests[i].expected, got.c_str());
        }
    }
    printf("\n  %d/%d passed\n", passed, n);
    return passed == n ? 0 : 1;
}
