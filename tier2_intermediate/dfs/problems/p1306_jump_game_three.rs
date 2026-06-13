/*
 * P1306: Jump Game III (Medium)
 * https://leetcode.com/problems/jump-game-iii/
 * Topics: Array, Depth-First Search, Breadth-First Search
 */

use wasm_libs::*;

fn solve(arr: &[i32], start: usize) -> bool {
    todo!()
}

fn main() {
    let arr = read_ints();
    let start: usize = read_line().trim().parse().unwrap();
    let result = solve(&arr, start);
    write_bool(result);
}
