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
#include "cpptest.h"
#include <string>
#include <vector>
#include <unordered_map>

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
        /* TODO: Implement */
    }

    bool search(const std::string &word) {
        return dfs(&root, word, 0);
    }

private:
    bool dfs(TrieNode *node, const std::string &word, int idx) {
        /* TODO: Implement */
        return 0;
    }
};

int main() {
    (void)print_arr;

    struct TC {
        const char *label;
        std::vector<const char*> words;
        std::vector<const char*> searches;
        std::vector<int> expected;
    };

    TC tests[] = {
        {"example 1", {"bad","dad","mad"}, {"pad","bad",".ad","b.."}, {0,1,1,1}},
        {"example 2", {"a","ab"}, {"a",".a","ab"}, {1,0,1}},
        {"all dots pattern", {"abc"}, {"...",".."}, {1,0}},
        {"single char dot matches multiple", {"a","b"}, {"."}, {1}},
        {"dot at beginning", {"abc","xbc"}, {"bc"}, {0}},
        {"dot in middle and at end", {"abc"}, {"a.c","a.."}, {1,1}},
    };

    int n = (int)(sizeof(tests) / sizeof(tests[0]));
    int passed = 0;

    printf("\n============================================================\n");
    printf("  211. Design Add and Search Words Data Structure\n");
    printf("============================================================\n");

    for (int t = 0; t < n; t++) {
        WordDictionary wd;
        for (auto w : tests[t].words)
            wd.addWord(w);

        int ok = 1;
        for (int i = 0; i < (int)tests[t].searches.size(); i++) {
            bool got = wd.search(tests[t].searches[i]);
            if ((int)got != tests[t].expected[i]) { ok = 0; break; }
        }

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
