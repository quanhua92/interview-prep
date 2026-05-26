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
    todo!()
}

fn dfs(board: &str, hand: &[u8], memo: &mut HashMap<(String, String), i32>) -> i32 {
    todo!()
}

fn find_min_step(board: &str, hand: &str) -> i32 {
    todo!()
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
