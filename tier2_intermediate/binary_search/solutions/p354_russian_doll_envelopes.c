/*
 * P354: Russian Doll Envelopes [PREMIUM] (Hard)
 * https://leetcode.com/problems/russian-doll-envelopes/
 * Topics: Array, Binary Search, Dynamic Programming, Sorting
 *
 * You are given a 2D array of integers envelopes where envelopes[i] = [wi, hi] represents the width and the height of an envelope.
 * One envelope can fit into another if and only if both the width and height of one envelope are greater than the other envelope's width and height.
 * Return the maximum number of envelopes you can Russian doll (i.e., put one inside the other).
 * Note: You cannot rotate an envelope.
 * Example 1:
 *     Input: envelopes = [[5,4],[6,4],[6,7],[2,3]]
 *     Output: 3
 *     Explanation: The maximum number of envelopes you can Russian doll is 3 ([2,3] => [5,4] => [6,7]).
 *
 * Example 2:
 *     Input: envelopes = [[1,1],[1,1],[1,1]]
 *     Output: 1
 *
 * Constraints:
 *     - 1 <= envelopes.length <= 105
 *     - envelopes[i].length == 2
 *     - 1 <= wi, hi <= 105
 *
 * Template (python3):
 *     class Solution:
 *         def maxEnvelopes(self, envelopes: List[List[int]]) -> int:
 */

#include "io.h"
#include <stdlib.h>
#include <string.h>

static int cmp_env(const void *a, const void *b)
{
    const int *ea = (const int *)a, *eb = (const int *)b;
    if (ea[0] != eb[0]) return ea[0] - eb[0];
    return eb[1] - ea[1];
}

int maxEnvelopes(int **envelopes, int envelopesSize, int *envelopesColSize)
{
    (void)envelopesColSize;
    if (envelopesSize <= 1) return envelopesSize;
    int sorted[100000][2];
    for (int i = 0; i < envelopesSize; i++) {
        sorted[i][0] = envelopes[i][0];
        sorted[i][1] = envelopes[i][1];
    }
    qsort(sorted, envelopesSize, sizeof(sorted[0]), cmp_env);

    int *dp = (int *)malloc(envelopesSize * sizeof(int));
    int dlen = 0;
    for (int i = 0; i < envelopesSize; i++) {
        int h = sorted[i][1];
        int lo = 0, hi = dlen;
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (dp[mid] < h) lo = mid + 1;
            else hi = mid;
        }
        dp[lo] = h;
        if (lo == dlen) dlen++;
    }
    free(dp);
    return dlen;
}

int main(void)
{
    int rows;
    int *flat = read_ints(&rows);
    int cols = flat[0];
    int envelopesSize = cols;
    int *envelopes_ptrs[100000];
    int colSizes[100000];
    int *envelopes_flat = flat + 1;
    for (int i = 0; i < envelopesSize; i++) {
        envelopes_ptrs[i] = envelopes_flat + i * 2;
        colSizes[i] = 2;
    }
    int result = maxEnvelopes(envelopes_ptrs, envelopesSize, colSizes);
    write_int(result);
    free(flat);
    return 0;
}
