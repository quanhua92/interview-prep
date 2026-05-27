/*
 * P524: Longest Word in Dictionary through Deleting [PREMIUM] (Medium)
 * https://leetcode.com/problems/longest-word-in-dictionary-through-deleting/
 * Topics: Array, Two Pointers, String, Sorting
 *
 * Given a string s and a string array dictionary, return the longest string in the dictionary that can be formed by deleting some of the given string characters. If there is more than one possible result, return the longest word with the smallest lexicographical order. If there is no possible result, return the empty string.
 * Example 1:
 *     Input: s = "abpcplea", dictionary = ["ale","apple","monkey","plea"]
 *     Output: "apple"
 *
 * Example 2:
 *     Input: s = "abpcplea", dictionary = ["a","b","c"]
 *     Output: "a"
 *
 * Constraints:
 *     - 1 <= s.length <= 1000
 *     - 1 <= dictionary.length <= 1000
 *     - 1 <= dictionary[i].length <= 1000
 *     - s and dictionary[i] consist of lowercase English letters.
 *
 * Template (python3):
 *     class Solution:
 *         def findLongestWord(self, s: str, dictionary: List[str]) -> str:
 */

#include "io.h"
#include <stdlib.h>
#include <string.h>

static int is_subseq(const char *word, const char *target) {
    int i = 0;
    int wlen = (int)strlen(word);
    for (int j = 0; target[j] && i < wlen; j++) {
        if (word[i] == target[j]) i++;
    }
    return i == wlen;
}

static char *findLongestWord(const char *s, const char **dict, int dict_size) {
    const char *best = "";
    for (int i = 0; i < dict_size; i++) {
        if (is_subseq(dict[i], s)) {
            int wlen = (int)strlen(dict[i]);
            int blen = (int)strlen(best);
            if (wlen > blen || (wlen == blen && strcmp(dict[i], best) < 0)) {
                best = dict[i];
            }
        }
    }
    char *result = malloc(strlen(best) + 1);
    strcpy(result, best);
    return result;
}

int main(void)
{
    char *s = read_line();
    int dict_size_arr_len;
    int *dict_size_arr = read_ints(&dict_size_arr_len);
    int dict_size = dict_size_arr[0];
    free(dict_size_arr);
    const char **dict = malloc(dict_size * sizeof(const char *));
    for (int i = 0; i < dict_size; i++) {
        dict[i] = read_line();
    }
    char *result = findLongestWord(s, dict, dict_size);
    write_string(result);
    free(s);
    free(result);
    for (int i = 0; i < dict_size; i++) free((void *)dict[i]);
    free(dict);
    return 0;
}
