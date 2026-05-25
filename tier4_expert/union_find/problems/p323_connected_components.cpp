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
 * Constraints:
 *     - 1 <= n <= 2000
 *     - 1 <= edges.length <= 5000
 *     - edges[i].length == 2
 *     - 0 <= ai <= bi < n
 *     - ai != bi
 *     - There are no repeated edges.
 * 
 * Template (python3):
 *     class Solution:
 *         def countComponents(self, n: int, edges: List[List[int]]) -> int:
 * 
 * Hint: Use a Union-Find data structure to merge connected nodes and count components.
 */
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

struct UnionFind {
    std::vector<int> parent, rank_;
    UnionFind(int n) : parent(n), rank_(n, 0) {
        for (int i = 0; i < n; i++) parent[i] = i;
    }
    int find(int x) {
        /* TODO: Implement */
        return 0;
    }
    bool unite(int x, int y) {
        /* TODO: Implement */
        return 0;
    }
};

int countComponents(int n, const std::vector<std::pair<int,int>> &edges) {
    /* TODO: Implement */
    return 0;
}

struct TC {
    const char *label;
    int n;
    std::vector<std::pair<int,int>> edges;
    int expected;
};

int main(void) {
    std::vector<TC> tcs = {
        { "example", 5, {{0,1},{1,2},{3,4}}, 2 },
        { "fully connected", 5, {{0,1},{1,2},{2,3},{3,4}}, 1 },
        { "no edges", 3, {}, 3 },
        { "single node no edges", 1, {}, 1 },
        { "two disjoint pairs", 4, {{0,1},{2,3}}, 2 },
        { "two triangles", 6, {{0,1},{1,2},{2,0},{3,4},{4,5},{5,3}}, 2 },
        { "three components with chain and pairs", 7, {{0,1},{1,2},{3,4},{5,6}}, 3 },
    };

    printf("\n============================================================\n");
    printf("  323. Number of Connected Components in an Undirected Graph\n");
    printf("============================================================\n");

    int passed = 0;
    for (int i = 0; i < (int)tcs.size(); i++) {
        int got = countComponents(tcs[i].n, tcs[i].edges);
        if (got == tcs[i].expected) {
            passed++;
            printf("  Test %d (%s): PASS\n", i + 1, tcs[i].label);
        } else {
            printf("  Test %d (%s): FAIL\n", i + 1, tcs[i].label);
            printf("    Expected: %d\n    Got:      %d\n", tcs[i].expected, got);
        }
    }
    printf("\n  %d/%d passed\n", passed, (int)tcs.size());
    printf("============================================================\n\n");
    return passed == (int)tcs.size() ? 0 : 1;
}
