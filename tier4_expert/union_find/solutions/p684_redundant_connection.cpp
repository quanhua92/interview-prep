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
#include <functional>
#include <vector>

std::vector<int> findRedundantConnection(const std::vector<std::vector<int>> &edges) {
    int size = (int)edges.size() + 1;
    std::vector<int> parent(size), rank_(size, 0);
    for (int i = 0; i < size; i++) parent[i] = i;

    std::function<int(int)> find = [&](int x) -> int {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    };

    for (auto &e : edges) {
        int u = e[0], v = e[1];
        int rx = find(u), ry = find(v);
        if (rx == ry) return {u, v};
        if (rank_[rx] < rank_[ry]) std::swap(rx, ry);
        parent[ry] = rx;
        if (rank_[rx] == rank_[ry]) rank_[rx]++;
    }
    return {};
}

int main(void)
{
    std::vector<int> first = read_ints();
    int n = first[0];
    std::vector<std::vector<int>> edges;
    for (int i = 0; i < n; i++) {
        edges.push_back(read_ints());
    }
    auto result = findRedundantConnection(edges);
    write_ints(result);
    return 0;
}
