/*
 * P519: Random Flip Matrix [PREMIUM] (Medium)
 * https://leetcode.com/problems/random-flip-matrix/
 * Topics: Hash Table, Math, Reservoir Sampling, Randomized
 *
 * There is an m x n binary grid matrix with all the values set 0 initially. Design an algorithm to randomly pick an index (i, j) where matrix[i][j] == 0 and flips it to 1. All the indices (i, j) where matrix[i][j] == 0 should be equally likely to be returned.
 * Optimize your algorithm to minimize the number of calls made to the built-in random function of your language and optimize the time and space complexity.
 * Implement the Solution class:
 * Example 1:
 *     Input
 * Example 1:
 *     ["Solution", "flip", "flip", "flip", "reset", "flip"]
 *     [[3, 1], [], [], [], [], []]
 *     Output
 *     [null, [1, 0], [2, 0], [0, 0], null, [2, 0]]
 *
 *     Explanation
 *     Solution solution = new Solution(3, 1);
 *     solution.flip();  // return [1, 0], [0,0], [1,0], and [2,0] should be equally likely to be returned.
 *     solution.flip();  // return [2, 0], Since [1,0] was returned, [2,0] and [0,0]
 *     solution.flip();  // return [0, 0], Based on the previously returned indices, only [0,0] can be returned.
 *     solution.reset(); // All the values are reset to 0 and can be returned.
 *     solution.flip();  // return [2, 0], [0,0], [1,0], and [2,0] should be equally likely to be returned.
 *
 * Constraints:
 *     - 1 <= m, n <= 10^4
 *     - There will be at least one free cell for each call to flip.
 *     - At most 1000 calls will be made to flip and reset.
 *
 * Template (python3):
 *     class Solution:
 *
 *         def __init__(self, m: int, n: int):
 *
 *
 *         def flip(self) -> List[int]:
 *
 *
 *         def reset(self) -> None:
 *
 *
 *
 *     # Your Solution object will be instantiated and called as such:
 *     # obj = Solution(m, n)
 *     # param_1 = obj.flip()
 *     # obj.reset()
 */

use std::collections::HashMap;
use wasm_libs::*;

struct Solution {
    m: i32,
    n: i32,
    total: i32,
    map: HashMap<i32, i32>,
}

impl Solution {
    fn new(m: i32, n: i32) -> Self {
        todo!();
    }

    fn flip(&mut self) -> Vec<i32> {
        todo!();
    }

    fn reset(&mut self) {
        todo!();
    }
}

fn solve(m: i32, n: i32, num_flips: i32) -> Vec<Vec<i32>> {
    let mut sol = Solution::new(m, n);
    let mut out = Vec::new();
    for _ in 0..num_flips {
        out.push(sol.flip());
    }
    out
}

fn main() {
    let m = read_int();
    let n = read_int();
    let num_flips = read_int();
    for pt in solve(m, n, num_flips) {
        write_ints(&pt);
    }
    std::process::exit(0);
}
