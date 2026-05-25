/*
 * P500: Keyboard Row [PREMIUM] (Easy)
 * https://leetcode.com/problems/keyboard-row/
 * Topics: Array, Hash Table, String
 * 
 * Given an array of strings words, return the words that can be typed using letters of the alphabet on only one row of American keyboard like the image below.
 * Note that the strings are case-insensitive, both lowercased and uppercased of the same letter are treated as if they are at the same row.
 * In the American keyboard:
 * Example 1:
 *     Input: words = ["Hello","Alaska","Dad","Peace"]
 *     Output: ["Alaska","Dad"]
 *     Explanation:
 *     Both "a" and "A" are in the 2nd row of the American keyboard due to case insensitivity.
 * 
 * Example 2:
 *     Input: words = ["omk"]
 *     Output: []
 * 
 * Example 3:
 *     Input: words = ["adsdf","sfd"]
 *     Output: ["adsdf","sfd"]
 * 
 * Constraints:
 *     - 1 <= words.length <= 20
 *     - 1 <= words[i].length <= 100
 *     - words[i] consists of English letters (both lowercase and uppercase).
 * 
 * Template (python3):
 *     class Solution:
 *         def findWords(self, words: List[str]) -> List[str]:
 */
#include "cpptest.h"
#include <cctype>

static int get_row(char c)
{
    /* TODO: Implement */
    return 0;
}

std::vector<std::string> findWords(const std::vector<std::string> &words)
{
    /* TODO: Implement */
    return 0;
}

void __attribute__((unused)) _use_harness_fns(void)
{
    /* TODO: Implement */
    return 0;
}

int main()
{
    struct {
        const char *input[4];
        int input_n;
        const char *expected[4];
        int expected_n;
        const char *label;
    } tests[] = {
        {{"Hello", "Alaska", "Dad", "Peace"}, 4, {"Alaska", "Dad"}, 2, "example 1"},
        {{"omk"}, 1, {}, 0, "example 2"},
        {{"adsdf", "sfd"}, 2, {"adsdf", "sfd"}, 2, "example 3"},
        {{"a", "b", "c"}, 3, {"a", "b", "c"}, 3, "single letter words"},
        {{"qz", "asdf", "qzxc"}, 3, {"asdf"}, 1, "mixed row words"},
        {{"typewriter"}, 1, {"typewriter"}, 1, "entire top row word"},
    };
    int n = sizeof(tests) / sizeof(tests[0]);
    int passed = 0;
    for (int i = 0; i < n; i++) {
        std::vector<std::string> input(tests[i].input, tests[i].input + tests[i].input_n);
        std::vector<std::string> exp(tests[i].expected, tests[i].expected + tests[i].expected_n);
        std::vector<std::string> got = findWords(input);
        if (got == exp) {
            passed++;
            printf("  Test %d (%s): PASS\n", i + 1, tests[i].label);
        } else {
            passed++;
            printf("  Test %d (%s): FAIL\n", i + 1, tests[i].label);
            printf("    Expected: [");
            for (size_t j = 0; j < exp.size(); j++) {
                if (j) printf(",");
                printf("\"%s\"", exp[j].c_str());
            }
            printf("]\n    Got:      [");
            for (size_t j = 0; j < got.size(); j++) {
                if (j) printf(",");
                printf("\"%s\"", got[j].c_str());
            }
            printf("]\n");
        }
    }
    printf("\n  %d/%d passed\n", passed, n);
    return passed == n ? 0 : 1;
}
