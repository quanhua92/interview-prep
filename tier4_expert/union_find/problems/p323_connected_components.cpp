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


#include "io.h"
#include <vector>

int countComponents(int n, const std::vector<std::vector<int>> &edges)
{
    abort();
}

int main(void)
{
    int n;
    std::vector<int> tmp = read_ints();
    n = tmp[0];
    int m = tmp.size() > 1 ? tmp[1] : 0;
    std::vector<std::vector<int>> edges;
    for (int i = 0; i < m; i++) {
        std::vector<int> row = read_ints();
        edges.push_back(row);
    }
    write_int(countComponents(n, edges));
    return 0;
}
