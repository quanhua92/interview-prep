/*
 * P520: Detect Capital [PREMIUM] (Easy)
 * https://leetcode.com/problems/detect-capital/
 * Topics: String
 * 
 * We define the usage of capitals in a word to be right when one of the following cases holds:
 * Given a string word, return true if the usage of capitals in it is right.
 * Example 1:
 *     Input: word = "USA"
 *     Output: true
 * 
 * Example 2:
 *     Input: word = "FlaG"
 *     Output: false
 * 
 * Constraints:
 *     - 1 <= word.length <= 100
 *     - word consists of lowercase and uppercase English letters.
 * 
 * Template (python3):
 *     class Solution:
 *         def detectCapitalUse(self, word: str) -> bool:
 */
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <string>

static bool detectCapitalUse(const std::string &word)
{
    abort();
}

int main()
{
    struct { const char *label; const char *input; bool expected; } tests[] = {
        {"example 1",       "USA",      true},
        {"example 2",       "FlaG",     false},
        {"single lowercase","a",        true},
        {"single uppercase","Z",        true},
        {"all lowercase",   "leetcode", true},
        {"title case",      "Google",   true},
        {"lowercase then uppercase", "mL", false},
    };
    int n = (int)(sizeof(tests) / sizeof(tests[0]));
    int passed = 0;
    for (int i = 0; i < n; i++) {
        bool got = detectCapitalUse(tests[i].input);
        if (got == tests[i].expected) {
            printf("  Test %d (%s): PASS\n", i + 1, tests[i].label);
            passed++;
        } else {
            printf("  Test %d (%s): FAIL\n", i + 1, tests[i].label);
            printf("    Expected: %s\n    Got: %s\n", tests[i].expected ? "true" : "false", got ? "true" : "false");
        }
    }
    printf("\n  %d/%d passed\n", passed, n);
    return passed == n ? 0 : 1;
}
