/*
 * P483: Smallest Good Base [PREMIUM] (Hard)
 * https://leetcode.com/problems/smallest-good-base/
 * Topics: Math, Binary Search
 *
 * Given an integer n represented as a string, return the smallest good base of n.
 * We call k >= 2 a good base of n, if all digits of n base k are 1's.
 * Example 1:
 *     Input: n = "13"
 *     Output: "3"
 *     Explanation: 13 base 3 is 111.
 *
 * Example 2:
 *     Input: n = "4681"
 *     Output: "8"
 *     Explanation: 4681 base 8 is 11111.
 *
 * Example 3:
 *     Input: n = "1000000000000000000"
 *     Output: "999999999999999999"
 *     Explanation: 1000000000000000000 base 999999999999999999 is 11.
 *
 * Constraints:
 *     - n is an integer in the range [3, 10^18].
 *     - n does not contain any leading zeros.
 *
 * Template (python3):
 *     class Solution:
 *         def smallestGoodBase(self, n: str) -> str:
 */

use wasm_libs::*;

fn calc(k: i64, m: i32, num: i64) -> i64 {
    todo!();
}

fn smallest_good_base(n: &str) -> String {
    todo!();
}

fn main() {
    let n = read_line();
    let result = smallest_good_base(&n);
    write_string(&result);
    std::process::exit(0);
}
