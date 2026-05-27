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
        let mut i = 0;
        for &ch in b {
            if i < a.len() && a[i] == ch {
                i += 1;
            }
        }
        i == a.len()
    }

    fn find_lus_length(strs: Vec<String>) -> i32 {
        let mut strs: Vec<String> = strs;
        strs.sort_by(|a, b| b.len().cmp(&a.len()));
        let n = strs.len();

        for i in 0..n {
            let mut uncommon = true;
            for j in 0..n {
                if i != j && Solution::is_subseq(strs[i].as_bytes(), strs[j].as_bytes()) {
                    uncommon = false;
                    break;
                }
            }
            if uncommon {
                return strs[i].len() as i32;
            }
        }
        -1
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
