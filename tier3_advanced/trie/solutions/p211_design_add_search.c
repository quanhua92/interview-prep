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

typedef struct {
    const char *label;
    const char *words[20];
    int nwords;
    const char *searches[20];
    int nsearches;
    const int *expected;
} WdTC;

static const int exp0[] = {0,1,1,1};
static const int exp1[] = {1,0,1};
static const int exp2[] = {1,0};
static const int exp3[] = {1};
static const int exp4[] = {0};
static const int exp5[] = {1,1};

int main(void) {
    (void)th_print_arr;
    (void)th_arr_eq;

    WdTC tests[] = {
        {"example 1",
         {"bad","dad","mad"}, 3,
         {"pad","bad",".ad","b.."}, 4, exp0},
        {"example 2",
         {"a","ab"}, 2,
         {"a",".a","ab"}, 3, exp1},
        {"all dots pattern",
         {"abc"}, 1,
         {"...",".."}, 2, exp2},
        {"single char dot matches multiple",
         {"a","b"}, 2,
         {"."}, 1, exp3},
        {"dot at beginning",
         {"abc","xbc"}, 2,
         {"bc"}, 1, exp4},
        {"dot in middle and at end",
         {"abc"}, 1,
         {"a.c","a.."}, 2, exp5},
    };

    int n = (int)(sizeof(tests) / sizeof(tests[0]));
    int passed = 0;

    printf("\n============================================================\n");
    printf("  211. Design Add and Search Words Data Structure\n");
    printf("============================================================\n");

    for (int t = 0; t < n; t++) {
        TrieNode *root = node_new();
        for (int i = 0; i < tests[t].nwords; i++)
            wd_insert(root, tests[t].words[i]);

        int ok = 1;
        for (int i = 0; i < tests[t].nsearches; i++) {
            int got = wd_search(root, tests[t].searches[i]);
            if (got != tests[t].expected[i]) { ok = 0; break; }
        }
        node_free(root);

        if (ok) {
            passed++;
            printf("  Test %d (%s): PASS\n", t + 1, tests[t].label);
        } else {
            printf("  Test %d (%s): FAIL\n", t + 1, tests[t].label);
        }
    }

    printf("\n  %d/%d passed\n", passed, n);
    printf("============================================================\n\n");
    return passed == n ? 0 : 1;
}
