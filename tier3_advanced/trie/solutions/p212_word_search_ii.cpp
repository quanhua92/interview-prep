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


#include "cpptest.h"
#include <string>
#include <vector>
#include <algorithm>
#include <array>

struct TrieNode {
    std::array<TrieNode*, 26> children{};
    std::string word;

    TrieNode() { children.fill(nullptr); }
};

class WordSearchII {
    int rows, cols;
    std::vector<std::string> result;

    void dfs(std::vector<std::vector<char>> &board, int r, int c, TrieNode *parent) {
        char ch = board[r][c];
        if (ch == '#') return;
        int idx = ch - 'a';
        TrieNode *curr = parent->children[idx];
        if (!curr) return;

        if (!curr->word.empty()) {
            result.push_back(curr->word);
            curr->word.clear();
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

        bool has_children = false;
        for (int i = 0; i < 26; i++) {
            if (curr->children[i]) { has_children = true; break; }
        }
        if (!has_children) parent->children[idx] = nullptr;
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

int main() {
    (void)print_arr;

    struct TC {
        const char *label;
        std::vector<std::vector<char>> board;
        std::vector<std::string> words;
        std::vector<std::string> expected;
    };

    TC tests[] = {
        {"example 1",
         {{'o','a','a','n'},{'e','t','a','e'},{'i','h','k','r'},{'i','f','l','v'}},
         {"oath","pea","eat","rain"},
         {"eat","oath"}},
        {"example 2",
         {{'a','b'},{'c','d'}},
         {"abcb"},
         {}},
        {"1x1 board single char",
         {{'a'}},
         {"a"},
         {"a"}},
        {"word not on board",
         {{'a','b'},{'c','d'}},
         {"xyz"},
         {}},
        {"same letter grid",
         {{'a','a'},{'a','a'}},
         {"aaaa"},
         {"aaaa"}},
        {"prefix is also a word",
         {{'o','a','a','n'},{'e','t','a','e'},{'i','h','k','r'},{'i','f','l','v'}},
         {"oath","oat"},
         {"oat","oath"}},
    };

    int n = (int)(sizeof(tests) / sizeof(tests[0]));
    int passed = 0;

    printf("\n============================================================\n");
    printf("  212. Word Search II\n");
    printf("============================================================\n");

    WordSearchII solver;
    for (int t = 0; t < n; t++) {
        auto got = solver.findWords(tests[t].board, tests[t].words);
        bool ok = (got == tests[t].expected);
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
