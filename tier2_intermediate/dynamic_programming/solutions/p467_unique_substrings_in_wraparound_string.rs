/*
 * P467: Unique Substrings in Wraparound String [PREMIUM] (Medium)
 * https://leetcode.com/problems/unique-substrings-in-wraparound-string/
 * Topics: String, Dynamic Programming
 *
 * We define the string base to be the infinite wraparound string of "abcdefghijklmnopqrstuvwxyz", so base will look like this:
 * Given a string s, return the number of unique non-empty substrings of s are present in base.
 * Example 1:
 *     Input: s = "a"
 *     Output: 1
 *     Explanation: Only the substring "a" of s is in base.
 *
 * Example 2:
 *     Input: s = "cac"
 *     Output: 2
 *     Explanation: There are two substrings ("a", "c") of s in base.
 *
 * Example 3:
 *     Input: s = "zab"
 *     Output: 6
 *     Explanation: There are six substrings ("z", "a", "b", "za", "ab", and "zab") of s in base.
 *
 * Constraints:
 *     - 1 <= s.length <= 105
 *     - s consists of lowercase English letters.
 *
 * Hint: One possible solution might be to consider allocating an array size of 26 for each character in the alphabet. (Credits to @r2ysxu)
 *
 * Template (python3):
 *     class Solution:
 *         def findSubstringInWraproundString(self, s: str) -> int:
 */

use wasm_libs::*;

impl Solution {
    fn find_substring_in_wrapround_string(s: &str) -> i32 {
        let bytes = s.as_bytes();
    let mut max_len = [0i32; 26];
    let mut curr = 0i32;
    for i in 0..bytes.len() {
        if i > 0 && (bytes[i] - bytes[i - 1] == 1 || bytes[i - 1] - bytes[i] == 25) {
            curr += 1;
        } else {
            curr = 1;
        }
        let idx = (bytes[i] - b'a') as usize;
        if curr > max_len[idx] { max_len[idx] = curr; }
    }
    max_len.iter().sum()
    }
}

struct Solution;

fn main() {
    let s = read_line();
    write_int(find_substring_in_wrapround_string(&s));
}
