/*
 * P684: Redundant Connection (Medium)
 * https://leetcode.com/problems/redundant-connection/
 * Topics: Depth-First Search, Breadth-First Search, Union Find, Graph
 *
 * Return an edge that can be removed so that the resulting graph is a tree of n nodes.
 * If there are multiple answers, return the answer that occurs last in the input.
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
    abort();
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
