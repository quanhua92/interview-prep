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

use wasm_libs::*;

fn find_redundant_connection(edges: &[&[i32]]) -> Vec<i32> {
    let n = edges.len() + 1;
    let mut parent: Vec<i32> = (0..n as i32).collect();
    let mut rank_: Vec<i32> = vec![0; n];

    fn find(parent: &mut Vec<i32>, x: i32) -> i32 {
        if parent[x as usize] != x {
            let root = find(parent, parent[x as usize]);
            parent[x as usize] = root;
            return root;
        }
        x
    }

    for e in edges {
        let (u, v) = (e[0], e[1]);
        let rx = find(&mut parent, u);
        let ry = find(&mut parent, v);
        if rx == ry { return vec![u, v]; }
        if rank_[rx as usize] < rank_[ry as usize] {
            parent[rx as usize] = ry;
            if rank_[rx as usize] == rank_[ry as usize] {
                rank_[ry as usize] += 1;
            }
        } else {
            parent[ry as usize] = rx;
            if rank_[rx as usize] == rank_[ry as usize] {
                rank_[rx as usize] += 1;
            }
        }
    }
    vec![0, 0]
}

fn main() {
    let first_line = read_ints();
    let n = first_line[0] as usize;
    let mut edge_vec: Vec<Vec<i32>> = Vec::new();
    for _ in 0..n {
        let row = read_ints();
        edge_vec.push(row);
    }
    let edge_refs: Vec<&[i32]> = edge_vec.iter().map(|v| v.as_slice()).collect();
    let result = find_redundant_connection(&edge_refs);
    write_ints(&result);
    std::process::exit(0);
}
