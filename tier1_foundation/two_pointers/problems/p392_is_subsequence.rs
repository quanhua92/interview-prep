/*
 * P392: Is Subsequence [PREMIUM] (Easy)
 * https://leetcode.com/problems/is-subsequence/
 * Topics: Two Pointers, String, Dynamic Programming
 * 
 * Given two strings s and t, return true if s is a subsequence of t, or false otherwise.
 * A subsequence of a string is a new string that is formed from the original string by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters. (i.e., "ace" is a subsequence of "abcde" while "aec" is not).
 * Example 1:
 *     Input: s = "abc", t = "ahbgdc"
 *     Output: true
 * 
 * Example 2:
 *     Input: s = "axc", t = "ahbgdc"
 *     Output: false
 * 
 * Constraints:
 *     - 0 <= s.length <= 100
 *     - 0 <= t.length <= 104
 *     - s and t consist only of lowercase English letters.
 * 
 * Template (python3):
 *     class Solution:
 *         def isSubsequence(self, s: str, t: str) -> bool:
 */
fn is_subsequence(s: &str, t: &str) -> bool {
    todo!()
}

fn main() {
    struct Case<'a> { label: &'a str, s: &'a str, t: &'a str, expected: bool }
    let tests: &[Case] = &[
        Case { label: "example 1", s: "abc", t: "ahbgdc", expected: true },
        Case { label: "example 2", s: "axc", t: "ahbgdc", expected: false },
        Case { label: "empty s is subsequence", s: "", t: "ahbgdc", expected: true },
        Case { label: "s equals t", s: "abc", t: "abc", expected: true },
        Case { label: "s longer than t", s: "abcd", t: "abc", expected: false },
        Case { label: "single char not found", s: "z", t: "aaaaa", expected: false },
    ];

    println!("\n============================================================");
    println!("  392. Is Subsequence");
    println!("============================================================");
    let mut passed = 0;
    for (i, tc) in tests.iter().enumerate() {
        let got = is_subsequence(tc.s, tc.t);
        if got == tc.expected {
            passed += 1;
            println!("  Test {} ({}): PASS", i + 1, tc.label);
        } else {
            println!("  Test {} ({}): FAIL", i + 1, tc.label);
            println!("    Expected: {:?}\n    Got:      {:?}", tc.expected, got);
        }
    }
    println!("\n  {}/{} passed", passed, tests.len());
    println!("============================================================\n");
    std::process::exit(if passed == tests.len() { 0 } else { 1 });
}
