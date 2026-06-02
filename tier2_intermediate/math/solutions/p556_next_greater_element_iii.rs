/*
 * P556: Next Greater Element III [PREMIUM] (Medium)
 * https://leetcode.com/problems/next-greater-element-iii/
 * Topics: Math, Two Pointers, String
 *
 * Given a positive integer n, find the smallest integer which has exactly the same digits existing in the integer n and is greater in value than n. If no such positive integer exists, return -1.
 * Note that the returned integer should fit in 32-bit integer, if there is a valid answer but it does not fit in 32-bit integer, return -1.
 * Example 1:
 *     Input: n = 12
 *     Output: 21
 *
 * Example 2:
 *     Input: n = 21
 *     Output: -1
 *
 * Constraints:
 *     - 1 <= n <= 2^31 - 1
 *
 * Template (python3):
 *     class Solution:
 *         def nextGreaterElement(self, n: int) -> int:
 */

use wasm_libs::*;

fn next_greater_element(n: i32) -> i32 {
    let mut digits: Vec<char> = n.to_string().chars().collect();
    let len = digits.len();
    if len <= 1 { return -1; }
    let mut i = len - 2;
    while i > 0 && digits[i] >= digits[i + 1] { i -= 1; }
    if digits[i] >= digits[i + 1] { return -1; }
    let mut j = len - 1;
    while digits[j] <= digits[i] { j -= 1; }
    digits.swap(i, j);
    digits[i + 1..].reverse();
    match digits.iter().collect::<String>().parse::<i64>() {
        Ok(v) if v <= i32::MAX as i64 => v as i32,
        _ => -1,
    }
}

fn main() {
    let vals = read_ints();
    write_int(next_greater_element(vals[0]));
    std::process::exit(0);
}
