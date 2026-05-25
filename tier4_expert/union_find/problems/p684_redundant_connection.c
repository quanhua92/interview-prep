/*
 * P684: Redundant Connection (Medium)
 * https://leetcode.com/problems/redundant-connection/
 * Topics: Depth-First Search, Breadth-First Search, Union Find, Graph
 * 
 * In this problem, a tree is an undirected graph that is connected and has no cycles.
 * You are given a graph that started as a tree with n nodes labeled from 1 to n, with one additional edge added. The added edge has two different vertices chosen from 1 to n, and was not an edge that already existed. The graph is represented as an array edges of length n where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the graph.
 * Return an edge that can be removed so that the resulting graph is a tree of n nodes. If there are multiple answers, return the answer that occurs last in the input.
 * 
 * Example 1:
 *     Input: edges = [[1,2],[1,3],[2,3]]
 *     Output: [2,3]
 * 
 * Example 2:
 *     Input: edges = [[1,2],[2,3],[3,4],[1,4],[1,5]]
 *     Output: [1,4]
 * 
 * Constraints:
 *     - n == edges.length
 *     - 3 <= n <= 1000
 *     - edges[i].length == 2
 *     - 1 <= ai < bi <= edges.length
 *     - ai != bi
 *     - There are no repeated edges.
 *     - The given graph is connected.
 * 
 * Template (python3):
 *     class Solution:
 *         def findRedundantConnection(self, edges: List[List[int]]) -> List[int]:
 * 
 * Hint: Use Union-Find to detect the first edge that connects two already-connected nodes.
 */
#include <stdio.h>
#include <stdlib.h>

static int find(int *parent, int x) {
    /* TODO: Implement */
    return 0;
}

static int unite(int *parent, int *rank, int x, int y) {
    /* TODO: Implement */
    return 0;
}

void findRedundantConnection(int n_edges, int (*edges)[2], int *out) {
    /* TODO: Implement */
    return 0;
}

typedef struct {
    const char *label;
    int edges[10][2];
    int n_edges;
    int expected[2];
} TC;

int main(void) {
    TC tcs[] = {
        { "example 1", {{1,2},{1,3},{2,3}}, 3, {2,3} },
        { "example 2", {{1,2},{2,3},{3,4},{1,4},{1,5}}, 5, {1,4} },
        { "triangle of 3", {{1,2},{2,3},{3,1}}, 3, {3,1} },
        { "redundant at end star", {{1,2},{1,3},{1,4},{1,5},{2,3}}, 5, {2,3} },
        { "last edge closes triangle", {{1,2},{1,3},{1,4},{2,3}}, 4, {2,3} },
    };
    int n_tcs = sizeof(tcs) / sizeof(tcs[0]);

    printf("\n============================================================\n");
    printf("  684. Redundant Connection\n");
    printf("============================================================\n");

    int passed = 0;
    for (int i = 0; i < n_tcs; i++) {
        int got[2] = {0, 0};
        findRedundantConnection(tcs[i].n_edges, tcs[i].edges, got);
        if (got[0] == tcs[i].expected[0] && got[1] == tcs[i].expected[1]) {
            passed++;
            printf("  Test %d (%s): PASS\n", i + 1, tcs[i].label);
        } else {
            printf("  Test %d (%s): FAIL\n", i + 1, tcs[i].label);
            printf("    Expected: [%d,%d]\n    Got:      [%d,%d]\n",
                   tcs[i].expected[0], tcs[i].expected[1], got[0], got[1]);
        }
    }
    printf("\n  %d/%d passed\n", passed, n_tcs);
    printf("============================================================\n\n");
    return passed == n_tcs ? 0 : 1;
}
