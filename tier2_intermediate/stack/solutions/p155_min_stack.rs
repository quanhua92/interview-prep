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
    fn new() -> Self { MinStack { st: Vec::new(), mn: Vec::new() } }
    fn push(&mut self, val: i32) {
        self.st.push(val);
        self.mn.push(if self.mn.is_empty() { val } else { val.min(*self.mn.last().unwrap()) });
    }
    fn pop(&mut self) { self.st.pop(); self.mn.pop(); }
    fn top(&self) -> i32 { *self.st.last().unwrap() }
    fn get_min(&self) -> i32 { *self.mn.last().unwrap() }
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
