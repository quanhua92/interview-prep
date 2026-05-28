/*
 * P388: Longest Absolute File Path [PREMIUM] (Medium)
 * https://leetcode.com/problems/longest-absolute-file-path/
 * Topics: String, Stack, Depth-First Search
 */

use wasm_libs::*;
use std::io::{self, BufRead};

fn main() {
    let stdin = std::io::stdin();
    let lines: Vec<String> = stdin.lock().lines().map(|l| l.unwrap()).collect();
    let input = lines.join("\n");
    let input = input.trim_end_matches('\n');
    let mut stack: Vec<i32> = vec![0];
    let mut max_len = 0;
    let mut i = 0;
    let bytes = input.as_bytes();
    let len = bytes.len();
    while i < len {
        let mut depth: usize = 0;
        while i < len && bytes[i] == b'\t' { depth += 1; i += 1; }
        let name_start = i;
        while i < len && bytes[i] != b'\n' { i += 1; }
        let name_len = i - name_start;
        if i < len { i += 1; }
        while stack.len() > depth + 1 { stack.pop(); }
        let is_file = bytes[name_start..name_start + name_len].iter().any(|&c| c == b'.');
        if is_file {
            max_len = max_len.max(stack[stack.len() - 1] + name_len as i32);
        } else {
            stack.push(stack[stack.len() - 1] + name_len as i32 + 1);
        }
    }
    write_int(max_len);
}
