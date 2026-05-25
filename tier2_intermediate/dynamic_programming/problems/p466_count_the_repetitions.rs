/*
 * P466: Count The Repetitions [PREMIUM] (Hard)
 * https://leetcode.com/problems/count-the-repetitions/
 * Topics: String, Dynamic Programming
 * 
 * We define str = [s, n] as the string str which consists of the string s concatenated n times.
 * We define that string s1 can be obtained from string s2 if we can remove some characters from s2 such that it becomes s1.
 * You are given two strings s1 and s2 and two integers n1 and n2. You have the two strings str1 = [s1, n1] and str2 = [s2, n2].
 * Return the maximum integer m such that str = [str2, m] can be obtained from str1.
 * Example 1:
 *     Input: s1 = "acb", n1 = 4, s2 = "ab", n2 = 2
 *     Output: 2
 * 
 * Example 2:
 *     Input: s1 = "acb", n1 = 1, s2 = "acb", n2 = 1
 *     Output: 1
 * 
 * Constraints:
 *     - 1 <= s1.length, s2.length <= 100
 *     - s1 and s2 consist of lowercase English letters.
 *     - 1 <= n1, n2 <= 106
 * 
 * Template (python3):
 *     class Solution:
 *         def getMaxRepetitions(self, s1: str, n1: int, s2: str, n2: int) -> int:
 */
use rstest;

fn get_max_repetitions(s1: &str, n1: i32, s2: &str, n2: i32) -> i32 {
    todo!()
}
        prev_iter[s2_idx] = i as i32;
        prev_count[s2_idx] = count;
    }
    count / n2
}

fn main() {
    struct TC<'a> { label: &'a str, s1: &'a str, n1: i32, s2: &'a str, n2: i32, expected: i32 }
    let tests: &[TC] = &[
        TC { label: "example 1", s1: "acb", n1: 4, s2: "ab", n2: 2, expected: 2 },
        TC { label: "example 2", s1: "acb", n1: 1, s2: "acb", n2: 1, expected: 1 },
        TC { label: "single char repeated", s1: "a", n1: 100, s2: "a", n2: 1, expected: 100 },
        TC { label: "impossible char", s1: "a", n1: 1, s2: "b", n2: 1, expected: 0 },
        TC { label: "each s1 yields one s2 match", s1: "abc", n1: 10, s2: "ac", n2: 1, expected: 10 },
        TC { label: "overlap matching", s1: "aba", n1: 3, s2: "ab", n2: 1, expected: 3 },
    ];
    let mut passed = 0;
    for (i, tc) in tests.iter().enumerate() {
        let got = get_max_repetitions(tc.s1, tc.n1, tc.s2, tc.n2);
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
