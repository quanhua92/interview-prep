/*
 * P472: Concatenated Words [PREMIUM] (Hard)
 * https://leetcode.com/problems/concatenated-words/
 * Topics: Array, String, Dynamic Programming, Depth-First Search, Trie, Sorting
 *
 * Given an array of strings words (without duplicates), return all the concatenated words in the given list of words.
 * A concatenated word is defined as a string that is comprised entirely of at least two shorter words (not necessarily distinct) in the given array.
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

#include "io.h"
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
    TrieNode *n = calloc(1, sizeof(TrieNode));
    return n;
}

static void node_free(TrieNode *n) {
    if (!n) return;
    for (int i = 0; i < ALPHA; i++)
        node_free(n->children[i]);
    free(n);
}

static void trie_insert(TrieNode *root, const char *word) {
    TrieNode *cur = root;
    for (int i = 0; word[i]; i++) {
        int idx = word[i] - 'a';
        if (!cur->children[idx])
            cur->children[idx] = node_new();
        cur = cur->children[idx];
    }
    cur->is_end = 1;
}

static int memo[31];

static int can_concatenate(TrieNode *root, const char *word, int start, int count) {
    if (memo[start] >= 0) return memo[start];
    TrieNode *cur = root;
    for (int i = start; word[i]; i++) {
        int idx = word[i] - 'a';
        if (!cur->children[idx]) { memo[start] = 0; return 0; }
        cur = cur->children[idx];
        if (cur->is_end) {
            int len = (int)strlen(word);
            if (i == len - 1) {
                int r = count >= 1;
                memo[start] = r;
                return r;
            }
            if (can_concatenate(root, word, i + 1, count + 1)) {
                memo[start] = 1;
                return 1;
            }
        }
    }
    memo[start] = 0;
    return 0;
}

static int cmp_str(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

static int cmp_len(const void *a, const void *b) {
    return strlen(*(const char **)a) - strlen(*(const char **)b);
}

int main(void) {
    int n;
    int *arr = read_ints(&n);
    int nw = arr[0];
    free(arr);

    char **words = malloc(nw * sizeof(char *));
    for (int i = 0; i < nw; i++) {
        words[i] = read_line();
    }

    qsort(words, nw, sizeof(char*), cmp_len);

    TrieNode *root = node_new();
    char **result = malloc(nw * sizeof(char *));
    int rc = 0;

    for (int i = 0; i < nw; i++) {
        memset(memo, -1, sizeof(memo));
        if (can_concatenate(root, words[i], 0, 0))
            result[rc++] = words[i];
        trie_insert(root, words[i]);
    }

    qsort(result, rc, sizeof(char*), cmp_str);

    write_int(rc);
    for (int i = 0; i < rc; i++) {
        write_string(result[i]);
    }

    for (int i = 0; i < nw; i++) free(words[i]);
    free(words);
    free(result);
    node_free(root);
    return 0;
}
