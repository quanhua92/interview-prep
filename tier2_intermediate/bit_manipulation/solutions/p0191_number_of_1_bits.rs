/*
 * P191: Number of 1 Bits (Easy)
 * https://leetcode.com/problems/number-of-1-bits/
 * Topics: Divide and Conquer, Bit Manipulation
 *
 * Given a positive integer n, write a function that returns the number of set bits in its binary representation (also known as the Hamming weight).
 *
 * Example 1:
 *     Input: n = 11
 *     Output: 3
 *     Explanation:
 *     The input binary string 1011 has a total of three set bits.
 *
 * Example 2:
 *     Input: n = 128
 *     Output: 1
 *     Explanation:
 *     The input binary string 10000000 has a total of one set bit.
 *
 * Example 3:
 *     Input: n = 2147483645
 *     Output: 30
 *     Explanation:
 *     The input binary string 1111111111111111111111111111101 has a total of thirty set bits.
 *
 * Constraints:
 *     - 1 <= n <= 2^31 - 1
 *
 * Template (python3):
 *     class Solution:
 *         def hammingWeight(self, n: int) -> int:
 *
 * Hint: Use Brian Kernighan's algorithm: n &= (n - 1) clears the lowest set bit.
 */

use wasm_libs::*;

fn hamming_weight(mut n: u32) -> i32 {
    let mut count = 0;
    while n != 0 {
        n &= n - 1;
        count += 1;
    }
    count
}

fn main() {
    let n = read_int();
    let result = hamming_weight(n as u32);
    write_int(result);
    std::process::exit(0);
}
