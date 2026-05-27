/*
 * P479: Largest Palindrome Product [PREMIUM] (Hard)
 * https://leetcode.com/problems/largest-palindrome-product/
 * Topics: Math, Enumeration
 *
 * Given an integer n, return the largest palindromic integer that can be represented as the product of two n-digits integers. Since the answer can be very large, return it modulo 1337.
 * Example 1:
 *     Input: n = 2
 *     Output: 987
 *     Explanation: 99 x 91 = 9009, 9009 % 1337 = 987
 *
 * Example 2:
 *     Input: n = 1
 *     Output: 9
 *
 * Constraints:
 *     - 1 <= n <= 8
 *
 * Template (python3):
 *     class Solution:
 *         def largestPalindrome(self, n: int) -> int:
 */

use wasm_libs::*;

fn largest_palindrome(n: i32) -> i32 {
    if n == 1 { return 9; }
    let upper = 10i64.pow(n as u32) - 1;
    let lower = 10i64.pow(n as u32 - 1);
    let mut left = upper;
    while left >= lower {
        let mut palindrome = left;
        let mut tmp = left;
        while tmp > 0 {
            palindrome = palindrome * 10 + tmp % 10;
            tmp /= 10;
        }
        let mut right = upper;
        while right >= lower {
            if right * right < palindrome { break; }
            if palindrome % right == 0 { return (palindrome % 1337) as i32; }
            right -= 1;
        }
        left -= 1;
    }
    0
}

fn main() {
    let vals = read_ints();
    write_int(largest_palindrome(vals[0]));
    std::process::exit(0);
}
