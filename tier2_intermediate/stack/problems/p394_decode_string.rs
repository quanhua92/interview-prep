/*
 * P394: Decode String (Medium)
 * https://leetcode.com/problems/decode-string/
 * Topics: String, Stack, Recursion
 *
 * Given an encoded string, return its decoded string.
 * The encoding rule is: k[encoded_string], where the encoded_string inside the square brackets is being repeated exactly k times.
 *
 * Hint: Use a stack to handle nested k[encoded] patterns.
 */

use wasm_libs::*;

fn decode_string(s: &str) -> String {
    todo!();
}

fn main() {
    let s = read_line();
    write_string(&decode_string(&s));
    std::process::exit(0);
}
