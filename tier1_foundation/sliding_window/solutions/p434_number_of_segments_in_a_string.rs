/*
 * P434: Number of Segments in a String [PREMIUM] (Easy)
 * https://leetcode.com/problems/number-of-segments-in-a-string/
 * Topics: String
 *
 * Given a string s, return the number of segments in the string.
 * A segment is defined to be a contiguous sequence of non-space characters.
 * Example 1:
 *     Input: s = "Hello, my name is John"
 *     Output: 5
 *     Explanation: The five segments are ["Hello,", "my", "name", "is", "John"]
 *
 * Example 2:
 *     Input: s = "Hello"
 *     Output: 1
 *
 * Constraints:
 *     - 0 <= s.length <= 300
 *     - s consists of lowercase and uppercase English letters, digits, or one of the following characters "!@#$%^&*()_+-=',.:".
 *     - The only space character in s is ' '.
 *
 * Template (python3):
 *     class Solution:
 *         def countSegments(self, s: str) -> int:
 */


fn count_segments(s: &str) -> i32 {
    let mut count = 0;
    let mut in_segment = false;
    for c in s.chars() {
        if c != ' ' && !in_segment {
            count += 1;
            in_segment = true;
        } else if c == ' ' {
            in_segment = false;
        }
    }
    count
}

fn main() {
    struct Test<'a> {
        s: &'a str,
        expected: i32,
        label: &'a str,
    }
    let tests: &[Test] = &[
        Test { s: "Hello, my name is John", expected: 5, label: "example 1" },
        Test { s: "Hello", expected: 1, label: "example 2" },
        Test { s: "", expected: 0, label: "empty string" },
        Test { s: "   ", expected: 0, label: "only spaces" },
        Test { s: "    foo    bar   ", expected: 2, label: "leading/trailing/multiple spaces" },
        Test { s: "a b c d e", expected: 5, label: "single char segments" },
    ];
    let total = tests.len();
    let mut passed = 0;
    for (i, tc) in tests.iter().enumerate() {
        let got = count_segments(tc.s);
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
