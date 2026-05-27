/*
 * P17: Letter Combinations of a Phone Number (Medium)
 * https://leetcode.com/problems/letter-combinations-of-a-phone-number/
 * Topics: Hash Table, String, Backtracking
 *
 * Given a string containing digits from 2-9 inclusive, return all possible letter combinations that the number could represent. Return the answer in any order.
 * A mapping of digits to letters (just like on the telephone buttons) is given below. Note that 1 does not map to any letters.
 *
 * Example 1:
 *     Input: digits = "23"
 *     Output: ["ad","ae","af","bd","be","bf","cd","ce","cf"]
 *
 * Example 2:
 *     Input: digits = ""
 *     Output: []
 *
 * Example 3:
 *     Input: digits = "2"
 *     Output: ["a","b","c"]
 *
 * Hint: Map each digit to its letters and use backtracking to build all combinations.
 */

use interview_prep::read_line;
use interview_prep::write_string;

fn letter_combinations(digits: &str) -> Vec<String> {
    let phone_map: &[&str] = &["", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"];
    if digits.is_empty() {
        return Vec::new();
    }
    let n = digits.len();
    let mut result: Vec<String> = Vec::new();
    let mut path: Vec<char> = vec!['\0'; n];

    fn backtrack(
        digits: &[u8],
        phone_map: &[&str],
        index: usize,
        n: usize,
        path: &mut Vec<char>,
        result: &mut Vec<String>,
    ) {
        if index == n {
            result.push(path.iter().collect());
            return;
        }
        for c in phone_map[(digits[index] - b'0') as usize].chars() {
            path[index] = c;
            backtrack(digits, phone_map, index + 1, n, path, result);
        }
    }

    backtrack(digits.as_bytes(), phone_map, 0, n, &mut path, &mut result);
    result.sort();
    result
}

fn main() {
    let digits = read_line();
    let result = letter_combinations(&digits);
    for s in result {
        write_string(&s);
    }
}
