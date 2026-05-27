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


#include "io.h"
#include <ctype.h>
#include <string.h>

static int get_row(char c)
{
    c = (char)tolower((unsigned char)c);
    const char *rows[] = {
        "qwertyuiop",
        "asdfghjkl",
        "zxcvbnm",
    };
    for (int r = 0; r < 3; r++) {
        if (strchr(rows[r], c)) return r;
    }
    return -1;
}

int main(void)
{
    int cnt;
    int *header = read_ints(&cnt);
    int n = header[0];
    free(header);

    for (int i = 0; i < n; i++) {
        char *word = read_line();
        if (word[0] == '\0') continue;
        int row = get_row(word[0]);
        int valid = 1;
        for (int j = 1; word[j]; j++) {
            if (get_row(word[j]) != row) {
                valid = 0;
                break;
            }
        }
        if (valid) {
            write_string(word);
        }
        free(word);
    }
    return 0;
}
