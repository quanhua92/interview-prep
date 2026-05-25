/*
 * P518: Coin Change II [PREMIUM] (Medium)
 * https://leetcode.com/problems/coin-change-ii/
 * Topics: Array, Dynamic Programming
 *
 * You are given an integer array coins representing coins of different denominations and an integer amount representing a total amount of money.
 * Return the number of combinations that make up that amount. If that amount of money cannot be made up by any combination of the coins, return 0.
 * You may assume that you have an infinite number of each kind of coin.
 * The answer is guaranteed to fit into a signed 32-bit integer.
 * Example 1:
 *     Input: amount = 5, coins = [1,2,5]
 *     Output: 4
 *     Explanation: there are four ways to make up the amount:
 *     5=5
 *     5=2+2+1
 *     5=2+1+1+1
 *     5=1+1+1+1+1
 *
 * Example 2:
 *     Input: amount = 3, coins = [2]
 *     Output: 0
 *     Explanation: the amount of 3 cannot be made up just with coins of 2.
 *
 * Example 3:
 *     Input: amount = 10, coins = [10]
 *     Output: 1
 *
 * Constraints:
 *     - 1 <= coins.length <= 300
 *     - 1 <= coins[i] <= 5000
 *     - All the values of coins are unique.
 *     - 0 <= amount <= 5000
 *
 * Template (python3):
 *     class Solution:
 *         def change(self, amount: int, coins: List[int]) -> int:
 */


use rstest;

fn change(amount: i32, coins: &[i32]) -> i32 {
    let amt = amount as usize;
    let mut dp = vec![0i32; amt + 1];
    dp[0] = 1;
    for &c in coins {
        for a in c as usize..=amt {
            dp[a] += dp[a - c as usize];
        }
    }
    dp[amt]
}

fn main() {
    struct TC<'a> { label: &'a str, amount: i32, coins: &'static [i32], expected: i32 }
    let tests: &[TC] = &[
        TC { label: "example 1", amount: 5, coins: &[1,2,5], expected: 4 },
        TC { label: "example 2", amount: 3, coins: &[2], expected: 0 },
        TC { label: "example 3", amount: 10, coins: &[10], expected: 1 },
        TC { label: "zero amount", amount: 0, coins: &[1,2,5], expected: 1 },
        TC { label: "single coin exact amount", amount: 1, coins: &[1], expected: 1 },
        TC { label: "large amount", amount: 500, coins: &[1,2,5], expected: 12701 },
    ];
    let mut passed = 0;
    for (i, tc) in tests.iter().enumerate() {
        let got = change(tc.amount, tc.coins);
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
