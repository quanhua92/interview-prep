/*
 * P556: Next Greater Element III [PREMIUM] (Medium)
 * https://leetcode.com/problems/next-greater-element-iii/
 * Topics: Math, Two Pointers, String
 * 
 * Given a positive integer n, find the smallest integer which has exactly the same digits existing in the integer n and is greater in value than n. If no such positive integer exists, return -1.
 * Note that the returned integer should fit in 32-bit integer, if there is a valid answer but it does not fit in 32-bit integer, return -1.
 * Example 1:
 *     Input: n = 12
 *     Output: 21
 * 
 * Example 2:
 *     Input: n = 21
 *     Output: -1
 * 
 * Constraints:
 *     - 1 <= n <= 231 - 1
 * 
 * Template (python3):
 *     class Solution:
 *         def nextGreaterElement(self, n: int) -> int:
 */
fn next_greater_element(n: i32) -> i32 {
    todo!()
}

fn main() {
    println!("\n============================================================");
    println!("  556. Next Greater Element III");
    println!("============================================================");
    let tests: &[(&str, i32, i32)] = &[
        ("example 1", 12, 21),
        ("example 2", 21, -1),
        ("single digit", 1, -1),
        ("all same digits", 11, -1),
        ("classic example", 230241, 230412),
        ("max 32-bit int", 2147483647, -1),
    ];
    let mut passed = 0;
    for (i, (label, input, expected)) in tests.iter().enumerate() {
        let got = next_greater_element(*input);
        if got == *expected {
            passed += 1;
            println!("  Test {} ({}): PASS", i + 1, label);
        } else {
            println!("  Test {} ({}): FAIL", i + 1, label);
            println!("    Expected: {}, Got: {}", expected, got);
        }
    }
    println!("\n  {}/{} passed", passed, tests.len());
    println!("============================================================\n");
    std::process::exit(if passed == tests.len() { 0 } else { 1 });
}
