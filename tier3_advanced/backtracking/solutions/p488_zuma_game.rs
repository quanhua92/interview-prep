/*
 * P488: Zuma Game [PREMIUM] (Hard)
 * https://leetcode.com/problems/zuma-game/
 * Topics: String, Dynamic Programming, Stack, Breadth-First Search, Memoization
 *
 * You are playing a variation of the game Zuma.
 * In this variation of Zuma, there is a single row of colored balls on a board, where each ball can be colored red 'R', yellow 'Y', blue 'B', green 'G', or white 'W'. You also have several colored balls in your hand.
 * Your goal is to clear all of the balls from the board. On each turn:
 * Given a string board, representing the row of balls on the board, and a string hand, representing the balls in your hand, return the minimum number of balls you have to insert to clear all the balls from the board. If you cannot clear all the balls from the board using the balls in your hand, return -1.
 * Example 1:
 *     Input: board = "WRRBBW", hand = "RB"
 *     Output: -1
 *     Explanation: It is impossible to clear all the balls. The best you can do is:
 *     - Insert 'R' so the board becomes WRRRBBW. WRRRBBW -> WBBW.
 *     - Insert 'B' so the board becomes WBBBW. WBBBW -> WW.
 *     There are still balls remaining on the board, and you are out of balls to insert.
 *
 * Example 2:
 *     Input: board = "WWRRBBWW", hand = "WRBRW"
 *     Output: 2
 *     Explanation: To make the board empty:
 *     - Insert 'R' so the board becomes WWRRRBBWW. WWRRRBBWW -> WWBBWW.
 *     - Insert 'B' so the board becomes WWBBBWW. WWBBBWW -> WWWW -> empty.
 *     2 balls from your hand were needed to clear the board.
 *
 * Example 3:
 *     Input: board = "G", hand = "GGGGG"
 *     Output: 2
 *     Explanation: To make the board empty:
 *     - Insert 'G' so the board becomes GG.
 *     - Insert 'G' so the board becomes GGG. GGG -> empty.
 *     2 balls from your hand were needed to clear the board.
 *
 * Constraints:
 *     - 1 <= board.length <= 16
 *     - 1 <= hand.length <= 5
 *     - board and hand consist of the characters 'R', 'Y', 'B', 'G', and 'W'.
 *     - The initial row of balls on the board will not have any groups of three or more consecutive balls of the same color.
 *
 * Template (python3):
 *     class Solution:
 *         def findMinStep(self, board: str, hand: str) -> int:
 */


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

struct TC {
    label: &'static str,
    board: &'static str,
    hand: &'static str,
    expected: i32,
}

fn main() {
    let tests: &[TC] = &[
        TC { label: "example 1", board: "WRRBBW", hand: "RB", expected: -1 },
        TC { label: "example 2", board: "WWRRBBWW", hand: "WRBRW", expected: 2 },
        TC { label: "example 3", board: "G", hand: "GGGGG", expected: 2 },
        TC { label: "one insertion clears chain reaction", board: "RBYYBBRR", hand: "YRB", expected: 1 },
        TC { label: "insert triggers cascade", board: "RRWWRRBB", hand: "WWB", expected: 2 },
        TC { label: "insufficient balls single", board: "R", hand: "R", expected: -1 },
        TC { label: "pair plus one makes triple", board: "RR", hand: "RR", expected: 1 },
    ];

    println!("\n============================================================");
    println!("  488. Zuma Game");
    println!("============================================================");

    let mut passed = 0;
    for (i, tc) in tests.iter().enumerate() {
        let got = find_min_step(tc.board, tc.hand);
        if got == tc.expected {
            passed += 1;
            println!("  Test {} ({}): PASS", i + 1, tc.label);
        } else {
            println!("  Test {} ({}): FAIL", i + 1, tc.label);
            println!("    Expected: {}", tc.expected);
            println!("    Got:      {}", got);
        }
    }

    println!("\n  {}/{} passed", passed, tests.len());
    println!("============================================================\n");

    std::process::exit(if passed == tests.len() { 0 } else { 1 });
}
