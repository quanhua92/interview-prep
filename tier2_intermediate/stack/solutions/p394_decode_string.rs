/*
 * P394: Decode String (Medium)
 * https://leetcode.com/problems/decode-string/
 * Topics: String, Stack, Recursion
 *
 * Given an encoded string, return its decoded string.
 * The encoding rule is: k[encoded_string], where the encoded_string inside the square brackets is being repeated exactly k times. Note that k is guaranteed to be a positive integer.
 * You may assume that the input string is always valid; there are no extra white spaces, square brackets are well-formed, etc. Furthermore, you may assume that the original data does not contain any digits and that digits are only for those repeat numbers, k. For example, there will not be input like 3a or 2[4].
 * The test cases are generated so that the length of the output will never exceed 105.
 *
 * Example 1:
 *     Input: s = "3[a]2[bc]"
 *     Output: "aaabcbc"
 *
 * Example 2:
 *     Input: s = "3[a2[c]]"
 *     Output: "accaccacc"
 *
 * Example 3:
 *     Input: s = "2[abc]3[cd]ef"
 *     Output: "abcabccdcdcdef"
 *
 * Constraints:
 *     - 1 <= s.length <= 30
 *     - s consists of lowercase English letters, digits, and square brackets '[]'.
 *     - s is guaranteed to be a valid input.
 *     - All the integers in s are in the range [1, 300].
 *
 * Template (python3):
 *     class Solution:
 *         def decodeString(self, s: str) -> str:
 *
 * Hint: Use a stack to handle nested k[encoded] patterns.
 */

#[allow(unused_imports)]
use rstest;

fn decode_string(s: &str) -> String {
    let mut num_stack: Vec<(i32, usize)> = Vec::new();
    let mut result: Vec<u8> = Vec::new();
    let mut curr_num = 0;

    for ch in s.bytes() {
        if ch.is_ascii_digit() {
            curr_num = curr_num * 10 + (ch - b'0') as i32;
        } else if ch == b'[' {
            num_stack.push((curr_num, result.len()));
            curr_num = 0;
        } else if ch == b']' {
            let (repeat, start) = num_stack.pop().unwrap();
            let seg: Vec<u8> = result[start..].to_vec();
            for _ in 1..repeat {
                result.extend_from_slice(&seg);
            }
        } else {
            result.push(ch);
        }
    }

    String::from_utf8(result).unwrap()
}

fn main() {
    struct TestCase {
        label: &'static str,
        input: &'static str,
        expected: &'static str,
    }

    let tests: &[TestCase] = &[
        TestCase { label: "example 1", input: "3[a]2[bc]", expected: "aaabcbc" },
        TestCase { label: "nested", input: "3[a2[c]]", expected: "accaccacc" },
        TestCase { label: "multiple segments", input: "2[abc]3[cd]ef", expected: "abcabccdcdcdef" },
        TestCase { label: "no encoding", input: "abc", expected: "abc" },
        TestCase { label: "multi-digit multiplier", input: "10[a]", expected: "aaaaaaaaaa" },
        TestCase { label: "deep nesting", input: "2[2[2[a]]]", expected: "aaaaaaaa" },
        TestCase { label: "encoded then plain", input: "3[a]b", expected: "aaab" },
        TestCase { label: "plain-enc-plain", input: "a2[b]c", expected: "abbc" },
    ];

    println!("\n============================================================");
    println!("  394. Decode String");
    println!("============================================================");

    let mut passed = 0;
    for (i, tc) in tests.iter().enumerate() {
        let got = decode_string(tc.input);
        if got == tc.expected {
            passed += 1;
            println!("  Test {} ({}): PASS", i + 1, tc.label);
        } else {
            println!("  Test {} ({}): FAIL", i + 1, tc.label);
            println!("    Expected: {}", tc.expected);
            println!("    Got:      {}", got);
        }
    }

    println!("\n  {}/{} passed", passed, tests.len());
    println!("============================================================\n");

    std::process::exit(if passed == tests.len() { 0 } else { 1 });
}
