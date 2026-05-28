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

use wasm_libs::*;

fn longest_palindrome_subseq(s: &str) -> i32 {
    let b = s.as_bytes();
    let n = b.len();
    if n == 0 { return 0; }
    let mut dp = vec![vec![0i32; n]; n];
    for i in 0..n { dp[i][i] = 1; }
    for length in 2..=n {
        for i in 0..=n - length {
            let j = i + length - 1;
            if b[i] == b[j] {
                dp[i][j] = if length == 2 { 2 } else { dp[i + 1][j - 1] + 2 };
            } else {
                dp[i][j] = dp[i + 1][j].max(dp[i][j - 1]);
            }
        }
    }
    dp[0][n - 1]
}

fn main() {
    let s = read_line();
    write_int(longest_palindrome_subseq(&s));
}
