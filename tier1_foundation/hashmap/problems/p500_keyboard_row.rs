/*
 * P500: Keyboard Row [PREMIUM] (Easy)
 * https://leetcode.com/problems/keyboard-row/
 * Topics: Array, Hash Table, String
 *
 * Given an array of strings words, return the words that can be typed using letters of the alphabet on only one row of American keyboard like the image below.
 * Note that the strings are case-insensitive, both lowercased and uppercased of the same letter are treated as if they are at the same row.
 * In the American keyboard:
 * Example 1:
 *     Input: words = ["Hello","Alaska","Dad","Peace"]
 *     Output: ["Alaska","Dad"]
 *     Explanation:
 *     Both "a" and "A" are in the 2nd row of the American keyboard due to case insensitivity.
 *
 * Example 2:
 *     Input: words = ["omk"]
 *     Output: []
 *
 * Example 3:
 *     Input: words = ["adsdf","sfd"]
 *     Output: ["adsdf","sfd"]
 *
 * Constraints:
 *     - 1 <= words.length <= 20
 *     - 1 <= words[i].length <= 100
 *     - words[i] consists of English letters (both lowercase and uppercase).
 *
 * Template (python3):
 *     class Solution:
 *         def findWords(self, words: List[str]) -> List[str]:
 */

use wasm_libs::*;

fn get_row(c: char) -> usize {
    todo!();
}

fn find_words(words: &[String]) -> Vec<String> {
    todo!();
}

fn main() {
    let header = read_ints();
    let n = header[0] as usize;
    let mut words: Vec<String> = Vec::new();
    for _ in 0..n {
        words.push(read_line());
    }
    let result = find_words(&words);
    for w in &result {
        write_string(w);
    }
    std::process::exit(0);
}
