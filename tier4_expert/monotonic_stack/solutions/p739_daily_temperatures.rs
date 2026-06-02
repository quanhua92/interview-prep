/*
 * P739: Daily Temperatures (Medium)
 * https://leetcode.com/problems/daily-temperatures/
 * Topics: Array, Stack, Monotonic Stack
 *
 * Given an array of integers temperatures represents the daily temperatures, return an array answer such that answer[i] is the number of days you have to wait after the ith day to get a warmer temperature. If there is no future day for which this is possible, keep answer[i] == 0 instead.
 *
 * Example 1:
 *     Input: temperatures = [73,74,75,71,69,72,76,73]
 *     Output: [1,1,4,2,1,1,0,0]
 *
 * Example 2:
 *     Input: temperatures = [30,40,50,60]
 *     Output: [1,1,1,0]
 *
 * Example 3:
 *     Input: temperatures = [30,60,90]
 *     Output: [1,1,0]
 *
 * Constraints:
 *     - 1 <= temperatures.length <= 10^5
 *     - 30 <= temperatures[i] <= 100
 *
 * Hints:
 *     - If the temperature is say, 70 today, then in the future a warmer temperature must be either 71, 72, 73, ..., 99, or 100.  We could remember when all of them occur next.
 *
 * Template (python3):
 *     class Solution:
 *         def dailyTemperatures(self, temperatures: List[int]) -> List[int]:
 *
 * Hint: Use a monotonic decreasing stack to track indices of warmer days.
 */

use wasm_libs::*;

impl Solution {
    fn daily_temperatures(temperatures: &[i32]) -> Vec<i32> {
        let n = temperatures.len();
        let mut answer = vec![0i32; n];
        let mut stack: Vec<usize> = Vec::new();
        for i in 0..n {
            while !stack.is_empty() && temperatures[i] > temperatures[*stack.last().unwrap()] {
                let j = stack.pop().unwrap();
                answer[j] = (i - j) as i32;
            }
            stack.push(i);
        }
        answer
    }
}

struct Solution;

fn main() {
    let temperatures = read_ints();
    write_ints(&Solution::daily_temperatures(&temperatures));
    std::process::exit(0);
}
