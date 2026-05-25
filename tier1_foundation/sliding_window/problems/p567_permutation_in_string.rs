/*
 * P567: Permutation in String [PREMIUM] (Medium)
 * https://leetcode.com/problems/permutation-in-string/
 * Topics: Hash Table, Two Pointers, String, Sliding Window
 * 
 * Given two strings s1 and s2, return true if s2 contains a permutation of s1, or false otherwise.
 * In other words, return true if one of s1's permutations is the substring of s2.
 * Example 1:
 *     Input: s1 = "ab", s2 = "eidbaooo"
 *     Output: true
 *     Explanation: s2 contains one permutation of s1 ("ba").
 * 
 * Example 2:
 *     Input: s1 = "ab", s2 = "eidboaoo"
 *     Output: false
 * 
 * Constraints:
 *     - 1 <= s1.length, s2.length <= 104
 *     - s1 and s2 consist of lowercase English letters.
 * 
 * Hint: Obviously, brute force will result in TLE. Think of something else.
 * Hint: How will you check whether one string is a permutation of another string?
 * Hint: One way is to sort the string and then compare. But, Is there a better way?
 * Hint: If one string is a permutation of another string then they must have one common metric. What is that?
 * Hint: Both strings must have same character frequencies, if  one is permutation of another. Which data structure should be used to store frequencies?
 * Hint: What about hash table?  An array of size 26?
 * 
 * Template (python3):
 *     class Solution:
 *         def checkInclusion(self, s1: str, s2: str) -> bool:
 */
fn check_inclusion(s1: &str, s2: &str) -> bool {
    todo!()
}

fn main() {
    struct Test { label: &'static str, s1: &'static str, s2: &'static str, expected: bool }
    let tests: &[Test] = &[
        Test { label: "example 1", s1: "ab", s2: "eidbaooo", expected: true },
        Test { label: "example 2", s1: "ab", s2: "eidboaoo", expected: false },
        Test { label: "single char match", s1: "a", s2: "a", expected: true },
        Test { label: "permutation at end", s1: "adc", s2: "dcda", expected: true },
        Test { label: "no match large string", s1: "abc", s2: "ccccbbbbaaaa", expected: false },
        Test { label: "s1 longer than s2", s1: "ab", s2: "a", expected: false },
    ];
    let mut passed = 0;
    for (i, t) in tests.iter().enumerate() {
        let got = check_inclusion(t.s1, t.s2);
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
