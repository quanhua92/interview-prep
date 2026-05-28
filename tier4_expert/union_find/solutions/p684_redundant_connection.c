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


#include "io.h"
#include <stdlib.h>

static int find(int *parent, int x) {
    if (parent[x] != x)
        parent[x] = find(parent, parent[x]);
    return parent[x];
}

static int unite(int *parent, int *rank, int x, int y) {
    int rx = find(parent, x), ry = find(parent, y);
    if (rx == ry) return 0;
    if (rank[rx] < rank[ry]) { int t = rx; rx = ry; ry = t; }
    parent[ry] = rx;
    if (rank[rx] == rank[ry]) rank[rx]++;
    return 1;
}

void findRedundantConnection(int n_edges, int (*edges)[2], int *out) {
    int size = n_edges + 1;
    int *parent = malloc(size * sizeof(int));
    int *rank = calloc(size, sizeof(int));
    for (int i = 0; i < size; i++) parent[i] = i;

    out[0] = 0; out[1] = 0;
    for (int i = 0; i < n_edges; i++) {
        int u = edges[i][0], v = edges[i][1];
        if (!unite(parent, rank, u, v)) {
            out[0] = u;
            out[1] = v;
            free(parent);
            free(rank);
            return;
        }
    }
    free(parent);
    free(rank);
}

int main(void)
{
    int cnt;
    int *first = read_ints(&cnt);
    int n = first[0];
    free(first);
    int (*edges)[2] = malloc(n * 2 * sizeof(int));
    for (int i = 0; i < n; i++) {
        int rc;
        int *row = read_ints(&rc);
        edges[i][0] = row[0];
        edges[i][1] = row[1];
        free(row);
    }
    int out[2] = {0, 0};
    findRedundantConnection(n, edges, out);
    write_ints(out, 2);
    free(edges);
    return 0;
}
