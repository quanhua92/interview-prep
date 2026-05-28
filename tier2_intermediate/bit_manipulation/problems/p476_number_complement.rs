/*
 * P476: Number Complement [PREMIUM] (Easy)
 * https://leetcode.com/problems/number-complement/
 * Topics: Bit Manipulation
 *
 * The complement of an integer is the integer you get when you flip all the 0's to 1's and all the 1's to 0's in its binary representation.
 * Given an integer num, return its complement.
 * Example 2:
 * Note: This question is the same as 1009: https://leetcode.com/problems/complement-of-base-10-integer/
 * Example 1:
 *     Input: num = 5
 *     Output: 2
 *     Explanation: The binary representation of 5 is 101 (no leading zero bits), and its complement is 010. So you need to output 2.
 *
 * Example 2:
 *     Input: num = 1
 *     Output: 0
 *     Explanation: The binary representation of 1 is 1 (no leading zero bits), and its complement is 0. So you need to output 0.
 *
 * Constraints:
 *     - 1 <= num < 231
 *
 * Template (python3):
 *     class Solution:
 *         def findComplement(self, num: int) -> int:
 */

use wasm_libs::*;

fn find_complement(num: i32) -> i32 {
    todo!();
}

fn main() {
    let num = read_int();
    let result = find_complement(num);
    write_int(result);
    std::process::exit(0);
}
