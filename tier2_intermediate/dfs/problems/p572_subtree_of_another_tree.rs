/*
 * P572: Subtree of Another Tree [PREMIUM] (Easy)
 * https://leetcode.com/problems/subtree-of-another-tree/
 * Topics: Tree, Depth-First Search, String Matching, Binary Tree, Hash Function
 */

use wasm_libs::*;

fn build_tree(vals: &[i32], nl: i32) -> (Vec<i32>, Vec<i32>) {
    todo!();
}

fn is_same(ri: i32, si: i32, rvals: &[i32], svals: &[i32], rleft: &[i32], rright: &[i32], sleft: &[i32], sright: &[i32]) -> bool {
    todo!();
}

fn is_subtree(ri: i32, si: i32, rvals: &[i32], svals: &[i32], rleft: &[i32], rright: &[i32], sleft: &[i32], sright: &[i32]) -> bool {
    todo!();
}

fn main() {
    let root_line = read_line();
    let sub_line = read_line();
    let nl = 2147483647i32;
    let parse = |line: &str| -> Vec<i32> {
        line.split_whitespace()
            .map(|t| if t == "null" { nl } else { t.parse().unwrap() })
            .collect()
    };
    let root_vals = parse(&root_line);
    let sub_vals = parse(&sub_line);
    let (rleft, rright) = build_tree(&root_vals, nl);
    let (sleft, sright) = build_tree(&sub_vals, nl);
    let root_idx = if root_vals.is_empty() || root_vals[0] == nl { -1 } else { 0 };
    let sub_idx = if sub_vals.is_empty() || sub_vals[0] == nl { -1 } else { 0 };
    write_bool(is_subtree(root_idx, sub_idx, &root_vals, &sub_vals, &rleft, &rright, &sleft, &sright));
}
