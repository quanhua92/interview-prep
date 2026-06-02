/*
 * P202: Happy Number (Easy)
 * https://leetcode.com/problems/happy-number/
 * Topics: Hash Table, Math, Two Pointers
 *
 * Write an algorithm to determine if a number n is happy.
 * A happy number is a number defined by the following process:
 *
 * 1. Starting with any positive integer, replace the number by the sum of the squares of its digits.
 * 2. Repeat the process until the number equals 1 (where it will stay), or it loops endlessly in a cycle which does not include 1.
 * 3. Those numbers for which this process ends in 1 are happy.
 * Return true if n is a happy number, and false if not.
 *
 * Example 1:
 *     Input: n = 19
 *     Output: true
 *     Explanation:
 *     1^2 + 9^2 = 82
 *     8^2 + 2^2 = 68
 *     6^2 + 8^2 = 100
 *     1^2 + 0^2 + 0^2 = 1
 *
 * Example 2:
 *     Input: n = 2
 *     Output: false
 *
 * Constraints:
 *     - 1 <= n <= 2^31 - 1
 *
 * Template (python3):
 *     class Solution:
 *         def isHappy(self, n: int) -> bool:
 *
 * Hint: Use fast and slow pointers on the sequence of sum-of-squared-digits.
 */

use wasm_libs::*;

fn get_next(mut num: i32) -> i32 {
    let mut total = 0;
    while num > 0 {
        let digit = num % 10;
        total += digit * digit;
        num /= 10;
    }
    total
}

fn solve(n: i32) -> bool {
    let mut slow = n;
    let mut fast = get_next(n);
    while fast != 1 && slow != fast {
        slow = get_next(slow);
        fast = get_next(get_next(fast));
    }
    fast == 1
}

fn main() {
    let n = read_int();
    write_bool(solve(n));
    std::process::exit(0);
}
