/*
 * P997: Find the Town Judge (Easy)
 * https://leetcode.com/problems/find-the-town-judge/
 * Topics: Array, Hash Table, Graph
 *
 * In a town, there are n people labeled from 1 to n. There is a rumor that one of these people is secretly the town judge.
 * If the town judge exists, then:
 * You are given an array trust where trust[i] = [ai, bi] representing that the person labeled ai trusts the person labeled bi. If a trust relationship does not exist in trust array, then such a trust relationship does not exist.
 * Return the label of the town judge if the town judge exists and can be identified, or return -1 otherwise.
 *
 * Example 1:
 *     Input: n = 2, trust = [[1,2]]
 *     Output: 2
 *
 * Example 2:
 *     Input: n = 3, trust = [[1,3],[2,3]]
 *     Output: 3
 *
 * Example 3:
 *     Input: n = 3, trust = [[1,3],[2,3],[3,1]]
 *     Output: -1
 *
 * Constraints:
 *     - 1 <= n <= 1000
 *     - 0 <= trust.length <= 104
 *     - trust[i].length == 2
 *     - All the pairs of trust are unique.
 *     - ai != bi
 *     - 1 <= ai, bi <= n
 *
 * Template (python3):
 *     class Solution:
 *         def findJudge(self, n: int, trust: List[List[int]]) -> int:
 *
 * Hint: Trust score array: for each [a,b], scores[a]-=1 and scores[b]+=1. Judge has score n-1.
 */

#include "io.h"
#include <stdlib.h>
#include <string.h>

int findJudge(int n, int (*trust)[2], int trustSize)
{
    int scores[1001];
    memset(scores, 0, sizeof(scores));
    for (int i = 0; i < trustSize; i++) {
        scores[trust[i][0]] -= 1;
        scores[trust[i][1]] += 1;
    }
    for (int i = 1; i <= n; i++) {
        if (scores[i] == n - 1) return i;
    }
    return -1;
}

int main(void)
{
    int k;
    int *header = read_ints(&k);
    int n = header[0];
    int trustCount = header[1];
    free(header);

    int (*trust)[2] = NULL;
    if (trustCount > 0) {
        trust = malloc(trustCount * sizeof(int[2]));
        for (int i = 0; i < trustCount; i++) {
            int m;
            int *pair = read_ints(&m);
            trust[i][0] = pair[0];
            trust[i][1] = pair[1];
            free(pair);
        }
    }

    write_int(findJudge(n, trust, trustCount));
    free(trust);
    return 0;
}
