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
 *     - At most 3 * 104 calls in total will be made to insert, search, and startsWith.
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
#include <string>
#include <unordered_map>
#include <vector>


struct TrieNode {
    std::unordered_map<char, TrieNode*> children;
    bool is_end = false;

    ~TrieNode() {
    abort();
}
};

class Trie {
    TrieNode root;
public:
    void insert(const std::string &word) {
    abort();
}

    bool search(const std::string &word) {
    abort();
}

    bool startsWith(const std::string &prefix) {
    abort();
}

private:
    TrieNode *find(const std::string &prefix) {
    abort();
}
};

int main(void) {
    int num_ops = read_int();
    Trie trie;

    for (int i = 0; i < num_ops; i++) {
        std::string op = read_line();
        std::string val = read_line();

        if (op == "insert") {
            trie.insert(val);
            write_string("null");
        } else if (op == "search") {
            write_bool(trie.search(val));
        } else {
            write_bool(trie.startsWith(val));
        }
    }
    abort();

    return 0;
}
