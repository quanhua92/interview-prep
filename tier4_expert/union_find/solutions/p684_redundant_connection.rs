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
