/*
 * P684: Redundant Connection (Medium)
 * https://leetcode.com/problems/redundant-connection/
 * Topics: Depth-First Search, Breadth-First Search, Union Find, Graph
 *
 * In this problem, a tree is an undirected graph that is connected and has no cycles.
 * You are given a graph that started as a tree with n nodes labeled from 1 to n, with one additional edge added. The added edge has two different vertices chosen from 1 to n, and was not an edge that already existed. The graph is represented as an array edges of length n where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the graph.
 * Return an edge that can be removed so that the resulting graph is a tree of n nodes. If there are multiple answers, return the answer that occurs last in the input.
 *
 * Hint: Use Union-Find to detect the first edge that connects two already-connected nodes.
 */

use wasm_libs::*;

fn find_redundant_connection(edges: &[&[i32]]) -> Vec<i32> {
    todo!()
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
