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
 *     - 1 <= temperatures.length <= 105
 *     - 30 <= temperatures[i] <= 100
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

fn main() {
    struct Case { label: &'static str, input: &'static [i32], expected: &'static [i32] }
    let tests: &[Case] = &[
        Case { label: "example 1", input: &[73, 74, 75, 71, 69, 72, 76, 73], expected: &[1, 1, 4, 2, 1, 1, 0, 0] },
        Case { label: "example 2", input: &[30, 40, 50, 60], expected: &[1, 1, 1, 0] },
        Case { label: "example 3", input: &[30, 60, 90], expected: &[1, 1, 0] },
        Case { label: "single element", input: &[50], expected: &[0] },
        Case { label: "all same temps", input: &[50, 50, 50], expected: &[0, 0, 0] },
        Case { label: "strictly decreasing", input: &[90, 80, 70, 60], expected: &[0, 0, 0, 0] },
        Case { label: "all same then warmer", input: &[50, 50, 50, 60], expected: &[3, 2, 1, 0] },
    ];

    println!("\n============================================================");
    println!("  739. Daily Temperatures");
    println!("============================================================");
    let mut passed = 0;
    for (i, tc) in tests.iter().enumerate() {
        let got = daily_temperatures(tc.input);
        if got == tc.expected {
            passed += 1;
            println!("  Test {} ({}): PASS", i + 1, tc.label);
        } else {
            println!("  Test {} ({}): FAIL", i + 1, tc.label);
            println!("    Expected: {:?}\n    Got:      {:?}", tc.expected, got);
        }
    }
    println!("\n  {}/{} passed", passed, tests.len());
    println!("============================================================\n");
    std::process::exit(if passed == tests.len() { 0 } else { 1 });
}
