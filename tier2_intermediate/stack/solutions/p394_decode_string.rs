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
    let mut num_stack: Vec<(i32, usize)> = Vec::new();
    let mut result: Vec<u8> = Vec::new();
    let mut curr_num = 0;

    for ch in s.bytes() {
        if ch.is_ascii_digit() {
            curr_num = curr_num * 10 + (ch - b'0') as i32;
        } else if ch == b'[' {
            num_stack.push((curr_num, result.len()));
            curr_num = 0;
        } else if ch == b']' {
            let (repeat, start) = num_stack.pop().unwrap();
            let seg: Vec<u8> = result[start..].to_vec();
            for _ in 1..repeat {
                result.extend_from_slice(&seg);
            }
        } else {
            result.push(ch);
        }
    }

    String::from_utf8(result).unwrap()
}

fn main() {
    let s = read_line();
    write_string(&decode_string(&s));
    std::process::exit(0);
}
