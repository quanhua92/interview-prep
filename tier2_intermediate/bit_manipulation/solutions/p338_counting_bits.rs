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

#[allow(unused_imports)]
use rstest;

fn count_bits(n: i32) -> Vec<i32> {
    let mut ans = vec![0; (n as usize) + 1];
    for i in 1..=(n as usize) {
        ans[i] = ans[i >> 1] + (i as i32 & 1);
    }
    ans
}

fn main() {
    let tests: &[(&str, i32, &[i32])] = &[
        ("example 1", 2, &[0, 1, 1]),
        ("example 2", 5, &[0, 1, 1, 2, 1, 2]),
        ("zero", 0, &[0]),
        ("one", 1, &[0, 1]),
        ("power-of-2 minus 1", 7, &[0, 1, 1, 2, 1, 2, 2, 3]),
        ("four bits all", 15, &[0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4]),
        ("power of 2", 16, &[0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 1]),
    ];

    println!("\n============================================================");
    println!("  338. Counting Bits");
    println!("============================================================");

    let mut passed = 0;
    for (i, (label, input, expected)) in tests.iter().enumerate() {
        let got = count_bits(*input);
        if got.as_slice() == *expected {
            passed += 1;
            println!("  Test {} ({}): PASS", i + 1, label);
        } else {
            println!("  Test {} ({}): FAIL", i + 1, label);
            println!("    Expected: {:?}", expected);
            println!("    Got:      {:?}", got);
        }
    }

    println!("\n  {}/{} passed", passed, tests.len());
    println!("============================================================\n");

    std::process::exit(if passed == tests.len() { 0 } else { 1 });
}
