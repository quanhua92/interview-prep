/*
 * P472: Concatenated Words [PREMIUM] (Hard)
 * https://leetcode.com/problems/concatenated-words/
 * Topics: Array, String, Dynamic Programming, Depth-First Search, Trie, Sorting
 *
 * Given an array of strings words (without duplicates), return all the concatenated words in the given list of words.
 * A concatenated word is defined as a string that is comprised entirely of at least two shorter words (not necessarily distinct) in the given array.
 * Example 1:
 *     Input: words = ["cat","cats","catsdogcats","dog","dogcatsdog","hippopotamuses","rat","ratcatdogcat"]
 *     Output: ["catsdogcats","dogcatsdog","ratcatdogcat"]
 *
 * Example 2:
 *     Input: words = ["cat","dog","catdog"]
 *     Output: ["catdog"]
 *
 * Template (python3):
 *     class Solution:
 *         def findAllConcatenatedWordsInADict(self, words: List[str]) -> List[str]:
 */

use wasm_libs::*;

fn find_all_concatenated_words(words: &mut Vec<String>) -> Vec<String> {
    todo!()
}

struct Solution;

fn main() {
    let nw = read_int() as usize;
    let mut words: Vec<String> = (0..nw).map(|_| read_line()).collect();

    let result = find_all_concatenated_words(&mut words);

    write_int(result.len() as i32);
    for w in &result {
        write_string(w);
    }

    std::process::exit(0);
}
