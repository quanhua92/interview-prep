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
 *
 * Example 2:
 *     Input: words = ["cat","dog","catdog"]
 *     Output: ["catdog"]
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

std::vector<std::string> findAllConcatenatedWordsInADict(std::vector<std::string> &words) {
    abort();
}

int main(void) {
    int nw = read_int();
    std::vector<std::string> words(nw);
    for (int i = 0; i < nw; i++) {
        words[i] = read_line();
    }

    auto result = findAllConcatenatedWordsInADict(words);

    write_int((int)result.size());
    for (auto &w : result) {
        write_string(w.c_str());
    }

    return 0;
}
