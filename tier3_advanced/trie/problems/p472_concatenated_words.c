/*
 * P472: Concatenated Words [PREMIUM] (Hard)
 * https://leetcode.com/problems/concatenated-words/
 * Topics: Array, String, Dynamic Programming, Depth-First Search, Trie, Sorting
 * 
 * Given an array of strings words (without duplicates), return all the concatenated words in the given list of words.
 * A concatenated word is defined as a string that is comprised entirely of at least two shorter words (not necessarily distinct) in the given array.
 * Example 1:
 *     Input: words = ["cat","cats","catsdogcats","dog","dogcatsdog","hippopotamuses","rat","ratcatdogcat"]
 *     Output: ["catsdogcats","dogcatsdog","ratcatdogcat"]
 *     Explanation: "catsdogcats" can be concatenated by "cats", "dog" and "cats";
 *     "dogcatsdog" can be concatenated by "dog", "cats" and "dog";
 *     "ratcatdogcat" can be concatenated by "rat", "cat", "dog" and "cat".
 * 
 * Example 2:
 *     Input: words = ["cat","dog","catdog"]
 *     Output: ["catdog"]
 * 
 * Constraints:
 *     - 1 <= words.length <= 104
 *     - 1 <= words[i].length <= 30
 *     - words[i] consists of only lowercase English letters.
 *     - All the strings of words are unique.
 *     - 1 <= sum(words[i].length) <= 105
 * 
 * Template (python3):
 *     class Solution:
 *         def findAllConcatenatedWordsInADict(self, words: List[str]) -> List[str]:
 */
#include "ctest.h"
#include <string.h>
#include <stdlib.h>

#define ALPHA 26
#define MAX_WORDS 10001
#define MAX_WORD_LEN 31

typedef struct TrieNode {
    struct TrieNode *children[ALPHA];
    int is_end;
} TrieNode;

static TrieNode *node_new(void) {
    /* TODO: Implement */
    return 0;
}

static void node_free(TrieNode *n) {
    /* TODO: Implement */
    return 0;
}

static void trie_insert(TrieNode *root, const char *word) {
    /* TODO: Implement */
    return 0;
}

static int can_concatenate(TrieNode *root, const char *word, int start, int count) {
    /* TODO: Implement */
    return 0;
}

static int cmp_str(const void *a, const void *b) {
    /* TODO: Implement */
    return 0;
}

static int cmp_len(const void *a, const void *b) {
    /* TODO: Implement */
    return 0;
}

typedef struct {
    const char *label;
    const char *words[20];
    int nw;
    const char *expected[20];
    int ne;
} CwTC;

int main(void) {
    (void)th_print_arr;
    (void)th_arr_eq;

    CwTC tests[] = {
        {"example 1",
         {"cat","cats","catsdogcats","dog","dogcatsdog","hippopotamuses","rat","ratcatdogcat"}, 8,
         {"catsdogcats","dogcatsdog","ratcatdogcat"}, 3},
        {"example 2",
         {"cat","dog","catdog"}, 3,
         {"catdog"}, 1},
        {"word from duplicate parts",
         {"cat","catcat"}, 2,
         {"catcat"}, 1},
        {"no concatenated words",
         {"a","b","c"}, 3,
         {""}, 0},
        {"deep concatenation chain",
         {"a","aa","aaaa"}, 3,
         {"aa","aaaa"}, 2},
        {"self-similar concatenation",
         {"ab","abab"}, 2,
         {"abab"}, 1},
    };

    int n = (int)(sizeof(tests) / sizeof(tests[0]));
    int passed = 0;

    printf("\n============================================================\n");
    printf("  472. Concatenated Words\n");
    printf("============================================================\n");

    for (int t = 0; t < n; t++) {
        const char *sorted[20];
        int nw = tests[t].nw;
        for (int i = 0; i < nw; i++) sorted[i] = tests[t].words[i];
        qsort(sorted, nw, sizeof(char*), cmp_len);

        TrieNode *root = node_new();
        char *result[20];
        int rc = 0;

        for (int i = 0; i < nw; i++) {
            if (can_concatenate(root, sorted[i], 0, 0))
                result[rc++] = (char *)sorted[i];
            trie_insert(root, sorted[i]);
        }

        qsort(result, rc, sizeof(char*), cmp_str);

        int ok = (rc == tests[t].ne);
        if (ok) {
            for (int i = 0; i < rc; i++) {
                if (strcmp(result[i], tests[t].expected[i]) != 0) { ok = 0; break; }
            }
        }
        node_free(root);

        if (ok) {
            passed++;
            printf("  Test %d (%s): PASS\n", t + 1, tests[t].label);
        } else {
            printf("  Test %d (%s): FAIL\n", t + 1, tests[t].label);
            printf("    Expected %d words, got %d\n", tests[t].ne, rc);
        }
    }

    printf("\n  %d/%d passed\n", passed, n);
    printf("============================================================\n\n");
    return passed == n ? 0 : 1;
}
