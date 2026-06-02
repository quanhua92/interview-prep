/*
 * P424: Longest Repeating Character Replacement (Medium)
 * https://leetcode.com/problems/longest-repeating-character-replacement/
 * Topics: Hash Table, String, Sliding Window
 *
 * You are given a string s and an integer k. You can choose any character of the string and change it to any other uppercase English character. You can perform this operation at most k times.
 * Return the length of the longest substring containing the same letter you can get after performing the above operations.
 *
 * Example 1:
 *     Input: s = "ABAB", k = 2
 *     Output: 4
 *     Explanation: Replace the two 'A's with two 'B's or vice versa.
 *
 * Example 2:
 *     Input: s = "AABABBA", k = 1
 *     Output: 4
 *     Explanation: Replace the one 'A' in the middle with 'B' and form "AABBBBA".
 *     The substring "BBBB" has the longest repeating letters, which is 4.
 *     There may exists other ways to achieve this answer too.
 *
 * Constraints:
 *     - 1 <= s.length <= 10^5
 *     - s consists of only uppercase English letters.
 *     - 0 <= k <= s.length
 *
 * Template (python3):
 *     class Solution:
 *         def characterReplacement(self, s: str, k: int) -> int:
 *
 * Hint: Freq map + max_freq tracker, window valid when len - max_freq <= k. Left only moves right.
 */

use wasm_libs::*;

fn solve(s: &str, k: i32) -> usize {
    let bytes = s.as_bytes();
    let mut freq = [0i32; 26];
    let mut max_freq = 0i32;
    let mut left = 0usize;
    let mut max_len = 0usize;
    for i in 0..bytes.len() {
        let idx = (bytes[i] - b'A') as usize;
        freq[idx] += 1;
        if freq[idx] > max_freq {
            max_freq = freq[idx];
        }
        while (i - left + 1) as i32 - max_freq > k {
            freq[(bytes[left] - b'A') as usize] -= 1;
            left += 1;
        }
        if i - left + 1 > max_len {
            max_len = i - left + 1;
        }
    }
    max_len
}

fn main() {
    let s = read_line();
    let k = read_int();
    let result = solve(&s, k);
    write_int(result as i32);
    std::process::exit(0);
}
