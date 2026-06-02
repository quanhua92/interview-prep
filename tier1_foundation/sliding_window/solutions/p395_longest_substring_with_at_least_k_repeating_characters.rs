/*
 * P395: Longest Substring with At Least K Repeating Characters [PREMIUM] (Medium)
 * https://leetcode.com/problems/longest-substring-with-at-least-k-repeating-characters/
 * Topics: Hash Table, String, Divide and Conquer, Sliding Window
 *
 * Given a string s and an integer k, return the length of the longest substring of s such that the frequency of each character in this substring is greater than or equal to k.
 * if no such substring exists, return 0.
 * Example 1:
 *     Input: s = "aaabb", k = 3
 *     Output: 3
 *     Explanation: The longest substring is "aaa", as 'a' is repeated 3 times.
 *
 * Example 2:
 *     Input: s = "ababbc", k = 2
 *     Output: 5
 *     Explanation: The longest substring is "ababb", as 'a' is repeated 2 times and 'b' is repeated 3 times.
 *
 * Constraints:
 *     - 1 <= s.length <= 10^4
 *     - s consists of only lowercase English letters.
 *     - 1 <= k <= 10^5
 *
 * Template (python3):
 *     class Solution:
 *         def longestSubstring(self, s: str, k: int) -> int:
 */

use wasm_libs::*;

fn solve(s: &str, k: i32) -> i32 {
    let k = k as usize;
    let bytes = s.as_bytes();
    let n = bytes.len();
    let mut max_len = 0usize;
    for t in 1..=26 {
        let mut freq = [0i32; 26];
        let mut left = 0usize;
        let mut unique = 0i32;
        let mut at_least_k = 0i32;
        for right in 0..n {
            let idx = (bytes[right] - b'a') as usize;
            freq[idx] += 1;
            if freq[idx] == 1 {
                unique += 1;
            }
            if freq[idx] == k as i32 {
                at_least_k += 1;
            }
            while unique > t as i32 {
                let lidx = (bytes[left] - b'a') as usize;
                if freq[lidx] == k as i32 {
                    at_least_k -= 1;
                }
                freq[lidx] -= 1;
                if freq[lidx] == 0 {
                    unique -= 1;
                }
                left += 1;
            }
            if unique == t as i32 && at_least_k == t as i32 {
                let cur = right - left + 1;
                if cur > max_len {
                    max_len = cur;
                }
            }
        }
    }
    max_len as i32
}

fn main() {
    let s = read_line();
    let k = read_int();
    let result = solve(&s, k);
    write_int(result);
    std::process::exit(0);
}
