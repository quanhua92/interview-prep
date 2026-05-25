/*
 * P472: Concatenated Words [PREMIUM] (Hard)
 * https://leetcode.com/problems/concatenated-words/
 * Topics: Array, String, Dynamic Programming, Depth-First Search, Trie, Sorting
 * 
 * Given an array of strings words (without duplicates), return all the concatenated words in the given list of words.
 * A concatenated word is defined as a string that is comprised entirely of at least two shorter words (not necessarily distinct) in the given array.
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
#include "cpptest.h"
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
        /* TODO: Implement */
    }

    bool canConcatenate(const std::string &word, int start, int count) {
        /* TODO: Implement */
        return 0;
    }

public:
    std::vector<std::string> findAllConcatenatedWordsInADict(std::vector<std::string> &words) {
        /* TODO: Implement */
        return {};
    }
};

int main() {
    (void)print_arr;

    struct TC {
        const char *label;
        std::vector<std::string> words;
        std::vector<std::string> expected;
    };

    TC tests[] = {
        {"example 1",
         {"cat","cats","catsdogcats","dog","dogcatsdog","hippopotamuses","rat","ratcatdogcat"},
         {"catsdogcats","dogcatsdog","ratcatdogcat"}},
        {"example 2",
         {"cat","dog","catdog"},
         {"catdog"}},
        {"word from duplicate parts",
         {"cat","catcat"},
         {"catcat"}},
        {"no concatenated words",
         {"a","b","c"},
         {}},
        {"deep concatenation chain",
         {"a","aa","aaaa"},
         {"aa","aaaa"}},
        {"self-similar concatenation",
         {"ab","abab"},
         {"abab"}},
    };

    int n = (int)(sizeof(tests) / sizeof(tests[0]));
    int passed = 0;

    printf("\n============================================================\n");
    printf("  472. Concatenated Words\n");
    printf("============================================================\n");

    for (int t = 0; t < n; t++) {
        ConcatenatedWords solver;
        auto got = solver.findAllConcatenatedWordsInADict(tests[t].words);
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
