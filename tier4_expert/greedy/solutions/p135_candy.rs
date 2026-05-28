/*
 * P135: Candy (Hard)
 * https://leetcode.com/problems/candy/
 * Topics: Array, Greedy
 *
 * There are n children standing in a line. Each child is assigned a rating value given in the integer array ratings.
 * You are giving candies to these children subjected to the following requirements:
 * Return the minimum number of candies you need to have to distribute the candies to the children.
 *
 * Example 1:
 *     Input: ratings = [1,0,2]
 *     Output: 5
 *
 * Example 2:
 *     Input: ratings = [1,2,2]
 *     Output: 4
 *
 * Constraints:
 *     - n == ratings.length
 *     - 1 <= n <= 2 * 104
 *     - 0 <= ratings[i] <= 2 * 104
 *
 * Template (python3):
 *     class Solution:
 *         def candy(self, ratings: List[int]) -> int:
 *
 * Hint: Two-pass greedy: left-to-right then right-to-left, taking the max of both passes.
 */

use wasm_libs::*;

fn candy(ratings: &[i32]) -> i32 {
    let n = ratings.len();
    if n == 1 { return 1; }
    let mut c = vec![1i32; n];
    for i in 1..n {
        if ratings[i] > ratings[i - 1] { c[i] = c[i - 1] + 1; }
    }
    for i in (0..n - 1).rev() {
        if ratings[i] > ratings[i + 1] && c[i] <= c[i + 1] { c[i] = c[i + 1] + 1; }
    }
    c.iter().sum()
}

fn main() {
    let ratings = read_ints();
    let result = candy(&ratings);
    write_int(result);
}
