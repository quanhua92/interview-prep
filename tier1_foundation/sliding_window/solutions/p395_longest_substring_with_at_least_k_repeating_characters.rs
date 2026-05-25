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
    let k = k as usize;
    let bytes = s.as_bytes();
    let n = bytes.len();
    let mut max_len = 0usize;
    for t in 1..=26 {
        let mut freq = [0i32; 26];
        let mut left = 0usize;
        let mut unique = 0i32;
        let mut at_least_k = 0i32;
        for right in 0..n {
            let idx = (bytes[right] - b'a') as usize;
            freq[idx] += 1;
            if freq[idx] == 1 {
                unique += 1;
            }
            if freq[idx] == k as i32 {
                at_least_k += 1;
            }
            while unique > t as i32 {
                let lidx = (bytes[left] - b'a') as usize;
                if freq[lidx] == k as i32 {
                    at_least_k -= 1;
                }
                freq[lidx] -= 1;
                if freq[lidx] == 0 {
                    unique -= 1;
                }
                left += 1;
            }
            if unique == t as i32 && at_least_k == t as i32 {
                let cur = right - left + 1;
                if cur > max_len {
                    max_len = cur;
                }
            }
        }
    }
    max_len as i32
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
