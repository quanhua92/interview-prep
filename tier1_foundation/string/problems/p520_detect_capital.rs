/*
 * P520: Detect Capital [PREMIUM] (Easy)
 * https://leetcode.com/problems/detect-capital/
 * Topics: String
 * 
 * We define the usage of capitals in a word to be right when one of the following cases holds:
 * Given a string word, return true if the usage of capitals in it is right.
 * Example 1:
 *     Input: word = "USA"
 *     Output: true
 * 
 * Example 2:
 *     Input: word = "FlaG"
 *     Output: false
 * 
 * Constraints:
 *     - 1 <= word.length <= 100
 *     - word consists of lowercase and uppercase English letters.
 * 
 * Template (python3):
 *     class Solution:
 *         def detectCapitalUse(self, word: str) -> bool:
 */
fn detect_capital_use(word: &str) -> bool {
    todo!()
}

fn main() {
    struct Test { label: &'static str, input: &'static str, expected: bool }
    let tests: &[Test] = &[
        Test { label: "example 1", input: "USA", expected: true },
        Test { label: "example 2", input: "FlaG", expected: false },
        Test { label: "single lowercase", input: "a", expected: true },
        Test { label: "single uppercase", input: "Z", expected: true },
        Test { label: "all lowercase", input: "leetcode", expected: true },
        Test { label: "title case", input: "Google", expected: true },
        Test { label: "lowercase then uppercase", input: "mL", expected: false },
    ];
    let mut passed = 0;
    for (i, t) in tests.iter().enumerate() {
        let got = detect_capital_use(t.input);
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
