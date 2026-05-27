/*
 * P202: Happy Number (Easy)
 * https://leetcode.com/problems/happy-number/
 * Topics: Hash Table, Math, Two Pointers
 *
 * Write an algorithm to determine if a number n is happy.
 * A happy number is a number defined by the following process:
 * Return true if n is a happy number, and false if not.
 *
 * Example 1:
 *     Input: n = 19
 *     Output: true
 *     Explanation:
 *     12 + 92 = 82
 *     82 + 22 = 68
 *     62 + 82 = 100
 *     12 + 02 + 02 = 1
 *
 * Example 2:
 *     Input: n = 2
 *     Output: false
 *
 * Constraints:
 *     - 1 <= n <= 231 - 1
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
