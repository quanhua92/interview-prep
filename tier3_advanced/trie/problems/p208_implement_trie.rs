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

use wasm_libs::*;
use std::collections::HashMap;

struct TrieNode {
    children: HashMap<char, Box<TrieNode>>,
    is_end: bool,
}

impl TrieNode {
    fn new() -> Self {
    todo!()
}
}

struct Trie {
    root: TrieNode,
}

impl Trie {
    fn new() -> Self {
    todo!()
}

    fn insert(&mut self, word: &str) {
    todo!()
}

    fn search(&self, word: &str) -> bool {
    todo!()
}

    fn starts_with(&self, prefix: &str) -> bool {
    todo!()
}

    fn find(&self, prefix: &str) -> Option<&TrieNode> {
    todo!()
}
}

fn main() {
    let num_ops = read_int() as usize;
    let mut trie = Trie::new();

    for _ in 0..num_ops {
        let op = read_line();
        let val = read_line();

        if op == "insert" {
            trie.insert(&val);
            write_string("null");
        } else if op == "search" {
            write_bool(trie.search(&val));
        } else {
            write_bool(trie.starts_with(&val));
        }
    }

    std::process::exit(0);
}
