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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int is_subseq(const char *word, const char *target) {
    abort();
}

static char *findLongestWord(const char *s, const char **dict, int dict_size) {
    abort();
}

int main(void) {
    int passed = 0, total = 6;
    printf("\n============================================================\n");
    printf("  524. Longest Word in Dictionary through Deleting\n");
    printf("============================================================\n");

    {
        const char *dict[] = {"ale", "apple", "monkey", "plea"};
        char *got = findLongestWord("abpcplea", dict, 4);
        if (strcmp(got, "apple") == 0) { passed++; printf("  Test 1 (example 1): PASS\n"); }
        else { printf("  Test 1 (example 1): FAIL\n  Expected: apple, Got: %s\n", got); }
        free(got);
    }
    {
        const char *dict[] = {"a", "b", "c"};
        char *got = findLongestWord("abpcplea", dict, 3);
        if (strcmp(got, "a") == 0) { passed++; printf("  Test 2 (example 2): PASS\n"); }
        else { printf("  Test 2 (example 2): FAIL\n  Expected: a, Got: %s\n", got); }
        free(got);
    }
    {
        char *got = findLongestWord("abpcplea", NULL, 0);
        if (strcmp(got, "") == 0) { passed++; printf("  Test 3 (empty dictionary): PASS\n"); }
        else { printf("  Test 3 (empty dictionary): FAIL\n  Expected: (empty), Got: %s\n", got); }
        free(got);
    }
    {
        const char *dict[] = {"xyz", "def"};
        char *got = findLongestWord("abc", dict, 2);
        if (strcmp(got, "") == 0) { passed++; printf("  Test 4 (no match): PASS\n"); }
        else { printf("  Test 4 (no match): FAIL\n  Expected: (empty), Got: %s\n", got); }
        free(got);
    }
    {
        const char *dict[] = {"apple", "ale", "abpple"};
        char *got = findLongestWord("abpcplea", dict, 3);
        if (strcmp(got, "abpple") == 0) { passed++; printf("  Test 5 (same length lexicographical tie): PASS\n"); }
        else { printf("  Test 5 (same length lexicographical tie): FAIL\n  Expected: abpple, Got: %s\n", got); }
        free(got);
    }
    {
        const char *dict[] = {"a", "aa", "aaa"};
        char *got = findLongestWord("a", dict, 3);
        if (strcmp(got, "a") == 0) { passed++; printf("  Test 6 (longer dict words than s): PASS\n"); }
        else { printf("  Test 6 (longer dict words than s): FAIL\n  Expected: a, Got: %s\n", got); }
        free(got);
    }

    printf("\n  %d/%d passed\n", passed, total);
    printf("============================================================\n\n");
    return passed == total ? 0 : 1;
}
