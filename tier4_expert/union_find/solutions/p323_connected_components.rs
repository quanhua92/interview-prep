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

use wasm_libs::*;

struct UnionFind {
    parent: Vec<i32>,
    rank_: Vec<i32>,
}

impl UnionFind {
    fn new(n: usize) -> Self {
        Self {
            parent: (0..n as i32).collect(),
            rank_: vec![0; n],
        }
    }

    fn find(&mut self, x: i32) -> i32 {
        if self.parent[x as usize] != x {
            let root = self.find(self.parent[x as usize]);
            self.parent[x as usize] = root;
            return root;
        }
        x
    }

    fn union(&mut self, x: i32, y: i32) -> bool {
        let mut rx = self.find(x);
        let mut ry = self.find(y);
        if rx == ry { return false; }
        if self.rank_[rx as usize] < self.rank_[ry as usize] {
            std::mem::swap(&mut rx, &mut ry);
        }
        self.parent[ry as usize] = rx;
        if self.rank_[rx as usize] == self.rank_[ry as usize] {
            self.rank_[rx as usize] += 1;
        }
        true
    }
}

fn count_components(n: usize, edges: &[(i32, i32)]) -> i32 {
    let mut uf = UnionFind::new(n);
    let mut components = n as i32;
    for &(u, v) in edges {
        if uf.union(u, v) { components -= 1; }
    }
    components
}

fn main() {
    let n = read_int() as usize;
    let m = read_int() as usize;
    let mut edge_vec: Vec<(i32, i32)> = Vec::new();
    for _ in 0..m {
        let row = read_ints();
        edge_vec.push((row[0], row[1]));
    }
    write_int(count_components(n, &edge_vec));
    std::process::exit(0);
}
