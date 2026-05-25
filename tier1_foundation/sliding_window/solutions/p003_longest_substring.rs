/*
 * P3: Longest Substring Without Repeating Characters (Medium)
 * https://leetcode.com/problems/longest-substring-without-repeating-characters/
 * Topics: Hash Table, String, Sliding Window
 *
 * Given a string s, find the length of the longest substring without duplicate characters.
 *
 * Example 1:
 *     Input: s = "abcabcbb"
 *     Output: 3
 *     Explanation: The answer is "abc", with the length of 3.
 *
 * Example 2:
 *     Input: s = "bbbbb"
 *     Output: 1
 *     Explanation: The answer is "b", with the length of 1.
 *
 * Example 3:
 *     Input: s = "pwwkew"
 *     Output: 3
 *     Explanation: The answer is "wke", with the length of 3.
 *     Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.
 *
 * Constraints:
 *     - 0 <= s.length <= 5 * 104
 *     - s consists of English letters, digits, symbols and spaces.
 *
 * Hints:
 *     - Generate all possible substrings & check for each substring if it's valid and keep updating maxLen accordingly.
 *
 * Template (python3):
 *     class Solution:
 *         def lengthOfLongestSubstring(self, s: str) -> int:
 *
 * Hint: Use a hash map to track the last index of each character.
 */


use std::collections::HashMap;

fn length_of_longest_substring(s: &str) -> usize {
    let mut last: HashMap<char, usize> = HashMap::new();
    let mut left = 0;
    let mut max_len = 0;
    for (i, c) in s.char_indices() {
        if let Some(&prev) = last.get(&c) {
            if prev >= left {
                left = prev + 1;
            }
        }
        last.insert(c, i);
        let len = i - left + 1;
        if len > max_len {
            max_len = len;
        }
    }
    max_len
}

fn main() {
    struct Test { label: &'static str, input: &'static str, expected: usize }
    let tests: &[Test] = &[
        Test { label: "example 1", input: "abcabcbb", expected: 3 },
        Test { label: "example 2", input: "bbbbb", expected: 1 },
        Test { label: "example 3", input: "pwwkew", expected: 3 },
        Test { label: "empty string", input: "", expected: 0 },
        Test { label: "single character", input: "a", expected: 1 },
        Test { label: "single space", input: " ", expected: 1 },
        Test { label: "two unique chars", input: "au", expected: 2 },
        Test { label: "reset from duplicate after unique prefix", input: "dvdf", expected: 3 },
        Test { label: "char seen before current window", input: "tmmzuxt", expected: 5 },
    ];
    let mut passed = 0;
    for (i, t) in tests.iter().enumerate() {
        let got = length_of_longest_substring(t.input);
        if got == t.expected {
            println!("  Test {} ({}): PASS", i + 1, t.label);
            passed += 1;
        } else {
            println!("  Test {} ({}): FAIL", i + 1, t.label);
            println!("    Expected: {}\n    Got: {}", t.expected, got);
        }
    }
    println!("\n  {}/{} passed", passed, tests.len());
    std::process::exit(if passed == tests.len() { 0 } else { 1 });
}
