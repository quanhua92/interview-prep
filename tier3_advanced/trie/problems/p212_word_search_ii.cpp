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
#include <string>
#include <vector>
#include <algorithm>
#include <array>


struct TrieNode {
    std::array<TrieNode*, 26> children{};
    std::string word;

    TrieNode() {
    abort();
}
};

class WordSearchII {
    int rows, cols;
    std::vector<std::string> result;

    void dfs(std::vector<std::vector<char>> &board, int r, int c, TrieNode *parent) {
    abort();
}

public:
    std::vector<std::string> findWords(std::vector<std::vector<char>> board,
                                       std::vector<std::string> words) {
        rows = (int)board.size();
        cols = (int)board[0].size();
        result.clear();

        TrieNode root;
        for (auto &w : words) {
            TrieNode *cur = &root;
            for (char ch : w) {
                int idx = ch - 'a';
                if (!cur->children[idx]) cur->children[idx] = new TrieNode();
                cur = cur->children[idx];
            }
            cur->word = w;
        }

        for (int r = 0; r < rows; r++)
            for (int c = 0; c < cols; c++)
                dfs(board, r, c, &root);

        std::sort(result.begin(), result.end());
        return result;
    }
};

int main(void) {
    int rows = read_int();
    int cols = read_int();

    std::vector<std::vector<char>> board(rows, std::vector<char>(cols));
    for (int r = 0; r < rows; r++) {
        std::string line = read_line();
        for (int c = 0; c < cols; c++) {
            board[r][c] = line[c];
        }
    }

    int nw = read_int();
    std::vector<std::string> words(nw);
    for (int i = 0; i < nw; i++) {
        words[i] = read_line();
    }

    WordSearchII solver;
    auto result = solver.findWords(board, words);

    write_int((int)result.size());
    for (auto &w : result) {
        write_string(w.c_str());
    }

    return 0;
}
