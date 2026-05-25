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
#[allow(unused_imports)]
use rstest;

fn find_complement(num: i32) -> i32 {
    todo!()
}

fn main() {
    struct TestCase {
        label: &'static str,
        input: i32,
        expected: i32,
    }

    let tests: &[TestCase] = &[
        TestCase { label: "example 1", input: 5, expected: 2 },
        TestCase { label: "example 2", input: 1, expected: 0 },
        TestCase { label: "power of two", input: 2, expected: 1 },
        TestCase { label: "1000 flips to 0111", input: 8, expected: 7 },
        TestCase { label: "all ones flips to zero", input: 15, expected: 0 },
        TestCase { label: "large power of two", input: 1 << 30, expected: (1 << 30) - 1 },
    ];

    println!("\n============================================================");
    println!("  476. Number Complement");
    println!("============================================================");

    let mut passed = 0;
    for (i, tc) in tests.iter().enumerate() {
        let got = find_complement(tc.input);
        if got == tc.expected {
            passed += 1;
            println!("  Test {} ({}): PASS", i + 1, tc.label);
        } else {
            println!("  Test {} ({}): FAIL", i + 1, tc.label);
            println!("    Expected: {}", tc.expected);
            println!("    Got:      {}", got);
        }
    }

    println!("\n  {}/{} passed", passed, tests.len());
    println!("============================================================\n");

    std::process::exit(if passed == tests.len() { 0 } else { 1 });
}
