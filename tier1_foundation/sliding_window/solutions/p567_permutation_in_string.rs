/*
 * P567: Permutation in String [PREMIUM] (Medium)
 * https://leetcode.com/problems/permutation-in-string/
 * Topics: Hash Table, Two Pointers, String, Sliding Window
 *
 * Given two strings s1 and s2, return true if s2 contains a permutation of s1, or false otherwise.
 * In other words, return true if one of s1's permutations is the substring of s2.
 * Example 1:
 *     Input: s1 = "ab", s2 = "eidbaooo"
 *     Output: true
 *     Explanation: s2 contains one permutation of s1 ("ba").
 *
 * Example 2:
 *     Input: s1 = "ab", s2 = "eidboaoo"
 *     Output: false
 *
 * Constraints:
 *     - 1 <= s1.length, s2.length <= 104
 *     - s1 and s2 consist of lowercase English letters.
 *
 * Hint: Obviously, brute force will result in TLE. Think of something else.
 * Hint: How will you check whether one string is a permutation of another string?
 * Hint: One way is to sort the string and then compare. But, Is there a better way?
 * Hint: If one string is a permutation of another string then they must have one common metric. What is that?
 * Hint: Both strings must have same character frequencies, if  one is permutation of another. Which data structure should be used to store frequencies?
 * Hint: What about hash table?  An array of size 26?
 *
 * Template (python3):
 *     class Solution:
 *         def checkInclusion(self, s1: str, s2: str) -> bool:
 */

use wasm_libs::*;

fn solve(s1: &str, s2: &str) -> bool {
    let b1 = s1.as_bytes();
    let b2 = s2.as_bytes();
    let n1 = b1.len();
    let n2 = b2.len();
    if n1 > n2 {
        return false;
    }
    let mut f1 = [0i32; 26];
    let mut f2 = [0i32; 26];
    for i in 0..n1 {
        f1[(b1[i] - b'a') as usize] += 1;
        f2[(b2[i] - b'a') as usize] += 1;
    }
    if f1 == f2 {
        return true;
    }
    for i in n1..n2 {
        f2[(b2[i] - b'a') as usize] += 1;
        f2[(b2[i - n1] - b'a') as usize] -= 1;
        if f1 == f2 {
            return true;
        }
    }
    false
}

fn main() {
    let s1 = read_line();
    let s2 = read_line();
    let result = solve(&s1, &s2);
    write_bool(result);
    std::process::exit(0);
}
