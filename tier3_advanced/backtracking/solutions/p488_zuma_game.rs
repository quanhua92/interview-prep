/*
 * P488: Zuma Game [PREMIUM] (Hard)
 * https://leetcode.com/problems/zuma-game/
 * Topics: String, Dynamic Programming, Stack, Breadth-First Search, Memoization
 *
 * Given a string board and a string hand, return the minimum number of balls you have to insert to clear all the balls from the board.
 * Example 1:
 *     Input: board = "WRRBBW", hand = "RB"
 *     Output: -1
 *
 * Example 2:
 *     Input: board = "WWRRBBWW", hand = "WRBRW"
 *     Output: 2
 *
 * Template (python3):
 *     class Solution:
 *         def findMinStep(self, board: str, hand: str) -> int:
 */

use wasm_libs::*;
use std::collections::HashMap;

fn collapse(s: &str) -> String {
    let mut result = s.to_string();
    loop {
        let mut changed = false;
        let mut next = String::new();
        let bytes = result.as_bytes();
        let mut i = 0;
        while i < bytes.len() {
            let mut j = i;
            while j < bytes.len() && bytes[j] == bytes[i] { j += 1; }
            if j - i >= 3 {
                changed = true;
            } else {
                for k in i..j {
                    next.push(bytes[k] as char);
                }
            }
            i = j;
        }
        result = next;
        if !changed { break; }
    }
    result
}

fn dfs(board: &str, hand: &[u8], memo: &mut HashMap<(String, String), i32>) -> i32 {
    let b = collapse(board);
    if b.is_empty() { return 0; }
    if hand.is_empty() { return -1; }

    let hand_sorted: Vec<u8> = {
        let mut h = hand.to_vec();
        h.sort();
        h
    };
    let hand_str = String::from_utf8(hand_sorted.clone()).unwrap();
    let key = (b.clone(), hand_str);
    if let Some(&v) = memo.get(&key) { return v; }

    let mut min_balls: i32 = -1;
    let blen = b.len();
    let hlen = hand_sorted.len();

    for i in 0..=blen {
        for hi in 0..hlen {
            if hi > 0 && hand_sorted[hi] == hand_sorted[hi - 1] { continue; }
            let color = hand_sorted[hi] as char;
            let new_board: String = format!("{}{}{}", &b[..i], color, &b[i..]);
            let mut new_hand = hand_sorted.clone();
            new_hand.remove(hi);
            let result = dfs(&new_board, &new_hand, memo);
            if result != -1 {
                if min_balls == -1 || result + 1 < min_balls {
                    min_balls = result + 1;
                }
            }
        }
    }

    memo.insert(key, min_balls);
    min_balls
}

fn find_min_step(board: &str, hand: &str) -> i32 {
    let mut memo = HashMap::new();
    dfs(board, hand.as_bytes(), &mut memo)
}

fn main() {
    let board = read_line();
    let hand = read_line();
    let result = find_min_step(&board, &hand);
    write_int(result);
}
