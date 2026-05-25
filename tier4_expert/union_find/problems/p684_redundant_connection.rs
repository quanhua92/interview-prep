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
fn find_redundant_connection(edges: &[&[i32]]) -> (i32, i32) {
    todo!()
}

struct TC {
    label: &'static str,
    edges: &'static [&'static [i32]],
    expected: (i32, i32),
}

fn main() {
    let tcs: &[TC] = &[
        TC { label: "example 1", edges: &[&[1,2],&[1,3],&[2,3]], expected: (2,3) },
        TC { label: "example 2", edges: &[&[1,2],&[2,3],&[3,4],&[1,4],&[1,5]], expected: (1,4) },
        TC { label: "triangle of 3", edges: &[&[1,2],&[2,3],&[3,1]], expected: (3,1) },
        TC { label: "redundant at end star", edges: &[&[1,2],&[1,3],&[1,4],&[1,5],&[2,3]], expected: (2,3) },
        TC { label: "last edge closes triangle", edges: &[&[1,2],&[1,3],&[1,4],&[2,3]], expected: (2,3) },
    ];

    println!("\n============================================================");
    println!("  684. Redundant Connection");
    println!("============================================================");

    let mut passed = 0;
    for (i, tc) in tcs.iter().enumerate() {
        let got = find_redundant_connection(tc.edges);
        if got == tc.expected {
            passed += 1;
            println!("  Test {} ({}): PASS", i + 1, tc.label);
        } else {
            println!("  Test {} ({}): FAIL", i + 1, tc.label);
            println!("    Expected: {:?}\n    Got:      {:?}", tc.expected, got);
        }
    }

    println!("\n  {}/{} passed", passed, tcs.len());
    println!("============================================================\n");

    std::process::exit(if passed == tcs.len() { 0 } else { 1 });
}
