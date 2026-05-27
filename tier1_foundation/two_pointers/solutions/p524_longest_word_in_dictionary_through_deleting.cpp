/*
 * P524: Longest Word in Dictionary through Deleting [PREMIUM] (Medium)
 * https://leetcode.com/problems/longest-word-in-dictionary-through-deleting/
 * Topics: Array, Two Pointers, String, Sorting
 *
 * Given a string s and a string array dictionary, return the longest string in the dictionary that can be formed by deleting some of the given string characters. If there is more than one possible result, return the longest word with the smallest lexicographical order. If there is no possible result, return the empty string.
 * Example 1:
 *     Input: s = "abpcplea", dictionary = ["ale","apple","monkey","plea"]
 *     Output: "apple"
 *
 * Example 2:
 *     Input: s = "abpcplea", dictionary = ["a","b","c"]
 *     Output: "a"
 *
 * Constraints:
 *     - 1 <= s.length <= 1000
 *     - 1 <= dictionary.length <= 1000
 *     - 1 <= dictionary[i].length <= 1000
 *     - s and dictionary[i] consist of lowercase English letters.
 *
 * Template (python3):
 *     class Solution:
 *         def findLongestWord(self, s: str, dictionary: List[str]) -> str:
 */


#include "io.h"
#include <cstdlib>
#include <string>
#include <vector>

static bool isSubseq(const std::string &word, const std::string &target) {
    int i = 0;
    for (char ch : target) {
        if (i < (int)word.size() && word[i] == ch) i++;
    }
    return i == (int)word.size();
}

static std::string findLongestWord(const std::string &s, const std::vector<std::string> &dict) {
    std::string best = "";
    for (const auto &word : dict) {
        if (isSubseq(word, s)) {
            if (word.size() > best.size() || (word.size() == best.size() && word < best)) {
                best = word;
            }
        }
    }
    return best;
}

int main(void)
{
    std::string s = read_line();
    int dict_size = std::stoi(read_line());
    std::vector<std::string> dict(dict_size);
    for (int i = 0; i < dict_size; i++)
        dict[i] = read_line();
    write_string(findLongestWord(s, dict));
    return 0;
}
