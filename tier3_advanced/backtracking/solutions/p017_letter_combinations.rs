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
 * Constraints:
 *     - 0 <= digits.length <= 4
 *     - digits[i] is a digit in the range ['2', '9'].
 *
 * Template (python3):
 *     class Solution:
 *         def letterCombinations(self, digits: str) -> List[str]:
 *
 * Hint: Map each digit to its letters and use backtracking to build all combinations.
 */


#[allow(unused_imports)]
use rstest;

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
    println!("\n============================================================");
    println!("  17. Letter Combinations of a Phone Number");
    println!("============================================================");

    let mut passed = 0;

    {
        let got = letter_combinations("23");
        let exp: Vec<&str> = vec!["ad","ae","af","bd","be","bf","cd","ce","cf"];
        if got == exp { passed += 1; println!("  Test 1 (example 1): PASS"); }
        else { println!("  Test 1 (example 1): FAIL\n    Expected: {:?}\n    Got:      {:?}", exp, got); }
    }
    {
        let got = letter_combinations("");
        if got.is_empty() { passed += 1; println!("  Test 2 (empty input): PASS"); }
        else { println!("  Test 2 (empty input): FAIL"); }
    }
    {
        let got = letter_combinations("2");
        let exp: Vec<&str> = vec!["a","b","c"];
        if got == exp { passed += 1; println!("  Test 3 (single digit): PASS"); }
        else { println!("  Test 3 (single digit): FAIL\n    Expected: {:?}\n    Got:      {:?}", exp, got); }
    }
    {
        let got = letter_combinations("7");
        let exp: Vec<&str> = vec!["p","q","r","s"];
        if got == exp { passed += 1; println!("  Test 4 (digit with 4 letters): PASS"); }
        else { println!("  Test 4 (digit with 4 letters): FAIL\n    Expected: {:?}\n    Got:      {:?}", exp, got); }
    }
    {
        let got = letter_combinations("9");
        let exp: Vec<&str> = vec!["w","x","y","z"];
        if got == exp { passed += 1; println!("  Test 5 (digit 9): PASS"); }
        else { println!("  Test 5 (digit 9): FAIL\n    Expected: {:?}\n    Got:      {:?}", exp, got); }
    }
    {
        let got = letter_combinations("79");
        let exp: Vec<&str> = vec![
            "pw","px","py","pz","qw","qx","qy","qz",
            "rw","rx","ry","rz","sw","sx","sy","sz",
        ];
        if got == exp { passed += 1; println!("  Test 6 (two 4-letter digits): PASS"); }
        else { println!("  Test 6 (two 4-letter digits): FAIL\n    Expected: {:?}\n    Got:      {:?}", exp, got); }
    }

    println!("\n  {}/6 passed", passed);
    println!("============================================================\n");

    std::process::exit(if passed == 6 { 0 } else { 1 });
}
