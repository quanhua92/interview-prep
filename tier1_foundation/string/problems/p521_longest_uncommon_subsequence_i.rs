/*
 * P521: Longest Uncommon Subsequence I [PREMIUM] (Easy)
 * https://leetcode.com/problems/longest-uncommon-subsequence-i/
 * Topics: String
 * 
 * Given two strings a and b, return the length of the longest uncommon subsequence between a and b. If no such uncommon subsequence exists, return -1.
 * An uncommon subsequence between two strings is a string that is a subsequence of exactly one of them.
 * Example 1:
 *     Input: a = "aba", b = "cdc"
 *     Output: 3
 *     Explanation: One longest uncommon subsequence is "aba" because "aba" is a subsequence of "aba" but not "cdc".
 *     Note that "cdc" is also a longest uncommon subsequence.
 * 
 * Example 2:
 *     Input: a = "aaa", b = "bbb"
 *     Output: 3
 *     Explanation: The longest uncommon subsequences are "aaa" and "bbb".
 * 
 * Example 3:
 *     Input: a = "aaa", b = "aaa"
 *     Output: -1
 *     Explanation: Every subsequence of string a is also a subsequence of string b. Similarly, every subsequence of string b is also a subsequence of string a. So the answer would be -1.
 * 
 * Constraints:
 *     - 1 <= a.length, b.length <= 100
 *     - a and b consist of lower-case English letters.
 * 
 * Hint: Think very simple.
 * Hint: If <code>a == b</code>, the answer is -1.
 * Hint: Otherwise, the answer is the string <code>a</code> or the string <code>b</code>.
 * 
 * Template (python3):
 *     class Solution:
 *         def findLUSlength(self, a: str, b: str) -> int:
 */
fn find_luslength(a: &str, b: &str) -> i32 {
    todo!()
}

fn main() {
    struct Test<'a> {
        a: &'a str,
        b: &'a str,
        expected: i32,
        label: &'a str,
    }
    let tests: &[Test] = &[
        Test { a: "aba", b: "cdc", expected: 3, label: "example 1" },
        Test { a: "aaa", b: "bbb", expected: 3, label: "example 2" },
        Test { a: "aaa", b: "aaa", expected: -1, label: "example 3" },
        Test { a: "a", b: "b", expected: 1, label: "single char different" },
        Test { a: "a", b: "aa", expected: 2, label: "one is subsequence of other" },
        Test { a: "abc", b: "abcde", expected: 5, label: "one longer than other" },
    ];
    let total = tests.len();
    let mut passed = 0;
    for (i, tc) in tests.iter().enumerate() {
        let got = find_luslength(tc.a, tc.b);
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
