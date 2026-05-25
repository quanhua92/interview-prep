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
 *     - 1 <= m, n <= 104
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


use std::collections::{HashMap, HashSet};

fn solve(m: i64, n: i64, num_flips: i64) -> i64 {
    let mut total = m * n;
    let mut mapping: HashMap<i64, i64> = HashMap::new();
    let mut results: HashSet<i64> = HashSet::new();

    for f in 0..num_flips {
        total -= 1;
        let idx = *mapping.get(&f).unwrap_or(&f);
        let last = *mapping.get(&total).unwrap_or(&total);
        mapping.insert(f, last);
        results.insert(idx);
    }
    results.len() as i64
}

fn main() {
    let tests: Vec<(&str, i64, i64, i64, i64)> = vec![
        ("single cell one flip", 1, 1, 1, 1),
        ("flip all cells in 2x2", 2, 2, 4, 4),
        ("column matrix flip all", 3, 1, 3, 3),
    ];

    let mut passed = 0;
    println!("\n============================================================");
    println!("  519. Random Flip Matrix");
    println!("============================================================");
    for (i, (label, m, n, num_flips, expected)) in tests.iter().enumerate() {
        let got = solve(*m, *n, *num_flips);
        let ok = got == *expected;
        if ok { passed += 1; }
        println!("  Test {} ({}): {}", i + 1, label, if ok { "PASS" } else { "FAIL" });
    }
    println!("\n  {}/{} passed", passed, tests.len());
    println!("============================================================\n");
    std::process::exit(if passed == tests.len() { 0 } else { 1 });
}
