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
 * Hint: Use a Union-Find data structure to merge connected nodes and count components.
 */

use wasm_libs::*;

fn count_components(n: usize, edges: &[(i32, i32)]) -> i32 {
    todo!()
}

fn main() {
    let first_line = read_ints();
    let n = first_line[0] as usize;
    let m = first_line[1] as usize;
    let mut edge_vec: Vec<(i32, i32)> = Vec::new();
    for _ in 0..m {
        let row = read_ints();
        edge_vec.push((row[0], row[1]));
    }
    write_int(count_components(n, &edge_vec));
    std::process::exit(0);
}
