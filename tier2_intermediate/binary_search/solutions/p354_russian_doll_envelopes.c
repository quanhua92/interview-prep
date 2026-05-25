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


#include <stdio.h>
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
    struct { const char *label; int env[10][2]; int n; int expected; int pass; } tests[] = {
        { "example 1", {{5,4},{6,4},{6,7},{2,3}}, 4, 3, 0 },
        { "example 2", {{1,1},{1,1},{1,1}}, 3, 1, 0 },
        { "single envelope", {{1,2}}, 1, 1, 0 },
        { "strictly increasing", {{1,2},{2,3},{3,4}}, 3, 3, 0 },
        { "width ties sorted by height desc", {{4,5},{4,6},{6,7},{2,3},{1,1}}, 5, 4, 0 },
        { "height breaks chain", {{2,100},{3,200},{4,300},{5,250}}, 4, 3, 0 },
    };
    int tn = (int)(sizeof(tests) / sizeof(tests[0]));
    int passed = 0;

    for (int i = 0; i < tn; i++) {
        int *env_ptrs[10];
        int colSizes[10];
        for (int j = 0; j < tests[i].n; j++) {
            env_ptrs[j] = tests[i].env[j];
            colSizes[j] = 2;
        }
        int got = maxEnvelopes(env_ptrs, tests[i].n, colSizes);
        tests[i].pass = (got == tests[i].expected);
        if (tests[i].pass) passed++;
    }

    printf("\n============================================================\n");
    printf("  354. Russian Doll Envelopes\n");
    printf("============================================================\n");
    for (int i = 0; i < tn; i++)
        printf("  Test %d (%s): %s\n", i + 1, tests[i].label, tests[i].pass ? "PASS" : "FAIL");
    printf("\n  %d/%d passed\n", passed, tn);
    printf("============================================================\n");
    return passed == tn ? 0 : 1;
}
