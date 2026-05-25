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
struct UnionFind {
    parent: Vec<i32>,
    rank_: Vec<i32>,
}

impl UnionFind {
    fn new(n: usize) -> Self {
        todo!()
    }

    fn find(&mut self, x: i32) -> i32 {
        todo!()
    }

    fn union(&mut self, x: i32, y: i32) -> bool {
        todo!()
    }
}

fn count_components(n: usize, edges: &[(i32, i32)]) -> i32 {
    todo!()
}

struct TC {
    label: &'static str,
    n: usize,
    edges: &'static [(i32, i32)],
    expected: i32,
}

fn main() {
    let tcs: &[TC] = &[
        TC { label: "example", n: 5, edges: &[(0,1),(1,2),(3,4)], expected: 2 },
        TC { label: "fully connected", n: 5, edges: &[(0,1),(1,2),(2,3),(3,4)], expected: 1 },
        TC { label: "no edges", n: 3, edges: &[], expected: 3 },
        TC { label: "single node no edges", n: 1, edges: &[], expected: 1 },
        TC { label: "two disjoint pairs", n: 4, edges: &[(0,1),(2,3)], expected: 2 },
        TC { label: "two triangles", n: 6, edges: &[(0,1),(1,2),(2,0),(3,4),(4,5),(5,3)], expected: 2 },
        TC { label: "three components with chain and pairs", n: 7, edges: &[(0,1),(1,2),(3,4),(5,6)], expected: 3 },
    ];

    println!("\n============================================================");
    println!("  323. Number of Connected Components in an Undirected Graph");
    println!("============================================================");

    let mut passed = 0;
    for (i, tc) in tcs.iter().enumerate() {
        let got = count_components(tc.n, tc.edges);
        if got == tc.expected {
            passed += 1;
            println!("  Test {} ({}): PASS", i + 1, tc.label);
        } else {
            println!("  Test {} ({}): FAIL", i + 1, tc.label);
            println!("    Expected: {}\n    Got:      {}", tc.expected, got);
        }
    }

    println!("\n  {}/{} passed", passed, tcs.len());
    println!("============================================================\n");

    std::process::exit(if passed == tcs.len() { 0 } else { 1 });
}
