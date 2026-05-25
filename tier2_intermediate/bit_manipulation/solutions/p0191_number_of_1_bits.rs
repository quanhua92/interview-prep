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
 *     - 1 <= n <= 231 - 1
 *
 * Template (python3):
 *     class Solution:
 *         def hammingWeight(self, n: int) -> int:
 *
 * Hint: Use Brian Kernighan's algorithm: n &= (n - 1) clears the lowest set bit.
 */

#[allow(unused_imports)]
use rstest;

fn hamming_weight(mut n: u32) -> i32 {
    let mut count = 0;
    while n != 0 {
        n &= n - 1;
        count += 1;
    }
    count
}

fn main() {
    struct TestCase {
        label: &'static str,
        input: u32,
        expected: i32,
    }

    let tests: &[TestCase] = &[
        TestCase { label: "example 1", input: 0b00000000000000000000000000001011, expected: 3 },
        TestCase { label: "power of two", input: 0b00000000000000000000000010000000, expected: 1 },
        TestCase { label: "leetcode example 3", input: 2147483645, expected: 30 },
        TestCase { label: "zero", input: 0, expected: 0 },
        TestCase { label: "single bit", input: 1, expected: 1 },
        TestCase { label: "alternating bits", input: 0x55555555, expected: 16 },
        TestCase { label: "max value all bits set", input: 0x7FFFFFFF, expected: 31 },
    ];

    println!("\n============================================================");
    println!("  191. Number of 1 Bits");
    println!("============================================================");

    let mut passed = 0;
    for (i, tc) in tests.iter().enumerate() {
        let got = hamming_weight(tc.input);
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
