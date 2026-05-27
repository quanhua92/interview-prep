/*
 * P338: Counting Bits (Easy)
 * https://leetcode.com/problems/counting-bits/
 * Topics: Dynamic Programming, Bit Manipulation
 *
 * Given an integer n, return an array ans of length n + 1 such that for each i (0 <= i <= n), ans[i] is the number of 1's in the binary representation of i.
 *
 * Example 1:
 *     Input: n = 2
 *     Output: [0,1,1]
 *     Explanation:
 *     0 --> 0
 *     1 --> 1
 *     2 --> 10
 *
 * Example 2:
 *     Input: n = 5
 *     Output: [0,1,1,2,1,2]
 *     Explanation:
 *     0 --> 0
 *     1 --> 1
 *     2 --> 10
 *     3 --> 11
 *     4 --> 100
 *     5 --> 101
 *
 * Constraints:
 *     - 0 <= n <= 105
 *
 * Hints:
 *     - You should make use of what you have produced already.
 *     - Divide the numbers in ranges like [2-3], [4-7], [8-15] and so on. And try to generate new range from previous.
 *     - Or does the odd/even status of the number help you in calculating the number of 1s?
 *
 * Template (python3):
 *     class Solution:
 *         def countBits(self, n: int) -> List[int]:
 *
 * Hint: DP approach: ans[i] = ans[i >> 1] + (i & 1).
 */

use wasm_libs::*;

fn count_bits(n: i32) -> Vec<i32> {
    let mut ans = vec![0; (n as usize) + 1];
    for i in 1..=(n as usize) {
        ans[i] = ans[i >> 1] + (i as i32 & 1);
    }
    ans
}

fn main() {
    let n = read_int();
    let result = count_bits(n);
    write_ints(&result);
    std::process::exit(0);
}
