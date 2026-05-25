/*
 * P20: Valid Parentheses (Easy)
 * https://leetcode.com/problems/valid-parentheses/
 * Topics: String, Stack
 * 
 * Given a string s containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.
 * An input string is valid if:
 * 
 * Example 1:
 *     Input: s = "()"
 *     Output: true
 * 
 * Example 2:
 *     Input: s = "()[]{}"
 *     Output: true
 * 
 * Example 3:
 *     Input: s = "(]"
 *     Output: false
 * 
 * Example 4:
 *     Input: s = "([])"
 *     Output: true
 * 
 * Example 5:
 *     Input: s = "([)]"
 *     Output: false
 * 
 * Constraints:
 *     - 1 <= s.length <= 104
 *     - s consists of parentheses only '()[]{}'.
 * 
 * Hints:
 *     - Use a stack of characters.
 *     - When you encounter an opening bracket, push it to the top of the stack.
 *     - When you encounter a closing bracket, check if the top of the stack was the opening for it. If yes, pop it from the stack. Otherwise, return false.
 * 
 * Template (python3):
 *     class Solution:
 *         def isValid(self, s: str) -> bool:
 * 
 * Hint: Use a stack to match opening and closing brackets.
 */
#[allow(unused_imports)]
use rstest;

fn is_valid(s: &str) -> bool {
    todo!()
}

fn main() {
    struct TestCase {
        label: &'static str,
        input: &'static str,
        expected: bool,
    }

    let tests: &[TestCase] = &[
        TestCase { label: "simple pair", input: "()", expected: true },
        TestCase { label: "mixed brackets", input: "()[]{}", expected: true },
        TestCase { label: "mismatched", input: "(]", expected: false },
        TestCase { label: "interleaved", input: "([)]", expected: false },
        TestCase { label: "nested", input: "{[]}", expected: true },
        TestCase { label: "single opening", input: "(", expected: false },
        TestCase { label: "single closing", input: ")", expected: false },
        TestCase { label: "only openings", input: "((((", expected: false },
        TestCase { label: "only closings", input: "))))", expected: false },
        TestCase { label: "deeply nested", input: "((({{{[[[]]]}}})))", expected: true },
    ];

    println!("\n============================================================");
    println!("  20. Valid Parentheses");
    println!("============================================================");

    let mut passed = 0;
    for (i, tc) in tests.iter().enumerate() {
        let got = is_valid(tc.input);
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
