/*
 * P20: Valid Parentheses (Easy)
 * https://leetcode.com/problems/valid-parentheses/
 * Topics: String, Stack
 *
 * Given a string s containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.
 *
 * Hint: Use a stack to match opening and closing brackets.
 */

use wasm_libs::*;

fn is_valid(s: &str) -> bool {
    todo!()
}

fn main() {
    let s = read_line();
    write_bool(is_valid(&s));
    std::process::exit(0);
}
