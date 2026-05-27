/*
 * P502: IPO [PREMIUM] (Hard)
 * https://leetcode.com/problems/ipo/
 * Topics: Array, Greedy, Sorting, Heap (Priority Queue)
 *
 * Given k, w, profits[], capital[], return maximized capital after at most k projects.
 */


use std::collections::BinaryHeap;

fn find_maximized_capital(k: i32, mut w: i32, profits: &[i32], capital: &[i32]) -> i32 {
    let n = profits.len();
    let mut proj: Vec<(i32, i32)> = capital.iter().zip(profits.iter()).map(|(&c, &p)| (c, p)).collect();
    proj.sort_by_key(|p| p.0);
    let mut heap: BinaryHeap<i32> = BinaryHeap::new();
    let mut idx = 0usize;
    for _ in 0..k {
        while idx < n && proj[idx].0 <= w {
            heap.push(proj[idx].1);
            idx += 1;
        }
        match heap.pop() {
            Some(p) => w += p,
            None => break,
        }
    }
    w
}

fn main() {
    let k = wasm_libs::read_int();
    let w = wasm_libs::read_int();
    let profits = wasm_libs::read_ints();
    let capital = wasm_libs::read_ints();
    let result = find_maximized_capital(k, w, &profits, &capital);
    wasm_libs::write_int(result);
}
