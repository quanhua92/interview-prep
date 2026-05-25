/*
 * P522: Longest Uncommon Subsequence II [PREMIUM] (Medium)
 * https://leetcode.com/problems/longest-uncommon-subsequence-ii/
 * Topics: Array, Hash Table, Two Pointers, String, Sorting
 * 
 * Given an array of strings strs, return the length of the longest uncommon subsequence between them. If the longest uncommon subsequence does not exist, return -1.
 * An uncommon subsequence between an array of strings is a string that is a subsequence of one string but not the others.
 * A subsequence of a string s is a string that can be obtained after deleting any number of characters from s.
 * Example 1:
 *     Input: strs = ["aba","cdc","eae"]
 *     Output: 3
 * 
 * Example 2:
 *     Input: strs = ["aaa","aaa","aa"]
 *     Output: -1
 * 
 * Constraints:
 *     - 2 <= strs.length <= 50
 *     - 1 <= strs[i].length <= 10
 *     - strs[i] consists of lowercase English letters.
 * 
 * Template (python3):
 *     class Solution:
 *         def findLUSlength(self, strs: List[str]) -> int:
 */
fn is_subseq(a: &[u8], b: &[u8]) -> bool {
    todo!()
}

fn find_lus_length(strs: Vec<String>) -> i32 {
    todo!()
}

fn main() {
    let tests: Vec<(&str, Vec<String>, i32)> = vec![
        ("example 1", vec!["aba".into(), "cdc".into(), "eae".into()], 3),
        ("example 2", vec!["aaa".into(), "aaa".into(), "aa".into()], -1),
        ("all length 1 different", vec!["a".into(), "b".into(), "c".into(), "d".into()], 1),
        ("all identical", vec!["abc".into(), "abc".into(), "abc".into()], -1),
        ("one string longer than rest", vec!["a".into(), "a".into(), "ab".into(), "abc".into()], 3),
        ("same length different chars", vec!["abc".into(), "abd".into(), "abe".into()], 3),
    ];

    let ntests = tests.len();
    let mut passed = 0;

    println!("\n============================================================");
    println!("  522. Longest Uncommon Subsequence II");
    println!("============================================================");

    for (i, (label, strs, expected)) in tests.iter().enumerate() {
        let got = find_lus_length(strs.clone());
        if got == *expected {
            passed += 1;
            println!("  Test {} ({}): PASS", i + 1, label);
        } else {
            println!("  Test {} ({}): FAIL", i + 1, label);
            println!("    Expected: {}", expected);
            println!("    Got:      {}", got);
        }
    }

    println!("\n  {}/{} passed", passed, ntests);
    println!("============================================================\n");

    std::process::exit(if passed == ntests { 0 } else { 1 });
}
