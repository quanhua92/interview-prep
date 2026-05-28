/*
 * P524: Longest Word in Dictionary through Deleting [PREMIUM] (Medium)
 * https://leetcode.com/problems/longest-word-in-dictionary-through-deleting/
 * Topics: Array, Two Pointers, String, Sorting
 *
 * Given a string s and a string array dictionary, return the longest string in the dictionary that can be formed by deleting some of the given string characters. If there is more than one possible result, return the longest word with the smallest lexicographical order. If there is no possible result, return the empty string.
 * Example 1:
 *     Input: s = "abpcplea", dictionary = ["ale","apple","monkey","plea"]
 *     Output: "apple"
 *
 * Example 2:
 *     Input: s = "abpcplea", dictionary = ["a","b","c"]
 *     Output: "a"
 *
 * Constraints:
 *     - 1 <= s.length <= 1000
 *     - 1 <= dictionary.length <= 1000
 *     - 1 <= dictionary[i].length <= 1000
 *     - s and dictionary[i] consist of lowercase English letters.
 *
 * Template (python3):
 *     class Solution:
 *         def findLongestWord(self, s: str, dictionary: List[str]) -> str:
 */

use wasm_libs::*;

impl Solution {
    fn is_subseq(word: &[u8], target: &[u8]) -> bool {
        todo!();
    }

    fn find_longest_word(s: &str, dict: &[String]) -> String {
        todo!();
    }
}

struct Solution;

fn main() {
    let s = read_line();
    let dict_size = read_int();
    let mut dict = Vec::new();
    for _ in 0..dict_size {
        dict.push(read_line());
    }
    write_string(&Solution::find_longest_word(&s, &dict));
    std::process::exit(0);
}
