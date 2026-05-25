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


#include <functional>
#include <cstdio>
#include <cstdlib>
#include <cstring>
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

struct TC {
    const char *label;
    std::vector<std::vector<int>> edges;
    std::vector<int> expected;
};

int main(void) {
    std::vector<TC> tcs = {
        { "example 1", {{1,2},{1,3},{2,3}}, {2,3} },
        { "example 2", {{1,2},{2,3},{3,4},{1,4},{1,5}}, {1,4} },
        { "triangle of 3", {{1,2},{2,3},{3,1}}, {3,1} },
        { "redundant at end star", {{1,2},{1,3},{1,4},{1,5},{2,3}}, {2,3} },
        { "last edge closes triangle", {{1,2},{1,3},{1,4},{2,3}}, {2,3} },
    };

    printf("\n============================================================\n");
    printf("  684. Redundant Connection\n");
    printf("============================================================\n");

    int passed = 0;
    for (int i = 0; i < (int)tcs.size(); i++) {
        auto got = findRedundantConnection(tcs[i].edges);
        if (got == tcs[i].expected) {
            passed++;
            printf("  Test %d (%s): PASS\n", i + 1, tcs[i].label);
        } else {
            printf("  Test %d (%s): FAIL\n", i + 1, tcs[i].label);
            printf("    Expected: [%d,%d]\n    Got:      [%d,%d]\n",
                   tcs[i].expected[0], tcs[i].expected[1], got[0], got[1]);
        }
    }
    printf("\n  %d/%d passed\n", passed, (int)tcs.size());
    printf("============================================================\n\n");
    return passed == (int)tcs.size() ? 0 : 1;
}
