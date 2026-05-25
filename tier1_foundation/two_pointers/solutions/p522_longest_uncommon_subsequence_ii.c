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


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#include "ctest.h"
#pragma GCC diagnostic pop

static int is_subseq(const char *a, const char *b)
{
    int i = 0, la = (int)strlen(a);
    for (int j = 0; b[j]; j++) {
        if (i < la && a[i] == b[j]) i++;
    }
    return i == la;
}

static int cmp_len_desc(const void *a, const void *b)
{
    int la = (int)strlen(*(const char *const *)a);
    int lb = (int)strlen(*(const char *const *)b);
    return lb - la;
}

static int findLUSlength(const char **strs, int n)
{
    const char *sorted[50];
    for (int i = 0; i < n; i++) sorted[i] = strs[i];
    qsort(sorted, n, sizeof(const char *), cmp_len_desc);

    for (int i = 0; i < n; i++) {
        int uncommon = 1;
        for (int j = 0; j < n; j++) {
            if (i != j && is_subseq(sorted[i], sorted[j])) {
                uncommon = 0;
                break;
            }
        }
        if (uncommon) return (int)strlen(sorted[i]);
    }
    return -1;
}

int main(void)
{
    const char *t1[] = {"aba","cdc","eae"};
    const char *t2[] = {"aaa","aaa","aa"};
    const char *t3[] = {"a","b","c","d"};
    const char *t4[] = {"abc","abc","abc"};
    const char *t5[] = {"a","a","ab","abc"};
    const char *t6[] = {"abc","abd","abe"};

    const char *label[] = {
        "example 1", "example 2", "all length 1 different",
        "all identical", "one string longer than rest", "same length different chars"
    };
    const char **strs[] = {t1, t2, t3, t4, t5, t6};
    int ns[] = {3, 3, 4, 3, 4, 3};
    int expected[] = {3, -1, 1, -1, 3, 3};
    int ntests = 6;
    int passed = 0;

    printf("\n============================================================\n");
    printf("  522. Longest Uncommon Subsequence II\n");
    printf("============================================================\n");

    for (int i = 0; i < ntests; i++) {
        int got = findLUSlength(strs[i], ns[i]);
        if (got == expected[i]) {
            passed++;
            printf("  Test %d (%s): PASS\n", i + 1, label[i]);
        } else {
            printf("  Test %d (%s): FAIL\n", i + 1, label[i]);
            printf("    Expected: %d\n    Got:      %d\n", expected[i], got);
        }
    }

    printf("\n  %d/%d passed\n", passed, ntests);
    printf("============================================================\n\n");
    return passed == ntests ? 0 : 1;
}
