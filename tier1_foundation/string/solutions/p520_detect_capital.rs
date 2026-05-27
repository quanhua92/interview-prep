/*
 * P520: Detect Capital [PREMIUM] (Easy)
 * https://leetcode.com/problems/detect-capital/
 * Topics: String
 *
 * We define the usage of capitals in a word to be right when one of the following cases holds:
 * Given a string word, return true if the usage of capitals in it is right.
 * Example 1:
 *     Input: word = "USA"
 *     Output: true
 *
 * Example 2:
 *     Input: word = "FlaG"
 *     Output: false
 *
 * Constraints:
 *     - 1 <= word.length <= 100
 *     - word consists of lowercase and uppercase English letters.
 *
 * Template (python3):
 *     class Solution:
 *         def detectCapitalUse(self, word: str) -> bool:
 */

use wasm_libs::*;

impl Solution {
    fn detect_capital_use(word: &str) -> bool {
        let upper: usize = word.chars().filter(|c| c.is_uppercase()).count();
        let len = word.len();
        let first_upper = word.chars().next().map(|c| c.is_uppercase()).unwrap_or(false);
        upper == len || upper == 0 || (first_upper && upper == 1)
    }
}

struct Solution;

fn main() {
    let word = read_line();
    write_bool(Solution::detect_capital_use(&word));
    std::process::exit(0);
}
