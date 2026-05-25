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


use rstest::TestCase;

fn get_next(mut num: i32) -> i32 {
    let mut total = 0;
    while num > 0 {
        let digit = num % 10;
        total += digit * digit;
        num /= 10;
    }
    total
}

fn is_happy(n: i32) -> bool {
    let mut slow = n;
    let mut fast = get_next(n);
    while fast != 1 && slow != fast {
        slow = get_next(slow);
        fast = get_next(get_next(fast));
    }
    fast == 1
}

fn main() {
    let tests: &[TestCase] = &[
        TestCase { label: "example 1", input_arr: &[], target: 19, expected: &[1] },
        TestCase { label: "example 2", input_arr: &[], target: 2, expected: &[0] },
        TestCase { label: "already happy", input_arr: &[], target: 1, expected: &[1] },
        TestCase { label: "small happy number", input_arr: &[], target: 7, expected: &[1] },
        TestCase { label: "enters 4-16 cycle", input_arr: &[], target: 4, expected: &[0] },
        TestCase { label: "power of 10", input_arr: &[], target: 100, expected: &[1] },
        TestCase { label: "large unhappy number", input_arr: &[], target: 999999999, expected: &[0] },
    ];
    let total = tests.len();
    let mut passed = 0;
    for (i, tc) in tests.iter().enumerate() {
        let got = is_happy(tc.target);
        let expected = tc.expected[0] != 0;
        if got == expected {
            passed += 1;
            println!("  Test {} ({}): PASS", i + 1, tc.label);
        } else {
            println!("  Test {} ({}): FAIL", i + 1, tc.label);
            println!("    Expected: {}", expected);
            println!("    Got:      {}", got);
        }
    }
    println!("\n  {}/{} passed", passed, total);
    std::process::exit(if passed == total { 0 } else { 1 });
}
