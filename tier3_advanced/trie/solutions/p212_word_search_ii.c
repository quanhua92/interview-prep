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

static TrieNode pool[600000];
static int pool_idx;

static TrieNode *node_new(void) {
    TrieNode *n = &pool[pool_idx++];
    memset(n, 0, sizeof(*n));
    return n;
}

static void trie_insert(TrieNode *root, const char *word) {
    TrieNode *cur = root;
    for (int i = 0; word[i]; i++) {
        int idx = word[i] - 'a';
        if (!cur->children[idx])
            cur->children[idx] = node_new();
        cur = cur->children[idx];
    }
    strcpy(cur->word, word);
    cur->has_word = 1;
}

static char result[MAX_WORDS][MAX_WORD_LEN + 1];
static int result_count;
static int rows, cols;

static void dfs(char board[MAX_BOARD][MAX_BOARD], int r, int c, TrieNode *parent) {
    char ch = board[r][c];
    if (ch == '#') return;
    int idx = ch - 'a';
    TrieNode *curr = parent->children[idx];
    if (!curr) return;

    if (curr->has_word) {
        strcpy(result[result_count++], curr->word);
        curr->has_word = 0;
        curr->word[0] = '\0';
    }

    board[r][c] = '#';
    int dr[] = {0, 0, 1, -1};
    int dc[] = {1, -1, 0, 0};
    for (int d = 0; d < 4; d++) {
        int nr = r + dr[d], nc = c + dc[d];
        if (nr >= 0 && nr < rows && nc >= 0 && nc < cols)
            dfs(board, nr, nc, curr);
    }
    board[r][c] = ch;

    int has_children = 0;
    for (int i = 0; i < ALPHA; i++) {
        if (curr->children[i]) { has_children = 1; break; }
    }
    if (!has_children) parent->children[idx] = NULL;
}

static int cmp_str(const void *a, const void *b) {
    return strcmp((const char *)a, (const char *)b);
}

int main(void) {
    int n;
    int *arr = read_ints(&n);
    rows = arr[0];
    cols = arr[1];
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
