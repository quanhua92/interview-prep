/*
 * P572: Subtree of Another Tree [PREMIUM] (Easy)
 * https://leetcode.com/problems/subtree-of-another-tree/
 * Topics: Tree, Depth-First Search, String Matching, Binary Tree, Hash Function
 */

use wasm_libs::*;

fn build_tree(vals: &[i32], nl: i32) -> (Vec<i32>, Vec<i32>) {
    let n = vals.len();
    if n == 0 || vals[0] == nl { return (vec![], vec![]); }
    let mut left = vec![-1i32; n];
    let mut right = vec![-1i32; n];
    let mut qi = 1usize;
    let mut queue = std::collections::VecDeque::new();
    queue.push_back(0usize);
    while let Some(i) = queue.pop_front() {
        if qi < n {
            left[i] = if vals[qi] == nl { -1 } else { qi as i32 };
            if vals[qi] != nl { queue.push_back(qi); }
            qi += 1;
        }
        if qi < n {
            right[i] = if vals[qi] == nl { -1 } else { qi as i32 };
            if vals[qi] != nl { queue.push_back(qi); }
            qi += 1;
        }
    }
    (left, right)
}

fn is_same(ri: i32, si: i32, rvals: &[i32], svals: &[i32], rleft: &[i32], rright: &[i32], sleft: &[i32], sright: &[i32]) -> bool {
    if ri < 0 && si < 0 { return true; }
    if ri < 0 || si < 0 { return false; }
    if rvals[ri as usize] != svals[si as usize] { return false; }
    is_same(rleft[ri as usize], sleft[si as usize], rvals, svals, rleft, rright, sleft, sright)
        && is_same(rright[ri as usize], sright[si as usize], rvals, svals, rleft, rright, sleft, sright)
}

fn is_subtree(ri: i32, si: i32, rvals: &[i32], svals: &[i32], rleft: &[i32], rright: &[i32], sleft: &[i32], sright: &[i32]) -> bool {
    if si < 0 { return true; }
    if ri < 0 { return false; }
    if is_same(ri, si, rvals, svals, rleft, rright, sleft, sright) { return true; }
    is_subtree(rleft[ri as usize], si, rvals, svals, rleft, rright, sleft, sright)
        || is_subtree(rright[ri as usize], si, rvals, svals, rleft, rright, sleft, sright)
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
