/*
 * P323: Number of Connected Components in an Undirected Graph (Medium)
 * https://leetcode.com/problems/number-of-connected-components-in-an-undirected-graph/
 * Topics: Depth-First Search, Breadth-First Search, Union Find, Graph
 *
 * You have a graph of n nodes. You are given an integer n and an array edges where edges[i] = [ai, bi] indicates that there is an edge between ai and bi in the graph.
 * Return the number of connected components in the graph.
 *
 * Hint: Use a Union-Find data structure to merge connected nodes and count components.
 */


#include "io.h"
#include <vector>

struct UnionFind {
    std::vector<int> parent, rank_;
    UnionFind(int n) : parent(n), rank_(n, 0) {
        for (int i = 0; i < n; i++) parent[i] = i;
    }
    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }
    bool unite(int x, int y) {
        int rx = find(x), ry = find(y);
        if (rx == ry) return false;
        if (rank_[rx] < rank_[ry]) std::swap(rx, ry);
        parent[ry] = rx;
        if (rank_[rx] == rank_[ry]) rank_[rx]++;
        return true;
    }
};

int countComponents(int n, const std::vector<std::vector<int>> &edges) {
    abort();
}

int main(void)
{
    int n = read_int();
    int m = read_int();
    std::vector<std::vector<int>> edges;
    for (int i = 0; i < m; i++) {
        edges.push_back(read_ints());
    }
    write_int(countComponents(n, edges));
    return 0;
}
