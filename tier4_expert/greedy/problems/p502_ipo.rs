/*
 * P502: IPO [PREMIUM] (Hard)
 * https://leetcode.com/problems/ipo/
 * Topics: Array, Greedy, Sorting, Heap (Priority Queue)
 *
 * Given k, w, profits[], capital[], return maximized capital after at most k projects.
 */


use std::collections::BinaryHeap;

fn find_maximized_capital(k: i32, w: i32, profits: &[i32], capital: &[i32]) -> i32 {
    todo!()
}

fn main() {
    let k = wasm_libs::read_int();
    let w = wasm_libs::read_int();
    let profits = wasm_libs::read_ints();
    let capital = wasm_libs::read_ints();
    let result = find_maximized_capital(k, w, &profits, &capital);
    wasm_libs::write_int(result);
}
