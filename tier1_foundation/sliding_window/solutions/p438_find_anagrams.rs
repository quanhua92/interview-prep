/*
 * P438: Find All Anagrams in a String (Medium)
 * https://leetcode.com/problems/find-all-anagrams-in-a-string/
 * Topics: Hash Table, String, Sliding Window
 *
 * Given two strings s and p, return an array of all the start indices of p's anagrams in s. You may return the answer in any order.
 *
 * Example 1:
 *     Input: s = "cbaebabacd", p = "abc"
 *     Output: [0,6]
 *     Explanation:
 *     The substring with start index = 0 is "cba", which is an anagram of "abc".
 *     The substring with start index = 6 is "bac", which is an anagram of "abc".
 *
 * Example 2:
 *     Input: s = "abab", p = "ab"
 *     Output: [0,1,2]
 *     Explanation:
 *     The substring with start index = 0 is "ab", which is an anagram of "ab".
 *     The substring with start index = 1 is "ba", which is an anagram of "ab".
 *     The substring with start index = 2 is "ab", which is an anagram of "ab".
 *
 * Constraints:
 *     - 1 <= s.length, p.length <= 3 * 104
 *     - s and p consist of lowercase English letters.
 *
 * Template (python3):
 *     class Solution:
 *         def findAnagrams(self, s: str, p: str) -> List[int]:
 *
 * Hint: Use a sliding window with frequency counters to compare against pattern.
 */

use wasm_libs::*;

fn solve(s: &str, p: &str) -> Vec<i32> {
    let sb = s.as_bytes();
    let pb = p.as_bytes();
    let slen = sb.len();
    let plen = pb.len();
    let mut result = Vec::new();
    if plen > slen {
        return result;
    }
    let mut pf = [0i32; 26];
    let mut sf = [0i32; 26];
    for i in 0..plen {
        pf[(pb[i] - b'a') as usize] += 1;
        sf[(sb[i] - b'a') as usize] += 1;
    }
    if pf == sf {
        result.push(0);
    }
    for i in plen..slen {
        sf[(sb[i] - b'a') as usize] += 1;
        sf[(sb[i - plen] - b'a') as usize] -= 1;
        if pf == sf {
            result.push((i - plen + 1) as i32);
        }
    }
    result
}

fn main() {
    let s = read_line();
    let p = read_line();
    let result = solve(&s, &p);
    write_ints(&result);
    std::process::exit(0);
}
