/*
 * P211: Design Add and Search Words Data Structure (Medium)
 * https://leetcode.com/problems/design-add-and-search-words-data-structure/
 * Topics: String, Depth-First Search, Design, Trie
 * 
 * Design a data structure that supports adding new words and finding if a string matches any previously added string.
 * Implement the WordDictionary class:
 * Example:
 * 
 * Example 1:
 *     Input
 *     ["WordDictionary","addWord","addWord","addWord","search","search","search","search"]
 *     [[],["bad"],["dad"],["mad"],["pad"],["bad"],[".ad"],["b.."]]
 *     Output
 *     [null,null,null,null,false,true,true,true]
 * 
 *     Explanation
 *     WordDictionary wordDictionary = new WordDictionary();
 *     wordDictionary.addWord("bad");
 *     wordDictionary.addWord("dad");
 *     wordDictionary.addWord("mad");
 *     wordDictionary.search("pad"); // return False
 *     wordDictionary.search("bad"); // return True
 *     wordDictionary.search(".ad"); // return True
 *     wordDictionary.search("b.."); // return True
 * 
 * Constraints:
 *     - 1 <= word.length <= 25
 *     - word in addWord consists of lowercase English letters.
 *     - word in search consist of '.' or lowercase English letters.
 *     - There will be at most 2 dots in word for search queries.
 *     - At most 104 calls will be made to addWord and search.
 * 
 * Hints:
 *     - You should be familiar with how a Trie works. If not, please work on this problem: <a href="https://leetcode.com/problems/implement-trie-prefix-tree/">Implement Trie (Prefix Tree)</a> first.
 * 
 * Template (python3):
 *     class WordDictionary:
 * 
 *         def __init__(self):
 * 
 * 
 *         def addWord(self, word: str) -> None:
 * 
 * 
 *         def search(self, word: str) -> bool:
 * 
 * 
 * 
 *     # Your WordDictionary object will be instantiated and called as such:
 *     # obj = WordDictionary()
 *     # obj.addWord(word)
 *     # param_2 = obj.search(word)
 * 
 * Hint: Build a Trie from the word list, then search with DFS handling '.' wildcards by trying all children.
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

struct WordDictionary {
    root: TrieNode,
}

impl WordDictionary {
    fn new() -> Self {
        WordDictionary { root: TrieNode::new() }
    }

    fn add_word(&mut self, word: &str) {
        todo!()
    }

    fn search(&self, word: &str) -> bool {
        todo!()
    }

    fn dfs(&self, node: &TrieNode, chars: Vec<char>, idx: usize) -> bool {
        todo!()
    }
}

fn main() {
    struct TC<'a> {
        label: &'a str,
        words: &'a [&'a str],
        searches: &'a [&'a str],
        expected: &'a [bool],
    }

    let tests: &[TC] = &[
        TC { label: "example 1", words: &["bad","dad","mad"], searches: &["pad","bad",".ad","b.."], expected: &[false,true,true,true] },
        TC { label: "example 2", words: &["a","ab"], searches: &["a",".a","ab"], expected: &[true,false,true] },
        TC { label: "all dots pattern", words: &["abc"], searches: &["...",".."], expected: &[true,false] },
        TC { label: "single char dot matches multiple", words: &["a","b"], searches: &["."], expected: &[true] },
        TC { label: "dot at beginning", words: &["abc","xbc"], searches: &["bc"], expected: &[false] },
        TC { label: "dot in middle and at end", words: &["abc"], searches: &["a.c","a.."], expected: &[true,true] },
    ];

    println!("\n============================================================");
    println!("  211. Design Add and Search Words Data Structure");
    println!("============================================================");

    let mut passed = 0;
    for (i, tc) in tests.iter().enumerate() {
        let mut wd = WordDictionary::new();
        for &w in tc.words {
            wd.add_word(w);
        }
        let mut ok = true;
        for (j, &s) in tc.searches.iter().enumerate() {
            if wd.search(s) != tc.expected[j] {
                ok = false;
                break;
            }
        }
        if ok {
            passed += 1;
            println!("  Test {} ({}): PASS", i + 1, tc.label);
        } else {
            println!("  Test {} ({}): FAIL", i + 1, tc.label);
        }
    }

    println!("\n  {}/{} passed", passed, tests.len());
    println!("============================================================\n");

    std::process::exit(if passed == tests.len() { 0 } else { 1 });
}
