/*
 * P211: Design Add and Search Words Data Structure (Medium)
 * https://leetcode.com/problems/design-add-and-search-words-data-structure/
 * Topics: String, Depth-First Search, Design, Trie
 *
 * Design a data structure that supports adding new words and finding if a string matches any previously added string.
 * Implement the WordDictionary class:
 * Example:
 *
 * Example 1:
 *     Input
 *     ["WordDictionary","addWord","addWord","addWord","search","search","search","search"]
 *     [[],["bad"],["dad"],["mad"],["pad"],["bad"],[".ad"],["b.."]]
 *     Output
 *     [null,null,null,null,false,true,true,true]
 *
 *     Explanation
 *     WordDictionary wordDictionary = new WordDictionary();
 *     wordDictionary.addWord("bad");
 *     wordDictionary.addWord("dad");
 *     wordDictionary.addWord("mad");
 *     wordDictionary.search("pad"); // return False
 *     wordDictionary.search("bad"); // return True
 *     wordDictionary.search(".ad"); // return True
 *     wordDictionary.search("b.."); // return True
 *
 * Constraints:
 *     - 1 <= word.length <= 25
 *     - word in addWord consists of lowercase English letters.
 *     - word in search consist of '.' or lowercase English letters.
 *     - There will be at most 2 dots in word for search queries.
 *     - At most 104 calls will be made to addWord and search.
 *
 * Hints:
 *     - You should be familiar with how a Trie works. If not, please work on this problem: <a href="https://leetcode.com/problems/implement-trie-prefix-tree/">Implement Trie (Prefix Tree)</a> first.
 *
 * Template (python3):
 *     class WordDictionary:
 *
 *         def __init__(self):
 *
 *
 *         def addWord(self, word: str) -> None:
 *
 *
 *         def search(self, word: str) -> bool:
 *
 *
 *
 *     # Your WordDictionary object will be instantiated and called as such:
 *     # obj = WordDictionary()
 *     # obj.addWord(word)
 *     # param_2 = obj.search(word)
 *
 * Hint: Build a Trie from the word list, then search with DFS handling '.' wildcards by trying all children.
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
    TrieNode *n = calloc(1, sizeof(TrieNode));
    return n;
}

static void node_free(TrieNode *n) {
    if (!n) return;
    for (int i = 0; i < ALPHA; i++)
        node_free(n->children[i]);
    free(n);
}

static void wd_insert(TrieNode *root, const char *word) {
    TrieNode *cur = root;
    for (int i = 0; word[i]; i++) {
        int idx = word[i] - 'a';
        if (!cur->children[idx])
            cur->children[idx] = node_new();
        cur = cur->children[idx];
    }
    cur->is_end = 1;
}

static int wd_search_dfs(TrieNode *node, const char *word, int idx) {
    if (!word[idx]) return node->is_end;
    char ch = word[idx];
    if (ch == '.') {
        for (int i = 0; i < ALPHA; i++) {
            if (node->children[i] && wd_search_dfs(node->children[i], word, idx + 1))
                return 1;
        }
        return 0;
    }
    int ci = ch - 'a';
    if (!node->children[ci]) return 0;
    return wd_search_dfs(node->children[ci], word, idx + 1);
}

static int wd_search(TrieNode *root, const char *word) {
    return wd_search_dfs(root, word, 0);
}

int main(void) {
    int n;
    int *arr = read_ints(&n);
    int n_words = arr[0];
    free(arr);

    TrieNode *root = node_new();
    for (int i = 0; i < n_words; i++) {
        char *w = read_line();
        wd_insert(root, w);
        free(w);
    }

    arr = read_ints(&n);
    int n_searches = arr[0];
    free(arr);

    for (int i = 0; i < n_searches; i++) {
        char *s = read_line();
        write_bool(wd_search(root, s));
        free(s);
    }

    node_free(root);
    return 0;
}
