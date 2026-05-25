/*
 * P424: Longest Repeating Character Replacement (Medium)
 * https://leetcode.com/problems/longest-repeating-character-replacement/
 * Topics: Hash Table, String, Sliding Window
 * 
 * You are given a string s and an integer k. You can choose any character of the string and change it to any other uppercase English character. You can perform this operation at most k times.
 * Return the length of the longest substring containing the same letter you can get after performing the above operations.
 * 
 * Example 1:
 *     Input: s = "ABAB", k = 2
 *     Output: 4
 *     Explanation: Replace the two 'A's with two 'B's or vice versa.
 * 
 * Example 2:
 *     Input: s = "AABABBA", k = 1
 *     Output: 4
 *     Explanation: Replace the one 'A' in the middle with 'B' and form "AABBBBA".
 *     The substring "BBBB" has the longest repeating letters, which is 4.
 *     There may exists other ways to achieve this answer too.
 * 
 * Constraints:
 *     - 1 <= s.length <= 105
 *     - s consists of only uppercase English letters.
 *     - 0 <= k <= s.length
 * 
 * Template (python3):
 *     class Solution:
 *         def characterReplacement(self, s: str, k: int) -> int:
 * 
 * Hint: Freq map + max_freq tracker, window valid when len - max_freq <= k. Left only moves right.
 */
fn character_replacement(s: &str, k: i32) -> usize {
    todo!()
}

fn main() {
    struct Test { label: &'static str, input: &'static str, k: i32, expected: usize }
    let tests: &[Test] = &[
        Test { label: "example 1", input: "ABAB", k: 2, expected: 4 },
        Test { label: "example 2", input: "AABABBA", k: 1, expected: 4 },
        Test { label: "no changes needed", input: "AAAA", k: 0, expected: 4 },
        Test { label: "all unique", input: "ABCDE", k: 1, expected: 2 },
        Test { label: "single char, k=0", input: "A", k: 0, expected: 1 },
        Test { label: "single char, k > len", input: "A", k: 5, expected: 1 },
        Test { label: "no changes, partial run", input: "AAAB", k: 0, expected: 3 },
        Test { label: "change middle B to A", input: "ABAA", k: 2, expected: 4 },
    ];
    let mut passed = 0;
    for (i, t) in tests.iter().enumerate() {
        let got = character_replacement(t.input, t.k);
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
