/*
 * P473: Matchsticks to Square [PREMIUM] (Medium)
 * https://leetcode.com/problems/matchsticks-to-square/
 * Topics: Array, Dynamic Programming, Backtracking, Bit Manipulation, Bitmask
 *
 * You are given an integer array matchsticks where matchsticks[i] is the length of the ith matchstick. You want to use all the matchsticks to make one square. You should not break any stick, but you can link them up, and each matchstick must be used exactly one time.
 * Return true if you can make this square and false otherwise.
 * Example 1:
 *     Input: matchsticks = [1,1,2,2,2]
 *     Output: true
 *     Explanation: You can form a square with length 2, one side of the square came two sticks with length 1.
 *
 * Example 2:
 *     Input: matchsticks = [3,3,3,3,4]
 *     Output: false
 *     Explanation: You cannot find a way to form a square with all the matchsticks.
 *
 * Constraints:
 *     - 1 <= matchsticks.length <= 15
 *     - 1 <= matchsticks[i] <= 108
 *
 * Hint: Treat the matchsticks as an array. Can we split the array into 4 equal parts?
 * Hint: Every matchstick can belong to either of the 4 sides. We don't know which one. Maybe try out all options!
 * Hint: For every matchstick, we have to try out each of the 4 options i.e. which side it can belong to. We can make use of recursion for this.
 * Hint: We don't really need to keep track of which matchsticks belong to a particular side during recursion. We just need to keep track of the <b>length</b> of each of the 4 sides.
 * Hint: When all matchsticks have been used we simply need to see the length of all 4 sides. If they're equal, we have a square on our hands!
 *
 * Template (python3):
 *     class Solution:
 *         def makesquare(self, matchsticks: List[int]) -> bool:
 */


#[allow(unused_imports)]
use rstest;

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
    println!("\n============================================================");
    println!("  473. Matchsticks to Square");
    println!("============================================================");

    let mut passed = 0;

    {
        if makesquare(vec![1, 1, 2, 2, 2]) { passed += 1; println!("  Test 1 (example 1): PASS"); }
        else { println!("  Test 1 (example 1): FAIL"); }
    }
    {
        if !makesquare(vec![3, 3, 3, 3, 4]) { passed += 1; println!("  Test 2 (example 2): PASS"); }
        else { println!("  Test 2 (example 2): FAIL"); }
    }
    {
        if makesquare(vec![5, 5, 5, 5]) { passed += 1; println!("  Test 3 (four equal sticks): PASS"); }
        else { println!("  Test 3 (four equal sticks): FAIL"); }
    }
    {
        if !makesquare(vec![2, 2, 2, 2, 2, 2]) { passed += 1; println!("  Test 4 (all twos cannot form square): PASS"); }
        else { println!("  Test 4 (all twos cannot form square): FAIL"); }
    }
    {
        if makesquare(vec![1, 1, 1, 1]) { passed += 1; println!("  Test 5 (minimal square): PASS"); }
        else { println!("  Test 5 (minimal square): FAIL"); }
    }
    {
        if makesquare(vec![3, 3, 3, 3]) { passed += 1; println!("  Test 6 (each stick one side): PASS"); }
        else { println!("  Test 6 (each stick one side): FAIL"); }
    }

    println!("\n  {}/6 passed", passed);
    println!("============================================================\n");

    std::process::exit(if passed == 6 { 0 } else { 1 });
}
