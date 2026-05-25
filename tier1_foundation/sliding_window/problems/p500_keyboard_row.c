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
#include "ctest.h"
#include <ctype.h>

static int get_row(char c)
{
    /* TODO: Implement */
    return 0;
}

int findWords(const char *words[], int n, const char *result[])
{
    /* TODO: Implement */
    return 0;
}

void __attribute__((unused)) _use_harness_fns(void)
{
    /* TODO: Implement */
    return 0;
}

int main(void)
{
    {
        const char *words[] = {"Hello", "Alaska", "Dad", "Peace"};
        const char *expected[] = {"Alaska", "Dad"};
        const char *result[4];
        int got_n = findWords(words, 4, result);
        int exp_n = 2;
        int pass = got_n == exp_n;
        if (pass) {
            for (int i = 0; i < exp_n; i++) {
                if (strcmp(result[i], expected[i]) != 0) { pass = 0; break; }
            }
        }
        printf("  Test 1 (example 1): %s\n", pass ? "PASS" : "FAIL");
    }
    {
        const char *words[] = {"omk"};
        const char *result[1];
        int got_n = findWords(words, 1, result);
        printf("  Test 2 (example 2): %s\n", got_n == 0 ? "PASS" : "FAIL");
    }
    {
        const char *words[] = {"adsdf", "sfd"};
        const char *expected[] = {"adsdf", "sfd"};
        const char *result[2];
        int got_n = findWords(words, 2, result);
        int pass = got_n == 2;
        if (pass) {
            for (int i = 0; i < 2; i++) {
                if (strcmp(result[i], expected[i]) != 0) { pass = 0; break; }
            }
        }
        printf("  Test 3 (example 3): %s\n", pass ? "PASS" : "FAIL");
    }
    {
        const char *words[] = {"a", "b", "c"};
        const char *expected[] = {"a", "b", "c"};
        const char *result[3];
        int got_n = findWords(words, 3, result);
        int pass = got_n == 3;
        if (pass) {
            for (int i = 0; i < 3; i++) {
                if (strcmp(result[i], expected[i]) != 0) { pass = 0; break; }
            }
        }
        printf("  Test 4 (single letter words): %s\n", pass ? "PASS" : "FAIL");
    }
    {
        const char *words[] = {"qz", "asdf", "qzxc"};
        const char *result[3];
        int got_n = findWords(words, 3, result);
        int pass = got_n == 1 && strcmp(result[0], "asdf") == 0;
        printf("  Test 5 (mixed row words): %s\n", pass ? "PASS" : "FAIL");
    }
    {
        const char *words[] = {"typewriter"};
        const char *result[1];
        int got_n = findWords(words, 1, result);
        int pass = got_n == 1 && strcmp(result[0], "typewriter") == 0;
        printf("  Test 6 (entire top row word): %s\n", pass ? "PASS" : "FAIL");
    }
    return 0;
}
