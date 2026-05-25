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
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

static bool isSubseq(const std::string &word, const std::string &target) {
    abort();
}

static std::string findLongestWord(const std::string &s, const std::vector<std::string> &dict) {
    abort();
}

int main(void) {
    int passed = 0, total = 6;
    printf("\n============================================================\n");
    printf("  524. Longest Word in Dictionary through Deleting\n");
    printf("============================================================\n");

    {
        std::string got = findLongestWord("abpcplea", {"ale", "apple", "monkey", "plea"});
        if (got == "apple") { passed++; printf("  Test 1 (example 1): PASS\n"); }
        else { printf("  Test 1 (example 1): FAIL\n  Expected: apple, Got: %s\n", got.c_str()); }
    }
    {
        std::string got = findLongestWord("abpcplea", {"a", "b", "c"});
        if (got == "a") { passed++; printf("  Test 2 (example 2): PASS\n"); }
        else { printf("  Test 2 (example 2): FAIL\n  Expected: a, Got: %s\n", got.c_str()); }
    }
    {
        std::string got = findLongestWord("abpcplea", {});
        if (got == "") { passed++; printf("  Test 3 (empty dictionary): PASS\n"); }
        else { printf("  Test 3 (empty dictionary): FAIL\n  Expected: (empty), Got: %s\n", got.c_str()); }
    }
    {
        std::string got = findLongestWord("abc", {"xyz", "def"});
        if (got == "") { passed++; printf("  Test 4 (no match): PASS\n"); }
        else { printf("  Test 4 (no match): FAIL\n  Expected: (empty), Got: %s\n", got.c_str()); }
    }
    {
        std::string got = findLongestWord("abpcplea", {"apple", "ale", "abpple"});
        if (got == "abpple") { passed++; printf("  Test 5 (same length lexicographical tie): PASS\n"); }
        else { printf("  Test 5 (same length lexicographical tie): FAIL\n  Expected: abpple, Got: %s\n", got.c_str()); }
    }
    {
        std::string got = findLongestWord("a", {"a", "aa", "aaa"});
        if (got == "a") { passed++; printf("  Test 6 (longer dict words than s): PASS\n"); }
        else { printf("  Test 6 (longer dict words than s): FAIL\n  Expected: a, Got: %s\n", got.c_str()); }
    }

    printf("\n  %d/%d passed\n", passed, total);
    printf("============================================================\n\n");
    return passed == total ? 0 : 1;
}
