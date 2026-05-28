/*
 * P472: Concatenated Words [PREMIUM] (Hard)
 * https://leetcode.com/problems/concatenated-words/
 * Topics: Array, String, Dynamic Programming, Depth-First Search, Trie, Sorting
 *
 * Given an array of strings words (without duplicates), return all the concatenated words in the given list of words.
 * A concatenated word is defined as a string that is comprised entirely of at least two shorter words (not necessarily distinct) in the given array.
 * Example 1:
 *     Input: words = ["cat","cats","catsdogcats","dog","dogcatsdog","hippopotamuses","rat","ratcatdogcat"]
 *     Output: ["catsdogcats","dogcatsdog","ratcatdogcat"]
 *     Explanation: "catsdogcats" can be concatenated by "cats", "dog" and "cats";
 *     "dogcatsdog" can be concatenated by "dog", "cats" and "dog";
 *     "ratcatdogcat" can be concatenated by "rat", "cat", "dog" and "cat".
 *
 * Example 2:
 *     Input: words = ["cat","dog","catdog"]
 *     Output: ["catdog"]
 *
 * Constraints:
 *     - 1 <= words.length <= 104
 *     - 1 <= words[i].length <= 30
 *     - words[i] consists of only lowercase English letters.
 *     - All the strings of words are unique.
 *     - 1 <= sum(words[i].length) <= 105
 *
 * Template (python3):
 *     class Solution:
 *         def findAllConcatenatedWordsInADict(self, words: List[str]) -> List[str]:
 */

#include "io.h"
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>


struct TrieNode {
    std::unordered_map<char, TrieNode*> children;
    bool is_end = false;

    ~TrieNode() {
        for (auto &p : children) delete p.second;
    }
};

class ConcatenatedWords {
    TrieNode root;

    void insert(const std::string &word) {
        TrieNode *cur = &root;
        for (char ch : word) {
            if (!cur->children.count(ch))
                cur->children[ch] = new TrieNode();
            cur = cur->children[ch];
        }
        cur->is_end = true;
    }

    bool canConcatenate(const std::string &word, int start, int count) {
        TrieNode *cur = &root;
        for (int i = start; i < (int)word.size(); i++) {
            char ch = word[i];
            if (!cur->children.count(ch)) return false;
            cur = cur->children[ch];
            if (cur->is_end) {
                if (i == (int)word.size() - 1) return count >= 1;
                if (canConcatenate(word, i + 1, count + 1)) return true;
            }
        }
        return false;
    }

public:
    std::vector<std::string> findAllConcatenatedWordsInADict(std::vector<std::string> &words) {
        std::sort(words.begin(), words.end(),
                  [](const std::string &a, const std::string &b) { return a.size() < b.size(); });

        std::vector<std::string> result;
        for (auto &word : words) {
            if (canConcatenate(word, 0, 0))
                result.push_back(word);
            insert(word);
        }
        std::sort(result.begin(), result.end());
        return result;
    }
};

int main(void) {
    int nw = read_int();
    std::vector<std::string> words(nw);
    for (int i = 0; i < nw; i++) {
        words[i] = read_line();
    }

    ConcatenatedWords solver;
    auto result = solver.findAllConcatenatedWordsInADict(words);

    write_int((int)result.size());
    for (auto &w : result) {
        write_string(w.c_str());
    }

    return 0;
}
