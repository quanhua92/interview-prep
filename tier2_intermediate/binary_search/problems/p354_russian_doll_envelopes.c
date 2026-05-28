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

static int env_buf[200000][2];
static int env_count;

static int cmp_env(const void *a, const void *b)
{
    abort();
}

int main(void)
{
    int cnt;
    int *header = read_ints(&cnt);
    int envelopesSize = header[0];
    free(header);
    env_count = 0;
    for (int i = 0; i < envelopesSize; i++) {
        int rc;
        int *row = read_ints(&rc);
        env_buf[env_count][0] = row[0];
        env_buf[env_count][1] = row[1];
        env_count++;
        free(row);
    }
    if (envelopesSize <= 1) { write_int(envelopesSize); return 0; }
    qsort(env_buf, envelopesSize, sizeof(env_buf[0]), cmp_env);

    int *dp = malloc(envelopesSize * sizeof(int));
    int dlen = 0;
    for (int i = 0; i < envelopesSize; i++) {
        int h = env_buf[i][1];
        int lo = 0, hi = dlen;
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (dp[mid] < h) lo = mid + 1;
            else hi = mid;
        }
        dp[lo] = h;
        if (lo == dlen) dlen++;
    }
    write_int(dlen);
    free(dp);
    return 0;
}
