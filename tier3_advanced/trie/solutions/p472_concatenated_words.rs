/*
 * P472: Concatenated Words [PREMIUM] (Hard)
 * https://leetcode.com/problems/concatenated-words/
 * Topics: Array, String, Dynamic Programming, Depth-First Search, Trie, Sorting
 *
 * Given an array of strings words (without duplicates), return all the concatenated words in the given list of words.
 * A concatenated word is defined as a string that is comprised entirely of at least two shorter words (not necessarily distinct) in the given array.
 * Example 1:
 *     Input: words = ["cat","cats","catsdogcats","dog","dogcatsdog","hippopotamuses","rat","ratcatdogcat"]
 *     Output: ["catsdogcats","dogcatsdog","ratcatdogcat"]
 *     Explanation: "catsdogcats" can be concatenated by "cats", "dog" and "cats";
 *     "dogcatsdog" can be concatenated by "dog", "cats" and "dog";
 *     "ratcatdogcat" can be concatenated by "rat", "cat", "dog" and "cat".
 *
 * Example 2:
 *     Input: words = ["cat","dog","catdog"]
 *     Output: ["catdog"]
 *
 * Constraints:
 *     - 1 <= words.length <= 104
 *     - 1 <= words[i].length <= 30
 *     - words[i] consists of only lowercase English letters.
 *     - All the strings of words are unique.
 *     - 1 <= sum(words[i].length) <= 105
 *
 * Template (python3):
 *     class Solution:
 *         def findAllConcatenatedWordsInADict(self, words: List[str]) -> List[str]:
 */


#[allow(unused_imports)]
use rstest;
use std::collections::HashMap;

struct TrieNode {
    children: HashMap<char, Box<TrieNode>>,
    is_end: bool,
}

impl TrieNode {
    fn new() -> Self {
        TrieNode { children: HashMap::new(), is_end: false }
    }
}

fn find_all_concatenated_words(words: &mut Vec<String>) -> Vec<String> {
    words.sort_by_key(|w| w.len());

    let mut root = TrieNode::new();

    fn can_concatenate(root: &TrieNode, word: &str, start: usize, count: usize) -> bool {
        let mut cur = root;
        let bytes = word.as_bytes();
        for i in start..word.len() {
            let ch = bytes[i] as char;
            match cur.children.get(&ch) {
                Some(child) => cur = child,
                None => return false,
            }
            if cur.is_end {
                if i == word.len() - 1 {
                    return count >= 1;
                }
                if can_concatenate(root, word, i + 1, count + 1) {
                    return true;
                }
            }
        }
        false
    }

    fn insert(root: &mut TrieNode, word: &str) {
        let mut cur = root;
        for ch in word.chars() {
            cur = cur.children.entry(ch).or_insert_with(|| Box::new(TrieNode::new()));
        }
        cur.is_end = true;
    }

    let mut result = Vec::new();
    for word in words.iter() {
        if can_concatenate(&root, word, 0, 0) {
            result.push(word.clone());
        }
        insert(&mut root, word);
    }

    result.sort();
    result
}

fn main() {
    struct TC<'a> {
        label: &'a str,
        words: Vec<&'a str>,
        expected: Vec<&'a str>,
    }

    let tests: Vec<TC> = vec![
        TC { label: "example 1",
             words: vec!["cat","cats","catsdogcats","dog","dogcatsdog","hippopotamuses","rat","ratcatdogcat"],
             expected: vec!["catsdogcats","dogcatsdog","ratcatdogcat"] },
        TC { label: "example 2",
             words: vec!["cat","dog","catdog"],
             expected: vec!["catdog"] },
        TC { label: "word from duplicate parts",
             words: vec!["cat","catcat"],
             expected: vec!["catcat"] },
        TC { label: "no concatenated words",
             words: vec!["a","b","c"],
             expected: vec![] },
        TC { label: "deep concatenation chain",
             words: vec!["a","aa","aaaa"],
             expected: vec!["aa","aaaa"] },
        TC { label: "self-similar concatenation",
             words: vec!["ab","abab"],
             expected: vec!["abab"] },
    ];

    println!("\n============================================================");
    println!("  472. Concatenated Words");
    println!("============================================================");

    let mut passed = 0;
    for (i, tc) in tests.iter().enumerate() {
        let mut words: Vec<String> = tc.words.iter().map(|s| s.to_string()).collect();
        let got = find_all_concatenated_words(&mut words);
        let exp: Vec<&str> = tc.expected.iter().copied().collect();
        let got_refs: Vec<&str> = got.iter().map(|s| s.as_str()).collect();
        if got_refs == exp {
            passed += 1;
            println!("  Test {} ({}): PASS", i + 1, tc.label);
        } else {
            println!("  Test {} ({}): FAIL", i + 1, tc.label);
            println!("    Expected: {:?}", exp);
            println!("    Got:      {:?}", got_refs);
        }
    }

    println!("\n  {}/{} passed", passed, tests.len());
    println!("============================================================\n");

    std::process::exit(if passed == tests.len() { 0 } else { 1 });
}
