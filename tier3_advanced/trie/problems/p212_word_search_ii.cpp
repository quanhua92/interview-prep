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
 * Hint: Build a Trie from the word list, then use DFS on the board to find matching words.
 */

#include "io.h"
#include <string>
#include <vector>
#include <algorithm>
#include <array>

std::vector<std::string> findWords(std::vector<std::vector<char>> board,
                                   std::vector<std::string> words) {
    abort();
}

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

    auto result = findWords(board, words);

    write_int((int)result.size());
    for (auto &w : result) {
        write_string(w.c_str());
    }

    return 0;
}
