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


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static int detectCapitalUse(const char *word)
{
    int upper = 0, first_upper = isupper((unsigned char)word[0]);
    for (int i = 0; word[i]; i++)
        if (isupper((unsigned char)word[i]))
            upper++;
    int len = (int)strlen(word);
    return upper == len || upper == 0 || (first_upper && upper == 1);
}

int main(void)
{
    struct { const char *label; const char *input; int expected; } tests[] = {
        {"example 1",       "USA",      1},
        {"example 2",       "FlaG",     0},
        {"single lowercase","a",        1},
        {"single uppercase","Z",        1},
        {"all lowercase",   "leetcode", 1},
        {"title case",      "Google",   1},
        {"lowercase then uppercase", "mL", 0},
    };
    int n = (int)(sizeof(tests) / sizeof(tests[0]));
    int passed = 0;
    for (int i = 0; i < n; i++) {
        int got = detectCapitalUse(tests[i].input);
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
