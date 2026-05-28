/*
 * P473: Matchsticks to Square [PREMIUM] (Medium)
 * https://leetcode.com/problems/matchsticks-to-square/
 * Topics: Array, Dynamic Programming, Backtracking, Bit Manipulation, Bitmask
 *
 * You are given an integer array matchsticks where matchsticks[i] is the length of the ith matchstick.
 * Return true if you can make this square and false otherwise.
 *
 * Example 1:
 *     Input: matchsticks = [1,1,2,2,2]
 *     Output: true
 *
 * Example 2:
 *     Input: matchsticks = [3,3,3,3,4]
 *     Output: false
 *
 * Hint: Treat the matchsticks as an array. Can we split the array into 4 equal parts?
 */

use wasm_libs::*;

fn makesquare(mut matchsticks: Vec<i32>) -> bool {
    todo!()
}

fn main() {
    let matchsticks = read_ints();
    let result = makesquare(matchsticks);
    write_bool(result);
}
