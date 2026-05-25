/*
 * P522: Longest Uncommon Subsequence II [PREMIUM] (Medium)
 * https://leetcode.com/problems/longest-uncommon-subsequence-ii/
 * Topics: Array, Hash Table, Two Pointers, String, Sorting
 *
 * Given an array of strings strs, return the length of the longest uncommon subsequence between them. If the longest uncommon subsequence does not exist, return -1.
 * An uncommon subsequence between an array of strings is a string that is a subsequence of one string but not the others.
 * A subsequence of a string s is a string that can be obtained after deleting any number of characters from s.
 * Example 1:
 *     Input: strs = ["aba","cdc","eae"]
 *     Output: 3
 *
 * Example 2:
 *     Input: strs = ["aaa","aaa","aa"]
 *     Output: -1
 *
 * Constraints:
 *     - 2 <= strs.length <= 50
 *     - 1 <= strs[i].length <= 10
 *     - strs[i] consists of lowercase English letters.
 *
 * Template (python3):
 *     class Solution:
 *         def findLUSlength(self, strs: List[str]) -> int:
 */


#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#include "cpptest.h"
#pragma GCC diagnostic pop

static bool is_subseq(const std::string &a, const std::string &b)
{
    int i = 0, la = (int)a.size();
    for (char ch : b) {
        if (i < la && a[i] == ch) i++;
    }
    return i == la;
}

static int findLUSlength(std::vector<std::string> strs)
{
    std::sort(strs.begin(), strs.end(),
              [](const std::string &a, const std::string &b) {
                  return a.size() > b.size();
              });

    int n = (int)strs.size();
    for (int i = 0; i < n; i++) {
        bool uncommon = true;
        for (int j = 0; j < n; j++) {
            if (i != j && is_subseq(strs[i], strs[j])) {
                uncommon = false;
                break;
            }
        }
        if (uncommon) return (int)strs[i].size();
    }
    return -1;
}

int main(void)
{
    struct {
        const char *label;
        std::vector<std::string> strs;
        int expected;
    } tests[] = {
        {"example 1", {"aba","cdc","eae"}, 3},
        {"example 2", {"aaa","aaa","aa"}, -1},
        {"all length 1 different", {"a","b","c","d"}, 1},
        {"all identical", {"abc","abc","abc"}, -1},
        {"one string longer than rest", {"a","a","ab","abc"}, 3},
        {"same length different chars", {"abc","abd","abe"}, 3},
    };
    int ntests = sizeof(tests) / sizeof(tests[0]);
    int passed = 0;

    printf("\n============================================================\n");
    printf("  522. Longest Uncommon Subsequence II\n");
    printf("============================================================\n");

    for (int i = 0; i < ntests; i++) {
        int got = findLUSlength(tests[i].strs);
        if (got == tests[i].expected) {
            passed++;
            printf("  Test %d (%s): PASS\n", i + 1, tests[i].label);
        } else {
            printf("  Test %d (%s): FAIL\n", i + 1, tests[i].label);
            printf("    Expected: %d\n    Got:      %d\n", tests[i].expected, got);
        }
    }

    printf("\n  %d/%d passed\n", passed, ntests);
    printf("============================================================\n\n");
    return passed == ntests ? 0 : 1;
}
