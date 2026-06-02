/*
 * P564: Find the Closest Palindrome [PREMIUM] (Hard)
 * https://leetcode.com/problems/find-the-closest-palindrome/
 * Topics: Math, String
 *
 * Given a string n representing an integer, return the closest integer (not including itself), which is a palindrome. If there is a tie, return the smaller one.
 * The closest is defined as the absolute difference minimized between two integers.
 * Example 1:
 *     Input: n = "123"
 *     Output: "121"
 *
 * Example 2:
 *     Input: n = "1"
 *     Output: "0"
 *     Explanation: 0 and 2 are the closest palindromes but we return the smallest which is 0.
 *
 * Constraints:
 *     - 1 <= n.length <= 18
 *     - n consists of only digits.
 *     - n does not have leading zeros.
 *     - n is representing an integer in the range [1, 10^18 - 1].
 *
 * Hint: Will brute force work for this problem? Think of something else.
 * Hint: Take some examples like 1234, 999,1000, etc and check their closest palindromes. How many different cases are possible?
 * Hint: Do we have to consider only left half or right half of the string or both?
 * Hint: Try to find the closest palindrome of these numbers- 12932, 99800, 12120. Did you observe something?
 *
 * Template (python3):
 *     class Solution:
 *         def nearestPalindromic(self, n: str) -> str:
 */

use wasm_libs::*;
use std::collections::BTreeSet;

fn make_palindrome(prefix: i64, total_len: usize) -> i64 {
    let p = prefix.to_string();
    let candidate_str = if total_len % 2 == 0 {
        let rev: String = p.chars().rev().collect();
        format!("{}{}", p, rev)
    } else {
        let suffix = &p[..p.len().saturating_sub(1)];
        let rev: String = suffix.chars().rev().collect();
        format!("{}{}", p, rev)
    };
    candidate_str.parse::<i64>().unwrap_or(0)
}

fn nearest_palindromic(n: &str) -> String {
    let num: i64 = n.parse().unwrap();
    if num <= 10 { return (num - 1).to_string(); }
    let len = n.len();
    let half = &n[..(len + 1) / 2];
    let prefix: i64 = half.parse().unwrap();
    let mut cands: BTreeSet<i64> = BTreeSet::new();
    for d in -1i64..=1 {
        cands.insert(make_palindrome(prefix + d, len));
    }
    if len > 1 { cands.insert(10i64.pow(len as u32 - 1) - 1); }
    cands.insert(10i64.pow(len as u32) + 1);
    cands.remove(&num);
    let best = cands.iter().min_by_key(|&&c| (c.abs_diff(num), c)).copied().unwrap_or(0);
    best.to_string()
}

fn main() {
    let n = read_line();
    write_string(&nearest_palindromic(&n));
    std::process::exit(0);
}
