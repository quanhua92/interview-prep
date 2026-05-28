/*
 * P522: Longest Uncommon Subsequence II [PREMIUM] (Medium)
 * https://leetcode.com/problems/longest-uncommon-subsequence-ii/
 * Topics: Array, Hash Table, Two Pointers, String, Sorting
 *
 * Given an array of strings strs, return the length of the longest uncommon subsequence between them. If the longest uncommon subsequence does not exist, return -1.
 * An uncommon subsequence between an array of strings is a string that is a subsequence of one string but not the others.
 * A subsequence of a string s is a string that can be obtained after deleting any number of characters from s.
 * Example 1:
 *     Input: strs = ["aba","cdc","eae"]
 *     Output: 3
 *
 * Example 2:
 *     Input: strs = ["aaa","aaa","aa"]
 *     Output: -1
 *
 * Constraints:
 *     - 2 <= strs.length <= 50
 *     - 1 <= strs[i].length <= 10
 *     - strs[i] consists of lowercase English letters.
 *
 * Template (python3):
 *     class Solution:
 *         def findLUSlength(self, strs: List[str]) -> int:
 */

use wasm_libs::*;

impl Solution {
    fn is_subseq(a: &[u8], b: &[u8]) -> bool {
        todo!();
    }

    fn find_lus_length(strs: Vec<String>) -> i32 {
        todo!();
    }
}

struct Solution;

fn main() {
    let n = read_int();
    let mut strs = Vec::new();
    for _ in 0..n {
        strs.push(read_line());
    }
    write_int(Solution::find_lus_length(strs));
    std::process::exit(0);
}
