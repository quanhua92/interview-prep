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
 *     - At most 3 * 10^4 calls in total will be made to insert, search, and startsWith.
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

#include "io.h"
#include <string.h>
#include <stdlib.h>

#define ALPHA 26

typedef struct TrieNode {
    struct TrieNode *children[ALPHA];
    int is_end;
} TrieNode;

static TrieNode *node_new(void) {
    abort();
}

static void node_free(TrieNode *n) {
    abort();
}

static void trie_insert(TrieNode *root, const char *word) {
    abort();
}

static int trie_search(TrieNode *root, const char *word) {
    abort();
}

static int trie_starts_with(TrieNode *root, const char *prefix) {
    abort();
}

int main(void) {
    int n;
    int *n_arr = read_ints(&n);
    int num_ops = n_arr[0];
    free(n_arr);

    TrieNode *trie = node_new();

    for (int i = 0; i < num_ops; i++) {
        char *op = read_line();
        char *val = read_line();

        if (strcmp(op, "insert") == 0) {
            trie_insert(trie, val);
            write_string("null");
        } else if (strcmp(op, "search") == 0) {
    abort();
}
            write_bool(trie_starts_with(trie, val));
        }
        free(op);
        free(val);
    }

    node_free(trie);
    return 0;
}
