/*
 * P70: Climbing Stairs (Easy)
 * https://leetcode.com/problems/climbing-stairs/
 * Topics: Math, Dynamic Programming, Memoization
 *
 * You are climbing a staircase. It takes n steps to reach the top.
 * Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?
 *
 * Constraints:
 *     - 1 <= n <= 45
 *
 * Hint: This is essentially Fibonacci -- each step depends on the two before it.
 */

use wasm_libs::*;

fn climb_stairs(n: i32) -> i32 {
    if n <= 2 { return n; }
    let (mut a, mut b) = (1, 2);
    for _ in 3..=n {
        let t = a + b;
        a = b;
        b = t;
    }
    b
}

fn main() {
    let n = read_int();
    write_int(climb_stairs(n));
    std::process::exit(0);
}
