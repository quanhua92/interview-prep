/*
 * P208: Implement Trie (Prefix Tree) (Medium)
 * https://leetcode.com/problems/implement-trie-prefix-tree/
 * Topics: Hash Table, String, Design, Trie
 *
 * A trie (pronounced as "try") or prefix tree is a tree data structure used to efficiently store and retrieve keys in a dataset of strings. There are various applications of this data structure, such as autocomplete and spellchecker.
 * Implement the Trie class:
 *
 * Example 1:
 *     Input
 *     ["Trie", "insert", "search", "search", "startsWith", "insert", "search"]
 *     [[], ["apple"], ["apple"], ["app"], ["app"], ["app"], ["app"]]
 *     Output
 *     [null, null, true, false, true, null, true]
 *
 *     Explanation
 *     Trie trie = new Trie();
 *     trie.insert("apple");
 *     trie.search("apple");   // return True
 *     trie.search("app");     // return False
 *     trie.startsWith("app"); // return True
 *     trie.insert("app");
 *     trie.search("app");     // return True
 *
 * Constraints:
 *     - 1 <= word.length, prefix.length <= 2000
 *     - word and prefix consist only of lowercase English letters.
 *     - At most 3 * 104 calls in total will be made to insert, search, and startsWith.
 *
 * Template (python3):
 *     class Trie:
 *
 *         def __init__(self):
 *
 *
 *         def insert(self, word: str) -> None:
 *
 *
 *         def search(self, word: str) -> bool:
 *
 *
 *         def startsWith(self, prefix: str) -> bool:
 *
 *
 *
 *     # Your Trie object will be instantiated and called as such:
 *     # obj = Trie()
 *     # obj.insert(word)
 *     # param_2 = obj.search(word)
 *     # param_3 = obj.startsWith(prefix)
 *
 * Hint: Build a Trie class with insert, search, and starts_with methods.
 */


#include "ctest.h"
#include <string.h>

#define ALPHA 26

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

static int trie_search(TrieNode *root, const char *word) {
    TrieNode *cur = root;
    for (int i = 0; word[i]; i++) {
        int idx = word[i] - 'a';
        if (!cur->children[idx]) return 0;
        cur = cur->children[idx];
    }
    return cur->is_end;
}

static int trie_starts_with(TrieNode *root, const char *prefix) {
    TrieNode *cur = root;
    for (int i = 0; prefix[i]; i++) {
        int idx = prefix[i] - 'a';
        if (!cur->children[idx]) return 0;
        cur = cur->children[idx];
    }
    return 1;
}

typedef struct { const char *op; const char *val; int expected; } Op;

typedef struct {
    const char *label;
    const Op *ops;
    int nops;
} TriTC;

static const Op t0[] = {{"insert","apple",-1},{"search","apple",1},{"search","app",0},{"starts_with","app",1},{"insert","app",-1},{"search","app",1}};
static const Op t1[] = {{"insert","a",-1},{"search","a",1},{"search","b",0},{"starts_with","a",1},{"starts_with","b",0}};
static const Op t2[] = {{"insert","hello",-1},{"search","world",0},{"starts_with","world",0},{"search","hel",0},{"starts_with","hel",1}};
static const Op t3[] = {{"insert","a",-1},{"insert","ab",-1},{"insert","abc",-1},{"search","a",1},{"search","ab",1},{"search","abc",1},{"search","abcd",0},{"starts_with","ab",1},{"starts_with","abcd",0}};
static const Op t4[] = {{"insert","test",-1},{"insert","test",-1},{"search","test",1},{"starts_with","te",1}};

int main(void) {
    (void)th_print_arr;
    (void)th_arr_eq;

    TriTC tests[] = {
        {"full sequence", t0, 6},
        {"single character", t1, 5},
        {"search non-existent word/prefix", t2, 5},
        {"overlapping prefixes", t3, 9},
        {"duplicate insert", t4, 4},
    };

    int n = (int)(sizeof(tests) / sizeof(tests[0]));
    int passed = 0;

    printf("\n============================================================\n");
    printf("  208. Implement Trie (Prefix Tree)\n");
    printf("============================================================\n");

    for (int t = 0; t < n; t++) {
        TrieNode *trie = node_new();
        int ok = 1;
        for (int i = 0; i < tests[t].nops; i++) {
            int got = -1;
            if (strcmp(tests[t].ops[i].op, "insert") == 0) {
                trie_insert(trie, tests[t].ops[i].val);
                got = -1;
            } else if (strcmp(tests[t].ops[i].op, "search") == 0) {
                got = trie_search(trie, tests[t].ops[i].val);
            } else {
                got = trie_starts_with(trie, tests[t].ops[i].val);
            }
            if (got != tests[t].ops[i].expected) { ok = 0; break; }
        }
        if (ok) {
            passed++;
            printf("  Test %d (%s): PASS\n", t + 1, tests[t].label);
        } else {
            printf("  Test %d (%s): FAIL\n", t + 1, tests[t].label);
        }
        node_free(trie);
    }

    printf("\n  %d/%d passed\n", passed, n);
    printf("============================================================\n\n");
    return passed == n ? 0 : 1;
}
