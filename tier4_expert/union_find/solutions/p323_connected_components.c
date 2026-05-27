/*
 * P323: Number of Connected Components in an Undirected Graph (Medium)
 * https://leetcode.com/problems/number-of-connected-components-in-an-undirected-graph/
 * Topics: Depth-First Search, Breadth-First Search, Union Find, Graph
 *
 * You have a graph of n nodes. You are given an integer n and an array edges where edges[i] = [ai, bi] indicates that there is an edge between ai and bi in the graph.
 * Return the number of connected components in the graph.
 *
 * Example 1:
 *     Input: n = 5, edges = [[0,1],[1,2],[3,4]]
 *     Output: 2
 *
 * Example 2:
 *     Input: n = 5, edges = [[0,1],[1,2],[2,3],[3,4]]
 *     Output: 1
 *
 * Hint: Use a Union-Find data structure to merge connected nodes and count components.
 */


#include "io.h"
#include <stdlib.h>

typedef struct {
    int *parent;
    int *rank;
    int n;
} UnionFind;

static UnionFind *UF_create(int n) {
    UnionFind *uf = malloc(sizeof(UnionFind));
    uf->n = n;
    uf->parent = malloc(n * sizeof(int));
    uf->rank = calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) uf->parent[i] = i;
    return uf;
}

static int UF_find(UnionFind *uf, int x) {
    if (uf->parent[x] != x)
        uf->parent[x] = UF_find(uf, uf->parent[x]);
    return uf->parent[x];
}

static int UF_union(UnionFind *uf, int x, int y) {
    int rx = UF_find(uf, x), ry = UF_find(uf, y);
    if (rx == ry) return 0;
    if (uf->rank[rx] < uf->rank[ry]) { int t = rx; rx = ry; ry = t; }
    uf->parent[ry] = rx;
    if (uf->rank[rx] == uf->rank[ry]) uf->rank[rx]++;
    return 1;
}

static void UF_free(UnionFind *uf) {
    free(uf->parent);
    free(uf->rank);
    free(uf);
}

int countComponents(int n, int edge_count, int (*edges)[2]) {
    UnionFind *uf = UF_create(n);
    int components = n;
    for (int i = 0; i < edge_count; i++) {
        int u = edges[i][0], v = edges[i][1];
        if (UF_union(uf, u, v)) components--;
    }
    UF_free(uf);
    return components;
}

int main(void)
{
    int cnt;
    int *first = read_ints(&cnt);
    int n = first[0];
    int m = cnt > 1 ? first[1] : 0;
    free(first);
    int (*edges)[2] = malloc(m * 2 * sizeof(int));
    for (int i = 0; i < m; i++) {
        int rc;
        int *row = read_ints(&rc);
        edges[i][0] = row[0];
        edges[i][1] = row[1];
        free(row);
    }
    int result = countComponents(n, m, edges);
    write_int(result);
    free(edges);
    return 0;
}
