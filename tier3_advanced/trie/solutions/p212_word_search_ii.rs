/*
 * P212: Word Search II (Hard)
 * https://leetcode.com/problems/word-search-ii/
 * Topics: Array, String, Backtracking, Trie, Matrix
 *
 * Given an m x n board of characters and a list of strings words, return all words on the board.
 * Each word must be constructed from letters of sequentially adjacent cells, where adjacent cells are horizontally or vertically neighboring. The same letter cell may not be used more than once in a word.
 *
 * Example 1:
 *     Input: board = [["o","a","a","n"],["e","t","a","e"],["i","h","k","r"],["i","f","l","v"]], words = ["oath","pea","eat","rain"]
 *     Output: ["eat","oath"]
 *
 * Example 2:
 *     Input: board = [["a","b"],["c","d"]], words = ["abcb"]
 *     Output: []
 *
 * Constraints:
 *     - m == board.length
 *     - n == board[i].length
 *     - 1 <= m, n <= 12
 *     - board[i][j] is a lowercase English letter.
 *     - 1 <= words.length <= 3 * 104
 *     - 1 <= words[i].length <= 10
 *     - words[i] consists of lowercase English letters.
 *     - All the strings of words are unique.
 *
 * Hints:
 *     - You would need to optimize your backtracking to pass the larger test. Could you stop backtracking earlier?
 *     - If the current candidate does not exist in all words&#39; prefix, you could stop backtracking immediately. What kind of data structure could answer such query efficiently? Does a hash table work? Why or why not? How about a Trie? If you would like to learn how to implement a basic trie, please work on this problem: <a href="https://leetcode.com/problems/implement-trie-prefix-tree/">Implement Trie (Prefix Tree)</a> first.
 *
 * Template (python3):
 *     class Solution:
 *         def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
 *
 * Hint: Build a Trie from the word list, then use DFS on the board to find matching words.
 */


#[allow(unused_imports)]
use rstest;
use std::collections::HashMap;

struct TrieNode {
    children: HashMap<char, Box<TrieNode>>,
    word: Option<String>,
}

impl TrieNode {
    fn new() -> Self {
        TrieNode { children: HashMap::new(), word: None }
    }
}

fn find_words(board: &mut Vec<Vec<char>>, words: &[&str]) -> Vec<String> {
    let mut root = TrieNode::new();
    for &w in words {
        let mut cur = &mut root;
        for ch in w.chars() {
            cur = cur.children.entry(ch).or_insert_with(|| Box::new(TrieNode::new()));
        }
        cur.word = Some(w.to_string());
    }

    let rows = board.len();
    let cols = board[0].len();
    let mut result: Vec<String> = Vec::new();

    fn dfs(
        board: &mut Vec<Vec<char>>,
        r: usize, c: usize,
        parent: &mut TrieNode,
        rows: usize, cols: usize,
        result: &mut Vec<String>,
    ) {
        let ch = board[r][c];
        if ch == '#' { return; }
        let curr = match parent.children.get_mut(&ch) {
            Some(n) => n,
            None => return,
        };

        if let Some(ref w) = curr.word.take() {
            result.push(w.clone());
        }

        board[r][c] = '#';
        let dirs: [(i32, i32); 4] = [(0,1),(0,-1),(1,0),(-1,0)];
        for &(dr, dc) in &dirs {
            let nr = r as i32 + dr;
            let nc = c as i32 + dc;
            if nr >= 0 && (nr as usize) < rows && nc >= 0 && (nc as usize) < cols {
                dfs(board, nr as usize, nc as usize, curr, rows, cols, result);
            }
        }
        board[r][c] = ch;

        if curr.children.is_empty() {
            parent.children.remove(&ch);
        }
    }

    for r in 0..rows {
        for c in 0..cols {
            dfs(board, r, c, &mut root, rows, cols, &mut result);
        }
    }

    result.sort();
    result
}

fn main() {
    struct TC<'a> {
        label: &'a str,
        board: Vec<Vec<char>>,
        words: &'a [&'a str],
        expected: Vec<&'a str>,
    }

    let tests: Vec<TC> = vec![
        TC { label: "example 1",
             board: vec![vec!['o','a','a','n'],vec!['e','t','a','e'],vec!['i','h','k','r'],vec!['i','f','l','v']],
             words: &["oath","pea","eat","rain"],
             expected: vec!["eat","oath"] },
        TC { label: "example 2",
             board: vec![vec!['a','b'],vec!['c','d']],
             words: &["abcb"],
             expected: vec![] },
        TC { label: "1x1 board single char",
             board: vec![vec!['a']],
             words: &["a"],
             expected: vec!["a"] },
        TC { label: "word not on board",
             board: vec![vec!['a','b'],vec!['c','d']],
             words: &["xyz"],
             expected: vec![] },
        TC { label: "same letter grid",
             board: vec![vec!['a','a'],vec!['a','a']],
             words: &["aaaa"],
             expected: vec!["aaaa"] },
        TC { label: "prefix is also a word",
             board: vec![vec!['o','a','a','n'],vec!['e','t','a','e'],vec!['i','h','k','r'],vec!['i','f','l','v']],
             words: &["oath","oat"],
             expected: vec!["oat","oath"] },
    ];

    println!("\n============================================================");
    println!("  212. Word Search II");
    println!("============================================================");

    let mut passed = 0;
    for (i, tc) in tests.iter().enumerate() {
        let mut board = tc.board.clone();
        let got = find_words(&mut board, tc.words);
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
