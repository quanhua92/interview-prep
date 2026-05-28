/*
 * P508: Most Frequent Subtree Sum [PREMIUM] (Medium)
 * https://leetcode.com/problems/most-frequent-subtree-sum/
 * Topics: Hash Table, Tree, Depth-First Search, Binary Tree
 */

use wasm_libs::*;
use std::collections::HashMap;

fn build_tree(vals: &[i32], nl: i32) -> (Vec<i32>, Vec<i32>) {
    todo!();
}

fn main() {
    let line = read_line();
    let nl = 2147483647i32;
    let vals: Vec<i32> = line.split_whitespace()
        .map(|t| if t == "null" { nl } else { t.parse().unwrap() })
        .collect();

    if vals.is_empty() || vals[0] == nl {
        write_ints(&[]);
        return;
    }

    let (left, right) = build_tree(&vals, nl);
    let mut freq: HashMap<i32, i32> = HashMap::new();

    fn subtree_sum(idx: i32, vals: &[i32], left: &[i32], right: &[i32], freq: &mut HashMap<i32, i32>) -> i32 {
        todo!();
    }

    subtree_sum(0, &vals, &left, &right, &mut freq);

    let max_freq = *freq.values().max().unwrap_or(&0);
    let mut result: Vec<i32> = freq.into_iter().filter(|&(_, v)| v == max_freq).map(|(k, _)| k).collect();
    result.sort();
    write_ints(&result);
}
