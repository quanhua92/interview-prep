/*
 * P516: Longest Palindromic Subsequence [PREMIUM] (Medium)
 * https://leetcode.com/problems/longest-palindromic-subsequence/
 * Topics: String, Dynamic Programming
 * 
 * Given a string s, find the longest palindromic subsequence's length in s.
 * A subsequence is a sequence that can be derived from another sequence by deleting some or no elements without changing the order of the remaining elements.
 * Example 1:
 *     Input: s = "bbbab"
 *     Output: 4
 *     Explanation: One possible longest palindromic subsequence is "bbbb".
 * 
 * Example 2:
 *     Input: s = "cbbd"
 *     Output: 2
 *     Explanation: One possible longest palindromic subsequence is "bb".
 * 
 * Constraints:
 *     - 1 <= s.length <= 1000
 *     - s consists only of lowercase English letters.
 * 
 * Template (python3):
 *     class Solution:
 *         def longestPalindromeSubseq(self, s: str) -> int:
 */
use rstest;

fn longest_palindrome_subseq(s: &str) -> i32 {
    todo!()
}

fn main() {
    struct TC<'a> { label: &'a str, s: &'a str, expected: i32 }
    let tests: &[TC] = &[
        TC { label: "example 1", s: "bbbab", expected: 4 },
        TC { label: "example 2", s: "cbbd", expected: 2 },
        TC { label: "single char", s: "a", expected: 1 },
        TC { label: "two same chars", s: "aa", expected: 2 },
        TC { label: "all distinct", s: "abcdef", expected: 1 },
        TC { label: "full palindrome", s: "aabbaa", expected: 6 },
    ];
    let mut passed = 0;
    for (i, tc) in tests.iter().enumerate() {
        let got = longest_palindrome_subseq(tc.s);
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
