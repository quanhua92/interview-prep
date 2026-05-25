/*
 * P212: Word Search II (Hard)
 * https://leetcode.com/problems/word-search-ii/
 * Topics: Array, String, Backtracking, Trie, Matrix
 * 
 * Given an m x n board of characters and a list of strings words, return all words on the board.
 * Each word must be constructed from letters of sequentially adjacent cells, where adjacent cells are horizontally or vertically neighboring. The same letter cell may not be used more than once in a word.
 * 
 * Example 1:
 *     Input: board = [["o","a","a","n"],["e","t","a","e"],["i","h","k","r"],["i","f","l","v"]], words = ["oath","pea","eat","rain"]
 *     Output: ["eat","oath"]
 * 
 * Example 2:
 *     Input: board = [["a","b"],["c","d"]], words = ["abcb"]
 *     Output: []
 * 
 * Constraints:
 *     - m == board.length
 *     - n == board[i].length
 *     - 1 <= m, n <= 12
 *     - board[i][j] is a lowercase English letter.
 *     - 1 <= words.length <= 3 * 104
 *     - 1 <= words[i].length <= 10
 *     - words[i] consists of lowercase English letters.
 *     - All the strings of words are unique.
 * 
 * Hints:
 *     - You would need to optimize your backtracking to pass the larger test. Could you stop backtracking earlier?
 *     - If the current candidate does not exist in all words&#39; prefix, you could stop backtracking immediately. What kind of data structure could answer such query efficiently? Does a hash table work? Why or why not? How about a Trie? If you would like to learn how to implement a basic trie, please work on this problem: <a href="https://leetcode.com/problems/implement-trie-prefix-tree/">Implement Trie (Prefix Tree)</a> first.
 * 
 * Template (python3):
 *     class Solution:
 *         def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
 * 
 * Hint: Build a Trie from the word list, then use DFS on the board to find matching words.
 */
#include "ctest.h"
#include <string.h>

#define ALPHA 26
#define MAX_WORDS 30000
#define MAX_WORD_LEN 12
#define MAX_BOARD 13

typedef struct TrieNode {
    struct TrieNode *children[ALPHA];
    char word[MAX_WORD_LEN + 1];
    int has_word;
} TrieNode;

static TrieNode pool[600000];
static int pool_idx;

static TrieNode *node_new(void) {
    /* TODO: Implement */
    return 0;
}

static void trie_insert(TrieNode *root, const char *word) {
    /* TODO: Implement */
    return 0;
}

static char result[MAX_WORDS][MAX_WORD_LEN + 1];
static int result_count;
static int rows, cols;

static void dfs(char board[MAX_BOARD][MAX_BOARD], int r, int c, TrieNode *parent) {
    /* TODO: Implement */
    return 0;
}

static int cmp_str(const void *a, const void *b) {
    /* TODO: Implement */
    return 0;
}

typedef struct {
    const char *label;
    char board[MAX_BOARD][MAX_BOARD];
    int br, bc;
    const char *words[30];
    int nw;
    const char *expected[30];
    int ne;
} WsTC;

int main(void) {
    (void)th_print_arr;
    (void)th_arr_eq;

    WsTC tests[] = {
        {"example 1",
         {{'o','a','a','n'},{'e','t','a','e'},{'i','h','k','r'},{'i','f','l','v'}},
         4, 4,
         {"oath","pea","eat","rain"}, 4,
         {"eat","oath"}, 2},
        {"example 2",
         {{'a','b'},{'c','d'}},
         2, 2,
         {"abcb"}, 1,
         {""}, 0},
        {"1x1 board single char",
         {{'a'}},
         1, 1,
         {"a"}, 1,
         {"a"}, 1},
        {"word not on board",
         {{'a','b'},{'c','d'}},
         2, 2,
         {"xyz"}, 1,
         {""}, 0},
        {"same letter grid",
         {{'a','a'},{'a','a'}},
         2, 2,
         {"aaaa"}, 1,
         {"aaaa"}, 1},
        {"prefix is also a word",
         {{'o','a','a','n'},{'e','t','a','e'},{'i','h','k','r'},{'i','f','l','v'}},
         4, 4,
         {"oath","oat"}, 2,
         {"oat","oath"}, 2},
    };

    int n = (int)(sizeof(tests) / sizeof(tests[0]));
    int passed = 0;

    printf("\n============================================================\n");
    printf("  212. Word Search II\n");
    printf("============================================================\n");

    for (int t = 0; t < n; t++) {
        pool_idx = 0;
        result_count = 0;
        rows = tests[t].br;
        cols = tests[t].bc;

        char board[MAX_BOARD][MAX_BOARD];
        memcpy(board, tests[t].board, sizeof(board));

        TrieNode *root = node_new();
        for (int i = 0; i < tests[t].nw; i++)
            trie_insert(root, tests[t].words[i]);

        for (int r = 0; r < rows; r++)
            for (int c = 0; c < cols; c++)
                dfs(board, r, c, root);

        qsort(result, result_count, MAX_WORD_LEN + 1, cmp_str);

        int ok = (result_count == tests[t].ne);
        if (ok) {
            for (int i = 0; i < result_count; i++) {
                if (strcmp(result[i], tests[t].expected[i]) != 0) { ok = 0; break; }
            }
        }

        if (ok) {
            passed++;
            printf("  Test %d (%s): PASS\n", t + 1, tests[t].label);
        } else {
            printf("  Test %d (%s): FAIL\n", t + 1, tests[t].label);
            printf("    Expected %d words, got %d\n", tests[t].ne, result_count);
        }
    }

    printf("\n  %d/%d passed\n", passed, n);
    printf("============================================================\n\n");
    return passed == n ? 0 : 1;
}
