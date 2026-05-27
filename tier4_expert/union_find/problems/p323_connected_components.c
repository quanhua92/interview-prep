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
#include <stdlib.h>

int countComponents(int n, int edge_count, int (*edges)[2])
{
    abort();
}

int main(void)
{
    int n = read_int(NULL);
    int m = read_int(NULL);
    int (*edges)[2] = malloc(m * 2 * sizeof(int));
    for (int i = 0; i < m; i++) {
        int *row = read_ints(NULL);
        edges[i][0] = row[0];
        edges[i][1] = row[1];
        free(row);
    }
    int result = countComponents(n, m, edges);
    write_int(result);
    free(edges);
    return 0;
}
