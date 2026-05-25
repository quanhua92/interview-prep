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
#include "ctest.h"

static int findJudge(int n, int trust[][2], int trustSize) {
    /* TODO: Implement */
    return 0;
}

typedef struct {
    const char *label;
    int n;
    int trust[10000][2];
    int trustSize;
    int expected;
} TC;

int main(void) {
    (void)th_print_arr;
    (void)th_arr_eq;
    TC tests[] = {
        {"example 1", 2, {{1,2}}, 1, 2},
        {"example 2", 3, {{1,3},{2,3}}, 2, 3},
        {"no judge", 3, {{1,3},{2,3},{3,1}}, 3, -1},
        {"single person", 1, {{0}}, 0, 1},
        {"judge candidate trusts someone", 4, {{1,3},{2,3},{4,3},{3,4}}, 4, -1},
        {"no trust relationships n>1", 3, {{0}}, 0, -1},
        {"mutual trust no judge", 2, {{1,2},{2,1}}, 2, -1},
    };
    int nt = (int)(sizeof(tests) / sizeof(tests[0]));
    int passed = 0;
    for (int i = 0; i < nt; i++) {
        int got = findJudge(tests[i].n, tests[i].trust, tests[i].trustSize);
        if (got == tests[i].expected) {
            passed++;
            printf("  Test %d (%s): PASS\n", i + 1, tests[i].label);
        } else {
            printf("  Test %d (%s): FAIL\n", i + 1, tests[i].label);
            printf("    Expected: %d\n    Got:      %d\n", tests[i].expected, got);
        }
    }
    printf("\n  %d/%d passed\n", passed, nt);
    return passed == nt ? 0 : 1;
}
