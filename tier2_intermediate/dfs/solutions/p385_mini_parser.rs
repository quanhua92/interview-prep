/*
 * P385: Mini Parser [PREMIUM] (Medium)
 * https://leetcode.com/problems/mini-parser/
 * Topics: String, Stack, Depth-First Search
 */

use wasm_libs::*;

fn main() {
    let s = read_line();
    if !s.starts_with('[') {
        write_int(s.parse::<i32>().unwrap());
    } else {
        write_string(&s);
    }
}
