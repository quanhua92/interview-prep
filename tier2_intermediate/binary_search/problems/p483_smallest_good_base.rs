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
 *     - n is an integer in the range [3, 1018].
 *     - n does not contain any leading zeros.
 * 
 * Template (python3):
 *     class Solution:
 *         def smallestGoodBase(self, n: str) -> str:
 */
fn calc(k: i64, m: i32, num: i64) -> i64 {
    todo!()
}

fn smallest_good_base(n: &str) -> String {
    todo!()
}

fn main() {
    let tests: Vec<(&str, &str, &str)> = vec![
        ("example 1", "13", "3"),
        ("example 2", "4681", "8"),
        ("example 3", "1000000000000000000", "999999999999999999"),
        ("smallest n equals 11 base 2", "3", "2"),
        ("111 base 2", "7", "2"),
        ("11111 base 2", "31", "2"),
    ];

    let mut passed = 0;
    println!("\n============================================================");
    println!("  483. Smallest Good Base");
    println!("============================================================");
    for (i, (label, input, expected)) in tests.iter().enumerate() {
        let got = smallest_good_base(input);
        let ok = got == *expected;
        if ok { passed += 1; }
        println!("  Test {} ({}): {}", i + 1, label, if ok { "PASS" } else { "FAIL" });
    }
    println!("\n  {}/{} passed", passed, tests.len());
    println!("============================================================\n");
    std::process::exit(if passed == tests.len() { 0 } else { 1 });
}
