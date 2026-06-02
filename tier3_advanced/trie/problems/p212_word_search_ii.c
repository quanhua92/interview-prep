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
 *     - 1 <= words.length <= 3 * 10^4
 *     - 1 <= words[i].length <= 10
 *     - words[i] consists of lowercase English letters.
 *     - All the strings of words are unique.
 *
 * Hints:
 *     - You would need to optimize your backtracking to pass the larger test. Could you stop backtracking earlier?
 *     - If the current candidate does not exist in all words' prefix, you could stop backtracking immediately. What kind of data structure could answer such query efficiently? Does a hash table work? Why or why not? How about a Trie? If you would like to learn how to implement a basic trie, please work on this problem: <a href="https://leetcode.com/problems/implement-trie-prefix-tree/">Implement Trie (Prefix Tree)</a> first.
 *
 * Template (python3):
 *     class Solution:
 *         def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
 *
 * Hint: Build a Trie from the word list, then use DFS on the board to find matching words.
 */

#include "io.h"
#include <string.h>
#include <stdlib.h>

#define ALPHA 26
#define MAX_WORDS 30000
#define MAX_WORD_LEN 12
#define MAX_BOARD 13

typedef struct TrieNode {
    struct TrieNode *children[ALPHA];
    char word[MAX_WORD_LEN + 1];
    int has_word;
} TrieNode;

static TrieNode *pool;
static int pool_idx;
static int pool_cap;

static TrieNode *node_new(void) {
    abort();
}

static void trie_insert(TrieNode *root, const char *word) {
    abort();
}

static char result[MAX_WORDS][MAX_WORD_LEN + 1];
static int result_count;
static int rows, cols;

static void dfs(char board[MAX_BOARD][MAX_BOARD], int r, int c, TrieNode *parent) {
    abort();
}

static int cmp_str(const void *a, const void *b) {
    abort();
}

int main(void) {
    int n;
    int *arr = read_ints(&n);
    rows = arr[0];
    free(arr);
    arr = read_ints(&n);
    cols = arr[0];
    free(arr);

    char board[MAX_BOARD][MAX_BOARD];
    for (int r = 0; r < rows; r++) {
        char *line = read_line();
        for (int c = 0; c < cols; c++) {
            board[r][c] = line[c];
        }
        free(line);
    }

    arr = read_ints(&n);
    int nw = arr[0];
    free(arr);

    pool_cap = 10000;
    pool = malloc(pool_cap * sizeof(TrieNode));
    pool_idx = 0;
    result_count = 0;

    TrieNode *root = node_new();
    for (int i = 0; i < nw; i++) {
        char *w = read_line();
        trie_insert(root, w);
        free(w);
    }

    for (int r = 0; r < rows; r++)
        for (int c = 0; c < cols; c++)
            dfs(board, r, c, root);

    qsort(result, result_count, MAX_WORD_LEN + 1, cmp_str);

    write_int(result_count);
    for (int i = 0; i < result_count; i++) {
        write_string(result[i]);
    }

    return 0;
}
