/*
 * P467: Unique Substrings in Wraparound String [PREMIUM] (Medium)
 * https://leetcode.com/problems/unique-substrings-in-wraparound-string/
 * Topics: String, Dynamic Programming
 * 
 * We define the string base to be the infinite wraparound string of "abcdefghijklmnopqrstuvwxyz", so base will look like this:
 * Given a string s, return the number of unique non-empty substrings of s are present in base.
 * Example 1:
 *     Input: s = "a"
 *     Output: 1
 *     Explanation: Only the substring "a" of s is in base.
 * 
 * Example 2:
 *     Input: s = "cac"
 *     Output: 2
 *     Explanation: There are two substrings ("a", "c") of s in base.
 * 
 * Example 3:
 *     Input: s = "zab"
 *     Output: 6
 *     Explanation: There are six substrings ("z", "a", "b", "za", "ab", and "zab") of s in base.
 * 
 * Constraints:
 *     - 1 <= s.length <= 105
 *     - s consists of lowercase English letters.
 * 
 * Hint: One possible solution might be to consider allocating an array size of 26 for each character in the alphabet. (Credits to @r2ysxu)
 * 
 * Template (python3):
 *     class Solution:
 *         def findSubstringInWraproundString(self, s: str) -> int:
 */
use rstest;

fn find_substring_in_wrapround_string(s: &str) -> i32 {
    todo!()
}

fn main() {
    struct TC<'a> { label: &'a str, s: &'a str, expected: i32 }
    let tests: &[TC] = &[
        TC { label: "example 1", s: "a", expected: 1 },
        TC { label: "example 2", s: "cac", expected: 2 },
        TC { label: "example 3", s: "zab", expected: 6 },
        TC { label: "all same chars only a in wraparound", s: "aaaaa", expected: 1 },
        TC { label: "wraparound chain length 8", s: "zabcdefg", expected: 36 },
        TC { label: "full alphabet", s: "abcdefghijklmnopqrstuvwxyz", expected: 351 },
    ];
    let mut passed = 0;
    for (i, tc) in tests.iter().enumerate() {
        let got = find_substring_in_wrapround_string(tc.s);
        if got == tc.expected {
            passed += 1;
            println!("  Test {} ({}): PASS", i + 1, tc.label);
        } else {
            println!("  Test {} ({}): FAIL (expected {}, got {})", i + 1, tc.label, tc.expected, got);
        }
    }
    println!("\n  {}/{} passed", passed, tests.len());
    std::process::exit(if passed == tests.len() { 0 } else { 1 });
}
