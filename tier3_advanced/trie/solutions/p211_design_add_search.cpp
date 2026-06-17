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
 *     - At most 10^4 calls will be made to addWord and search.
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
#include <string>
#include <unordered_map>
#include <vector>


struct TrieNode {
    std::unordered_map<char, TrieNode*> children;
    bool is_end = false;

    ~TrieNode() {
        for (auto &p : children) delete p.second;
    }
};

class WordDictionary {
    TrieNode root;
public:
    void addWord(const std::string &word) {
        TrieNode *cur = &root;
        for (char ch : word) {
            if (!cur->children.count(ch))
                cur->children[ch] = new TrieNode();
            cur = cur->children[ch];
        }
        cur->is_end = true;
    }

    bool search(const std::string &word) {
        return dfs(&root, word, 0);
    }

private:
    bool dfs(TrieNode *node, const std::string &word, int idx) {
        if (idx == (int)word.size()) return node->is_end;
        char ch = word[idx];
        if (ch == '.') {
            for (auto &p : node->children) {
                if (dfs(p.second, word, idx + 1)) return true;
            }
            return false;
        }
        if (!node->children.count(ch)) return false;
        return dfs(node->children[ch], word, idx + 1);
    }
};

int main(void) {
    int num_ops = read_int();
    WordDictionary wd;
    for (int i = 0; i < num_ops; i++) {
        std::string op = read_line();
        std::string val = read_line();
        if (op == "add_word") {
            wd.addWord(val);
            write_string("null");
        } else if (op == "search") {
            write_bool(wd.search(val));
        }
    }
    return 0;
}
