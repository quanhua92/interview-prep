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

#include "io.h"
#include <stdlib.h>
#include <string.h>

static int is_subseq(const char *a, const char *b)
{
    abort();
}

static int cmp_len_desc(const void *a, const void *b)
{
    abort();
}

static int findLUSlength(const char **strs, int n)
{
    abort();
}

int main(void)
{
    int n_line_count;
    int *n_arr = read_ints(&n_line_count);
    int n = n_arr[0];
    free(n_arr);
    const char **strs = malloc(n * sizeof(const char *));
    for (int i = 0; i < n; i++) {
        strs[i] = read_line();
    }
    write_int(findLUSlength(strs, n));
    for (int i = 0; i < n; i++) free((void *)strs[i]);
    free(strs);
    return 0;
}
