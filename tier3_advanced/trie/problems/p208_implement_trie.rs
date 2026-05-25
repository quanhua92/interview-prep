/*
 * P208: Implement Trie (Prefix Tree) (Medium)
 * https://leetcode.com/problems/implement-trie-prefix-tree/
 * Topics: Hash Table, String, Design, Trie
 * 
 * A trie (pronounced as "try") or prefix tree is a tree data structure used to efficiently store and retrieve keys in a dataset of strings. There are various applications of this data structure, such as autocomplete and spellchecker.
 * Implement the Trie class:
 * 
 * Example 1:
 *     Input
 *     ["Trie", "insert", "search", "search", "startsWith", "insert", "search"]
 *     [[], ["apple"], ["apple"], ["app"], ["app"], ["app"], ["app"]]
 *     Output
 *     [null, null, true, false, true, null, true]
 * 
 *     Explanation
 *     Trie trie = new Trie();
 *     trie.insert("apple");
 *     trie.search("apple");   // return True
 *     trie.search("app");     // return False
 *     trie.startsWith("app"); // return True
 *     trie.insert("app");
 *     trie.search("app");     // return True
 * 
 * Constraints:
 *     - 1 <= word.length, prefix.length <= 2000
 *     - word and prefix consist only of lowercase English letters.
 *     - At most 3 * 104 calls in total will be made to insert, search, and startsWith.
 * 
 * Template (python3):
 *     class Trie:
 * 
 *         def __init__(self):
 * 
 * 
 *         def insert(self, word: str) -> None:
 * 
 * 
 *         def search(self, word: str) -> bool:
 * 
 * 
 *         def startsWith(self, prefix: str) -> bool:
 * 
 * 
 * 
 *     # Your Trie object will be instantiated and called as such:
 *     # obj = Trie()
 *     # obj.insert(word)
 *     # param_2 = obj.search(word)
 *     # param_3 = obj.startsWith(prefix)
 * 
 * Hint: Build a Trie class with insert, search, and starts_with methods.
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

struct Trie {
    root: TrieNode,
}

impl Trie {
    fn new() -> Self {
        Trie { root: TrieNode::new() }
    }

    fn insert(&mut self, word: &str) {
        let mut cur = &mut self.root;
        for ch in word.chars() {
            cur = cur.children.entry(ch).or_insert_with(|| Box::new(TrieNode::new()));
        }
        cur.is_end = true;
    }

    fn search(&self, word: &str) -> bool {
        let node = self.find(word);
        node.map_or(false, |n| n.is_end)
    }

    fn starts_with(&self, prefix: &str) -> bool {
        self.find(prefix).is_some()
    }

    fn find(&self, prefix: &str) -> Option<&TrieNode> {
        let mut cur = &self.root;
        for ch in prefix.chars() {
            cur = cur.children.get(&ch)?;
        }
        Some(cur)
    }
}

fn run_test(_label: &str, ops: &[(&str, &str)], expected: &[Option<bool>]) -> bool {
    todo!()
}

fn main() {
    struct TC<'a> { label: &'a str, ops: &'a [(&'a str, &'a str)], expected: &'a [Option<bool>] }

    let tests: &[TC] = &[
        TC { label: "full sequence",
             ops: &[("insert","apple"),("search","apple"),("search","app"),("starts_with","app"),("insert","app"),("search","app")],
             expected: &[None, Some(true), Some(false), Some(true), None, Some(true)] },
        TC { label: "single character",
             ops: &[("insert","a"),("search","a"),("search","b"),("starts_with","a"),("starts_with","b")],
             expected: &[None, Some(true), Some(false), Some(true), Some(false)] },
        TC { label: "search non-existent word/prefix",
             ops: &[("insert","hello"),("search","world"),("starts_with","world"),("search","hel"),("starts_with","hel")],
             expected: &[None, Some(false), Some(false), Some(false), Some(true)] },
        TC { label: "overlapping prefixes",
             ops: &[("insert","a"),("insert","ab"),("insert","abc"),("search","a"),("search","ab"),("search","abc"),("search","abcd"),("starts_with","ab"),("starts_with","abcd")],
             expected: &[None, None, None, Some(true), Some(true), Some(true), Some(false), Some(true), Some(false)] },
        TC { label: "duplicate insert",
             ops: &[("insert","test"),("insert","test"),("search","test"),("starts_with","te")],
             expected: &[None, None, Some(true), Some(true)] },
    ];

    println!("\n============================================================");
    println!("  208. Implement Trie (Prefix Tree)");
    println!("============================================================");

    let mut passed = 0;
    for (i, tc) in tests.iter().enumerate() {
        if run_test(tc.label, tc.ops, tc.expected) {
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
