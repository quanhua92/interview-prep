/*
 * P395: Longest Substring with At Least K Repeating Characters [PREMIUM] (Medium)
 * https://leetcode.com/problems/longest-substring-with-at-least-k-repeating-characters/
 * Topics: Hash Table, String, Divide and Conquer, Sliding Window
 * 
 * Given a string s and an integer k, return the length of the longest substring of s such that the frequency of each character in this substring is greater than or equal to k.
 * if no such substring exists, return 0.
 * Example 1:
 *     Input: s = "aaabb", k = 3
 *     Output: 3
 *     Explanation: The longest substring is "aaa", as 'a' is repeated 3 times.
 * 
 * Example 2:
 *     Input: s = "ababbc", k = 2
 *     Output: 5
 *     Explanation: The longest substring is "ababb", as 'a' is repeated 2 times and 'b' is repeated 3 times.
 * 
 * Constraints:
 *     - 1 <= s.length <= 104
 *     - s consists of only lowercase English letters.
 *     - 1 <= k <= 105
 * 
 * Template (python3):
 *     class Solution:
 *         def longestSubstring(self, s: str, k: int) -> int:
 */
fn longest_substring(s: &str, k: i32) -> i32 {
    todo!()
}

fn main() {
    struct Test<'a> {
        s: &'a str,
        k: i32,
        expected: i32,
        label: &'a str,
    }
    let tests: &[Test] = &[
        Test { s: "aaabb", k: 3, expected: 3, label: "example 1" },
        Test { s: "ababbc", k: 2, expected: 5, label: "example 2" },
        Test { s: "ababacb", k: 3, expected: 0, label: "no valid substring" },
        Test { s: "a", k: 1, expected: 1, label: "single char k=1" },
        Test { s: "a", k: 2, expected: 0, label: "single char k>1" },
        Test { s: "bbaaacbd", k: 3, expected: 3, label: "multiple runs" },
    ];
    let total = tests.len();
    let mut passed = 0;
    for (i, tc) in tests.iter().enumerate() {
        let got = longest_substring(tc.s, tc.k);
        if got == tc.expected {
            passed += 1;
            println!("  Test {} ({}): PASS", i + 1, tc.label);
        } else {
            println!("  Test {} ({}): FAIL", i + 1, tc.label);
            println!("    Expected: {}", tc.expected);
            println!("    Got:      {}", got);
        }
    }
    println!("\n  {}/{} passed", passed, total);
    std::process::exit(if passed == total { 0 } else { 1 });
}
