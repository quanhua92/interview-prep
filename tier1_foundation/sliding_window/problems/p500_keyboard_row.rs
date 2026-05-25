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
fn get_row(c: char) -> usize {
    todo!()
}

fn find_words<'a>(words: &'a [&'a str]) -> Vec<&'a str> {
    todo!()
}

fn main() {
    struct Test<'a> {
        input: &'a [&'a str],
        expected: &'a [&'a str],
        label: &'a str,
    }
    let tests: &[Test] = &[
        Test { input: &["Hello", "Alaska", "Dad", "Peace"], expected: &["Alaska", "Dad"], label: "example 1" },
        Test { input: &["omk"], expected: &[], label: "example 2" },
        Test { input: &["adsdf", "sfd"], expected: &["adsdf", "sfd"], label: "example 3" },
        Test { input: &["a", "b", "c"], expected: &["a", "b", "c"], label: "single letter words" },
        Test { input: &["qz", "asdf", "qzxc"], expected: &["asdf"], label: "mixed row words" },
        Test { input: &["typewriter"], expected: &["typewriter"], label: "entire top row word" },
    ];
    let total = tests.len();
    let mut passed = 0;
    for (i, tc) in tests.iter().enumerate() {
        let got = find_words(tc.input);
        if got == tc.expected {
            passed += 1;
            println!("  Test {} ({}): PASS", i + 1, tc.label);
        } else {
            println!("  Test {} ({}): FAIL", i + 1, tc.label);
            println!("    Expected: {:?}", tc.expected);
            println!("    Got:      {:?}", got);
        }
    }
    println!("\n  {}/{} passed", passed, total);
    std::process::exit(if passed == total { 0 } else { 1 });
}
