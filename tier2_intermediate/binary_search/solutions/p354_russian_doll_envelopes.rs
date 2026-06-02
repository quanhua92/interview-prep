/*
 * P354: Russian Doll Envelopes [PREMIUM] (Hard)
 * https://leetcode.com/problems/russian-doll-envelopes/
 * Topics: Array, Binary Search, Dynamic Programming, Sorting
 *
 * You are given a 2D array of integers envelopes where envelopes[i] = [wi, hi] represents the width and the height of an envelope.
 * One envelope can fit into another if and only if both the width and height of one envelope are greater than the other envelope's width and height.
 * Return the maximum number of envelopes you can Russian doll (i.e., put one inside the other).
 * Note: You cannot rotate an envelope.
 * Example 1:
 *     Input: envelopes = [[5,4],[6,4],[6,7],[2,3]]
 *     Output: 3
 *     Explanation: The maximum number of envelopes you can Russian doll is 3 ([2,3] => [5,4] => [6,7]).
 *
 * Example 2:
 *     Input: envelopes = [[1,1],[1,1],[1,1]]
 *     Output: 1
 *
 * Constraints:
 *     - 1 <= envelopes.length <= 10^5
 *     - envelopes[i].length == 2
 *     - 1 <= wi, hi <= 10^5
 *
 * Template (python3):
 *     class Solution:
 *         def maxEnvelopes(self, envelopes: List[List[int]]) -> int:
 */

use wasm_libs::*;

fn max_envelopes(mut envelopes: Vec<Vec<i32>>) -> i32 {
    if envelopes.len() <= 1 { return envelopes.len() as i32; }
    envelopes.sort_by(|a, b| {
        if a[0] != b[0] { a[0].cmp(&b[0]) } else { b[1].cmp(&a[1]) }
    });
    let mut dp: Vec<i32> = Vec::new();
    for env in &envelopes {
        let h = env[1];
        match dp.binary_search(&h) {
            Ok(pos) => dp[pos] = h,
            Err(pos) => { if pos == dp.len() { dp.push(h); } else { dp[pos] = h; } }
        }
    }
    dp.len() as i32
}

fn main() {
    let cols = read_int() as usize;
    let mut envelopes: Vec<Vec<i32>> = Vec::new();
    for _ in 0..cols {
        envelopes.push(read_ints());
    }
    write_int(max_envelopes(envelopes));
    std::process::exit(0);
}
