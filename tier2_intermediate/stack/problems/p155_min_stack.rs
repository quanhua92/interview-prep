/*
 * P155: Min Stack (Medium)
 * https://leetcode.com/problems/min-stack/
 * Topics: Stack, Design
 *
 * Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.
 * You must implement a solution with O(1) time complexity for each function.
 *
 * Hint: stdin: n, then n blocks of (op_name, value_count, values...)
 *       stdout: one line per result, "null" or integer
 */

use wasm_libs::*;

struct MinStack {
    st: Vec<i32>,
    mn: Vec<i32>,
}

impl MinStack {
    fn new() -> Self {
    todo!();
}
    fn push(&mut self, val: i32) {
    todo!();
}
    fn pop(&mut self) {
    todo!();
}
    fn top(&self) -> i32 {
    todo!();
}
    fn get_min(&self) -> i32 {
    todo!();
}
}

fn main() {
    let n = read_int();
    let mut ms = MinStack::new();
    for _ in 0..n {
        let op = read_line();
        let count = read_int();
        let val = if count > 0 { read_ints()[0] } else { 0 };

        if op == "push" {
            ms.push(val);
            write_string("null");
        } else if op == "pop" {
            ms.pop();
            write_string("null");
        } else if op == "top" {
            write_int(ms.top());
        } else if op == "getMin" {
            write_int(ms.get_min());
        } else {
            write_string("null");
        }
    }
    std::process::exit(0);
}
