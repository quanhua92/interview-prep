/*
 * P524: Longest Word in Dictionary through Deleting [PREMIUM] (Medium)
 * https://leetcode.com/problems/longest-word-in-dictionary-through-deleting/
 * Topics: Array, Two Pointers, String, Sorting
 *
 * Given a string s and a string array dictionary, return the longest string in the dictionary that can be formed by deleting some of the given string characters. If there is more than one possible result, return the longest word with the smallest lexicographical order. If there is no possible result, return the empty string.
 * Example 1:
 *     Input: s = "abpcplea", dictionary = ["ale","apple","monkey","plea"]
 *     Output: "apple"
 *
 * Example 2:
 *     Input: s = "abpcplea", dictionary = ["a","b","c"]
 *     Output: "a"
 *
 * Constraints:
 *     - 1 <= s.length <= 1000
 *     - 1 <= dictionary.length <= 1000
 *     - 1 <= dictionary[i].length <= 1000
 *     - s and dictionary[i] consist of lowercase English letters.
 *
 * Template (python3):
 *     class Solution:
 *         def findLongestWord(self, s: str, dictionary: List[str]) -> str:
 */


fn is_subseq(word: &[u8], target: &[u8]) -> bool {
    let mut i = 0;
    for &ch in target {
        if i < word.len() && word[i] == ch {
            i += 1;
        }
    }
    i == word.len()
}

fn find_longest_word(s: &str, dict: &[&str]) -> String {
    let mut best = "";
    for &word in dict {
        if is_subseq(word.as_bytes(), s.as_bytes()) {
            if word.len() > best.len() || (word.len() == best.len() && word < best) {
                best = word;
            }
        }
    }
    best.to_string()
}

fn main() {
    let mut passed = 0;
    let total = 6;
    println!("\n============================================================");
    println!("  524. Longest Word in Dictionary through Deleting");
    println!("============================================================");

    {
        let dict = ["ale", "apple", "monkey", "plea"];
        let got = find_longest_word("abpcplea", &dict);
        if got == "apple" { passed += 1; println!("  Test 1 (example 1): PASS"); }
        else { println!("  Test 1 (example 1): FAIL\n  Expected: apple, Got: {}", got); }
    }
    {
        let dict = ["a", "b", "c"];
        let got = find_longest_word("abpcplea", &dict);
        if got == "a" { passed += 1; println!("  Test 2 (example 2): PASS"); }
        else { println!("  Test 2 (example 2): FAIL\n  Expected: a, Got: {}", got); }
    }
    {
        let dict: [&str; 0] = [];
        let got = find_longest_word("abpcplea", &dict);
        if got == "" { passed += 1; println!("  Test 3 (empty dictionary): PASS"); }
        else { println!("  Test 3 (empty dictionary): FAIL\n  Expected: (empty), Got: {}", got); }
    }
    {
        let dict = ["xyz", "def"];
        let got = find_longest_word("abc", &dict);
        if got == "" { passed += 1; println!("  Test 4 (no match): PASS"); }
        else { println!("  Test 4 (no match): FAIL\n  Expected: (empty), Got: {}", got); }
    }
    {
        let dict = ["apple", "ale", "abpple"];
        let got = find_longest_word("abpcplea", &dict);
        if got == "abpple" { passed += 1; println!("  Test 5 (same length lexicographical tie): PASS"); }
        else { println!("  Test 5 (same length lexicographical tie): FAIL\n  Expected: abpple, Got: {}", got); }
    }
    {
        let dict = ["a", "aa", "aaa"];
        let got = find_longest_word("a", &dict);
        if got == "a" { passed += 1; println!("  Test 6 (longer dict words than s): PASS"); }
        else { println!("  Test 6 (longer dict words than s): FAIL\n  Expected: a, Got: {}", got); }
    }

    println!("\n  {}/{} passed", passed, total);
    println!("============================================================\n");
    std::process::exit(if passed == total { 0 } else { 1 });
}
