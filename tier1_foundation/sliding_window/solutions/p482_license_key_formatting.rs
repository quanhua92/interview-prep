/*
 * P482: License Key Formatting [PREMIUM] (Easy)
 * https://leetcode.com/problems/license-key-formatting/
 * Topics: String
 *
 * You are given a license key represented as a string s that consists of only alphanumeric characters and dashes. The string is separated into n + 1 groups by n dashes. You are also given an integer k.
 * We want to reformat the string s such that each group contains exactly k characters, except for the first group, which could be shorter than k but still must contain at least one character. Furthermore, there must be a dash inserted between two groups, and you should convert all lowercase letters to uppercase.
 * Return the reformatted license key.
 * Example 1:
 *     Input: s = "5F3Z-2e-9-w", k = 4
 *     Output: "5F3Z-2E9W"
 *     Explanation: The string s has been split into two parts, each part has 4 characters.
 *     Note that the two extra dashes are not needed and can be removed.
 *
 * Example 2:
 *     Input: s = "2-5g-3-J", k = 2
 *     Output: "2-5G-3J"
 *     Explanation: The string s has been split into three parts, each part has 2 characters except the first part as it could be shorter as mentioned above.
 *
 * Constraints:
 *     - 1 <= s.length <= 105
 *     - s consists of English letters, digits, and dashes '-'.
 *     - 1 <= k <= 104
 *
 * Template (python3):
 *     class Solution:
 *         def licenseKeyFormatting(self, s: str, k: int) -> str:
 */


fn license_key_formatting(s: &str, k: i32) -> String {
    let cleaned: Vec<char> = s.chars().filter(|&c| c != '-').map(|c| c.to_ascii_uppercase()).collect();
    let clen = cleaned.len();
    if clen == 0 {
        return String::new();
    }
    let k = k as usize;
    let first_len = clen % k;
    let mut result = String::new();
    if first_len > 0 {
        result.extend(&cleaned[..first_len]);
    }
    let mut i = first_len;
    while i < clen {
        if !result.is_empty() {
            result.push('-');
        }
        result.extend(&cleaned[i..i + k]);
        i += k;
    }
    result
}

fn main() {
    struct Test<'a> {
        s: &'a str,
        k: i32,
        expected: &'a str,
        label: &'a str,
    }
    let tests: &[Test] = &[
        Test { s: "5F3Z-2e-9-w", k: 4, expected: "5F3Z-2E9W", label: "example 1" },
        Test { s: "2-5g-3-J", k: 2, expected: "2-5G-3J", label: "example 2" },
        Test { s: "a", k: 1, expected: "A", label: "single char no dash" },
        Test { s: "---", k: 3, expected: "", label: "only dashes" },
        Test { s: "2-4A0r7-4k", k: 4, expected: "24A0-R74K", label: "even groups no short first" },
        Test { s: "aa-aa-aa-aa-aa-aa", k: 1, expected: "A-A-A-A-A-A-A-A-A-A-A-A", label: "k=1" },
    ];
    let total = tests.len();
    let mut passed = 0;
    for (i, tc) in tests.iter().enumerate() {
        let got = license_key_formatting(tc.s, tc.k);
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
