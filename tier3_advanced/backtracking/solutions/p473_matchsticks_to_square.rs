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
    if matchsticks.is_empty() {
        return false;
    }
    let total: i64 = matchsticks.iter().map(|&x| x as i64).sum();
    if total % 4 != 0 {
        return false;
    }
    let side = (total / 4) as i32;
    matchsticks.sort_by(|a, b| b.cmp(a));
    if matchsticks[0] > side {
        return false;
    }
    let n = matchsticks.len();
    let mut sides = [0i32; 4];

    fn bt(
        sticks: &[i32],
        idx: usize,
        n: usize,
        side: i32,
        sides: &mut [i32; 4],
    ) -> bool {
        if idx == n {
            return sides[0] == side && sides[1] == side && sides[2] == side && sides[3] == side;
        }
        for i in 0..4 {
            if sides[i] + sticks[idx] <= side {
                sides[i] += sticks[idx];
                if bt(sticks, idx + 1, n, side, sides) {
                    return true;
                }
                sides[i] -= sticks[idx];
                if sides[i] == 0 {
                    break;
                }
            }
        }
        false
    }

    bt(&matchsticks, 0, n, side, &mut sides)
}

fn main() {
    let matchsticks = read_ints();
    let result = makesquare(matchsticks);
    write_bool(result);
}
