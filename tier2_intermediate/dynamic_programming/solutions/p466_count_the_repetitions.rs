/*
 * P466: Count The Repetitions [PREMIUM] (Hard)
 * https://leetcode.com/problems/count-the-repetitions/
 * Topics: String, Dynamic Programming
 *
 * We define str = [s, n] as the string str which consists of the string s concatenated n times.
 * We define that string s1 can be obtained from string s2 if we can remove some characters from s2 such that it becomes s1.
 * You are given two strings s1 and s2 and two integers n1 and n2. You have the two strings str1 = [s1, n1] and str2 = [s2, n2].
 * Return the maximum integer m such that str = [str2, m] can be obtained from str1.
 * Example 1:
 *     Input: s1 = "acb", n1 = 4, s2 = "ab", n2 = 2
 *     Output: 2
 *
 * Example 2:
 *     Input: s1 = "acb", n1 = 1, s2 = "acb", n2 = 1
 *     Output: 1
 *
 * Constraints:
 *     - 1 <= s1.length, s2.length <= 100
 *     - s1 and s2 consist of lowercase English letters.
 *     - 1 <= n1, n2 <= 106
 *
 * Template (python3):
 *     class Solution:
 *         def getMaxRepetitions(self, s1: str, n1: int, s2: str, n2: int) -> int:
 */

use wasm_libs::*;

impl Solution {
    fn get_max_repetitions(s1: &str, n1: i32, s2: &str, n2: i32) -> i32 {
    if n1 == 0 { return 0; }
    let s1b = s1.as_bytes(), s2b = s2.as_bytes();
    let s1_len = s1b.len(), s2_len = s2b.len();
    let mut s1_count = [0i32; 26];
    for &c in s1b { s1_count[(c - 97) as usize] += 1; }
    for &c in s2b { if s1_count[(c - 97) as usize] == 0 { return 0; } }
    let n1 = n1 as usize, n2 = n2 as i32;
    let mut prev_iter = [-1i32; 101], prev_count = [0i32; 101];
    let mut count = 0i32; let mut s2_idx = 0usize;
    'outer: for i in 0..n1 {
        for j in 0..s1_len {
            if s1b[j] == s2b[s2_idx] { s2_idx += 1; if s2_idx == s2_len { count += 1; s2_idx = 0; } }
        }
        if prev_iter[s2_idx] >= 0 {
            let cycle_len = i as i32 - prev_iter[s2_idx], cycle_count = count - prev_count[s2_idx];
            let remaining = (n1 - 1 - i) as i32, full_cycles = remaining / cycle_len;
            count += full_cycles * cycle_count;
            let processed = i + 1 + (full_cycles as usize) * (cycle_len as usize);
            for _ii in processed..n1 {
                for jj in 0..s1_len {
                    if s1b[jj] == s2b[s2_idx] { s2_idx += 1; if s2_idx == s2_len { count += 1; s2_idx = 0; } }
                }
            }
            break 'outer;
        }
        prev_iter[s2_idx] = i as i32; prev_count[s2_idx] = count;
    }
    count / n2
    }
}

struct Solution;

fn main() {
    let s1 = read_line();
    let n1 = read_int();
    let s2 = read_line();
    let n2 = read_int();
    write_int(get_max_repetitions(&s1, n1, &s2, n2));
}
