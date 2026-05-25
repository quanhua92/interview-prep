/*
 * P403: Frog Jump [PREMIUM] (Hard)
 * https://leetcode.com/problems/frog-jump/
 * Topics: Array, Dynamic Programming
 *
 * A frog is crossing a river. The river is divided into some number of units, and at each unit, there may or may not exist a stone. The frog can jump on a stone, but it must not jump into the water.
 * Given a list of stones positions (in units) in sorted ascending order, determine if the frog can cross the river by landing on the last stone. Initially, the frog is on the first stone and assumes the first jump must be 1 unit.
 * If the frog's last jump was k units, its next jump must be either k - 1, k, or k + 1 units. The frog can only jump in the forward direction.
 * Example 1:
 *     Input: stones = [0,1,3,5,6,8,12,17]
 *     Output: true
 *     Explanation: The frog can jump to the last stone by jumping 1 unit to the 2nd stone, then 2 units to the 3rd stone, then 2 units to the 4th stone, then 3 units to the 6th stone, 4 units to the 7th stone, and 5 units to the 8th stone.
 *
 * Example 2:
 *     Input: stones = [0,1,2,3,4,8,9,11]
 *     Output: false
 *     Explanation: There is no way to jump to the last stone as the gap between the 5th and 6th stone is too large.
 *
 * Constraints:
 *     - 2 <= stones.length <= 2000
 *     - 0 <= stones[i] <= 231 - 1
 *     - stones[0] == 0
 *     - stones is sorted in a strictly increasing order.
 *
 * Template (python3):
 *     class Solution:
 *         def canCross(self, stones: List[int]) -> bool:
 */


use rstest;

fn can_cross(stones: &[i32]) -> bool {
    let n = stones.len();
    let stones_i64: Vec<i64> = stones.iter().map(|&x| x as i64).collect();
    let mut dp = vec![vec![false; n + 1]; n];
    dp[0][0] = true;
    for i in 0..n {
        for k in 0..=n {
            if !dp[i][k] { continue; }
            let step_start = if k == 0 { 1 } else { k.saturating_sub(1) };
            for step in step_start..=k + 1 {
                let target = stones_i64[i] + step as i64;
                match stones_i64[i + 1..].binary_search(&target) {
                    Ok(j) => { dp[i + 1 + j][step] = true; }
                    Err(_) => {}
                }
            }
        }
    }
    (0..=n).any(|k| dp[n - 1][k])
}

fn main() {
    struct TC<'a> { label: &'a str, stones: &'static [i32], expected: bool }
    let tests: &[TC] = &[
        TC { label: "example 1", stones: &[0,1,3,5,6,8,12,17], expected: true },
        TC { label: "example 2", stones: &[0,1,2,3,4,8,9,11], expected: false },
        TC { label: "minimum 2 stones", stones: &[0,1], expected: true },
        TC { label: "gap too large for first jump", stones: &[0,2], expected: false },
        TC { label: "increasing jumps 1,2,3,4,5,6", stones: &[0,1,3,6,10,15,21], expected: true },
        TC { label: "consecutive stones", stones: &[0,1,2,3,4,5,6,7,8,9], expected: true },
    ];
    let mut passed = 0;
    for (i, tc) in tests.iter().enumerate() {
        let got = can_cross(tc.stones);
        if got == tc.expected {
            passed += 1;
            println!("  Test {} ({}): PASS", i + 1, tc.label);
        } else {
            println!("  Test {} ({}): FAIL (expected {}, got {})", i + 1, tc.label, tc.expected, got);
        }
    }
    println!("\n  {}/{} passed", passed, tests.len());
    std::process::exit(if passed == tests.len() { 0 } else { 1 });
}
