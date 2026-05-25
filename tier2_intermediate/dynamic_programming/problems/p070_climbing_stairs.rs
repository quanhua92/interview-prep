/*
 * P70: Climbing Stairs (Easy)
 * https://leetcode.com/problems/climbing-stairs/
 * Topics: Math, Dynamic Programming, Memoization
 * 
 * You are climbing a staircase. It takes n steps to reach the top.
 * Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?
 * 
 * Example 1:
 *     Input: n = 2
 *     Output: 2
 *     Explanation: There are two ways to climb to the top.
 *     1. 1 step + 1 step
 *     2. 2 steps
 * 
 * Example 2:
 *     Input: n = 3
 *     Output: 3
 *     Explanation: There are three ways to climb to the top.
 *     1. 1 step + 1 step + 1 step
 *     2. 1 step + 2 steps
 *     3. 2 steps + 1 step
 * 
 * Constraints:
 *     - 1 <= n <= 45
 * 
 * Hints:
 *     - To reach nth step, what could have been your previous steps? (Think about the step sizes)
 * 
 * Template (python3):
 *     class Solution:
 *         def climbStairs(self, n: int) -> int:
 * 
 * Hint: This is essentially Fibonacci -- each step depends on the two before it.
 */
use rstest;

fn climb_stairs(n: i32) -> i32 {
    todo!()
}

fn main() {
    struct TC { label: &'static str, n: i32, expected: i32 }
    let tests: &[TC] = &[
        TC { label: "example 1", n: 2, expected: 2 },
        TC { label: "example 2", n: 3, expected: 3 },
        TC { label: "base case", n: 1, expected: 1 },
        TC { label: "larger", n: 10, expected: 89 },
        TC { label: "max constraint", n: 45, expected: 1836311903 },
        TC { label: "n=4", n: 4, expected: 5 },
        TC { label: "n=5", n: 5, expected: 8 },
        TC { label: "n=6", n: 6, expected: 13 },
        TC { label: "n=20", n: 20, expected: 10946 },
        TC { label: "near max constraint", n: 44, expected: 1134903170 },
    ];
    let mut passed = 0;
    for (i, tc) in tests.iter().enumerate() {
        let got = climb_stairs(tc.n);
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
