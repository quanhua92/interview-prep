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
    todo!()
}

fn dfs(board: &str, hand: &[u8], memo: &mut HashMap<(String, String), i32>) -> i32 {
    todo!()
}

fn find_min_step(board: &str, hand: &str) -> i32 {
    todo!()
}

fn main() {
    let board = read_line();
    let hand = read_line();
    let result = find_min_step(&board, &hand);
    write_int(result);
}
