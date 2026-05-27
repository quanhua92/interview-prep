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
 * Hint: Build a Trie from the word list, then use DFS on the board to find matching words.
 */

use wasm_libs::*;

fn find_words(board: &mut Vec<Vec<char>>, words: &[String]) -> Vec<String> {
    todo!()
}

struct Solution;

fn main() {
    let rows = read_int() as usize;
    let cols = read_int() as usize;

    let mut board = Vec::new();
    for _ in 0..rows {
        let line = read_line();
        board.push(line.chars().collect::<Vec<char>>());
    }

    let nw = read_int() as usize;
    let mut words = Vec::new();
    for _ in 0..nw {
        words.push(read_line());
    }

    let result = find_words(&mut board, &words);
    write_int(result.len() as i32);
    for w in &result {
        write_string(w);
    }

    std::process::exit(0);
}
