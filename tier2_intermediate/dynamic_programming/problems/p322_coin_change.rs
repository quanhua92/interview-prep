/*
 * P322: Coin Change (Medium)
 * https://leetcode.com/problems/coin-change/
 * Topics: Array, Dynamic Programming, Breadth-First Search
 * 
 * You are given an integer array coins representing coins of different denominations and an integer amount representing a total amount of money.
 * Return the fewest number of coins that you need to make up that amount. If that amount of money cannot be made up by any combination of the coins, return -1.
 * You may assume that you have an infinite number of each kind of coin.
 * 
 * Example 1:
 *     Input: coins = [1,2,5], amount = 11
 *     Output: 3
 *     Explanation: 11 = 5 + 5 + 1
 * 
 * Example 2:
 *     Input: coins = [2], amount = 3
 *     Output: -1
 * 
 * Example 3:
 *     Input: coins = [1], amount = 0
 *     Output: 0
 * 
 * Constraints:
 *     - 1 <= coins.length <= 12
 *     - 1 <= coins[i] <= 231 - 1
 *     - 0 <= amount <= 104
 * 
 * Template (python3):
 *     class Solution:
 *         def coinChange(self, coins: List[int], amount: int) -> int:
 * 
 * Hint: Use bottom-up DP where dp[i] is the minimum coins needed for amount i.
 */
use rstest;

fn coin_change(coins: &[i32], amount: i32) -> i32 {
    todo!()
}

fn main() {
    struct TC<'a> { label: &'a str, coins: &'static [i32], amount: i32, expected: i32 }
    let tests: &[TC] = &[
        TC { label: "example 1", coins: &[1,2,5], amount: 11, expected: 3 },
        TC { label: "example 2", coins: &[2], amount: 3, expected: -1 },
        TC { label: "zero amount", coins: &[1], amount: 0, expected: 0 },
        TC { label: "smallest amount", coins: &[1], amount: 1, expected: 1 },
        TC { label: "suboptimal greedy", coins: &[1,3,4], amount: 6, expected: 2 },
        TC { label: "coin larger than amount", coins: &[2], amount: 1, expected: -1 },
        TC { label: "single coin exact match", coins: &[7], amount: 7, expected: 1 },
        TC { label: "large amount", coins: &[1,2,5], amount: 100, expected: 20 },
        TC { label: "multiple denominations", coins: &[2,5,10,1], amount: 27, expected: 4 },
    ];
    let mut passed = 0;
    for (i, tc) in tests.iter().enumerate() {
        let got = coin_change(tc.coins, tc.amount);
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
