/*
 * P502: IPO [PREMIUM] (Hard)
 * https://leetcode.com/problems/ipo/
 * Topics: Array, Greedy, Sorting, Heap (Priority Queue)
 *
 * Given k, w, profits[], capital[], return maximized capital after at most k projects.
 */

use wasm_libs::*;
use std::collections::BinaryHeap;

fn find_maximized_capital(k: i32, mut w: i32, profits: &[i32], capital: &[i32]) -> i32 {
    todo!();
}

fn main() {
    let k = read_int();
    let w = read_int();
    let profits = read_ints();
    let capital = read_ints();
    let result = find_maximized_capital(k, w, &profits, &capital);
    write_int(result);
}
