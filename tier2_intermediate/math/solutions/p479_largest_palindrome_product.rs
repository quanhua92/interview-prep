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


use rstest;

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
    struct TC { label: &'static str, n: i32, expected: i32 }
    let tests: &[TC] = &[
        TC { label: "example 1", n: 2, expected: 987 },
        TC { label: "example 2", n: 1, expected: 9 },
        TC { label: "3 digits", n: 3, expected: 123 },
        TC { label: "4 digits", n: 4, expected: 597 },
        TC { label: "8 digits (max n)", n: 8, expected: 475 },
    ];
    let mut passed = 0;
    for (i, tc) in tests.iter().enumerate() {
        let got = largest_palindrome(tc.n);
        if got == tc.expected {
            passed += 1;
            println!("  Test {} ({}): PASS", i + 1, tc.label);
        } else {
            println!("  Test {} ({}): FAIL (expected {}, got {})", i + 1, tc.label, tc.expected, got);
        }
    }
    println!("\n  {}/{} passed", passed, tests.len());
    std::process::exit(if passed == tests.len() { 0 } else { 1 });
}
