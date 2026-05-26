/*
 * P495: Teemo Attacking [PREMIUM] (Easy)
 * https://leetcode.com/problems/teemo-attacking/
 * Topics: Array, Simulation
 * 
 * Our hero Teemo is attacking an enemy Ashe with poison attacks! When Teemo attacks Ashe, Ashe gets poisoned for a exactly duration seconds. More formally, an attack at second t will mean Ashe is poisoned during the inclusive time interval [t, t + duration - 1]. If Teemo attacks again before the poison effect ends, the timer for it is reset, and the poison effect will end duration seconds after the new attack.
 * You are given a non-decreasing integer array timeSeries, where timeSeries[i] denotes that Teemo attacks Ashe at second timeSeries[i], and an integer duration.
 * Return the total number of seconds that Ashe is poisoned.
 * Example 1:
 *     Input: timeSeries = [1,4], duration = 2
 *     Output: 4
 *     Explanation: Teemo's attacks on Ashe go as follows:
 *     - At second 1, Teemo attacks, and Ashe is poisoned for seconds 1 and 2.
 *     - At second 4, Teemo attacks, and Ashe is poisoned for seconds 4 and 5.
 *     Ashe is poisoned for seconds 1, 2, 4, and 5, which is 4 seconds in total.
 * 
 * Example 2:
 *     Input: timeSeries = [1,2], duration = 2
 *     Output: 3
 *     Explanation: Teemo's attacks on Ashe go as follows:
 *     - At second 1, Teemo attacks, and Ashe is poisoned for seconds 1 and 2.
 *     - At second 2 however, Teemo attacks again and resets the poison timer. Ashe is poisoned for seconds 2 and 3.
 *     Ashe is poisoned for seconds 1, 2, and 3, which is 3 seconds in total.
 * 
 * Constraints:
 *     - 1 <= timeSeries.length <= 104
 *     - 0 <= timeSeries[i], duration <= 107
 *     - timeSeries is sorted in non-decreasing order.
 * 
 * Template (python3):
 *     class Solution:
 *         def findPoisonedDuration(self, timeSeries: List[int], duration: int) -> int:
 */
fn find_poisoned_duration(time_series: &[i32], duration: i32) -> i32 {
    todo!()
}

fn main() {
    struct Test { label: &'static str, input: &'static [i32], duration: i32, expected: i32 }
    let tests: &[Test] = &[
        Test { label: "example 1", input: &[1, 4], duration: 2, expected: 4 },
        Test { label: "example 2", input: &[1, 2], duration: 2, expected: 3 },
        Test { label: "single attack", input: &[1], duration: 2, expected: 2 },
        Test { label: "consecutive attacks, duration 1", input: &[1, 2, 3, 4, 5], duration: 1, expected: 5 },
        Test { label: "non-overlapping attacks", input: &[1, 3, 5, 7, 9], duration: 2, expected: 10 },
        Test { label: "duplicate timestamps", input: &[1, 1, 1, 1], duration: 5, expected: 5 },
    ];
    let mut passed = 0;
    for (i, t) in tests.iter().enumerate() {
        let got = find_poisoned_duration(t.input, t.duration);
        if got == t.expected {
            println!("  Test {} ({}): PASS", i + 1, t.label);
            passed += 1;
        } else {
            println!("  Test {} ({}): FAIL", i + 1, t.label);
            println!("    Expected: {}\n    Got: {}", t.expected, got);
        }
    }
    println!("\n  {}/{} passed", passed, tests.len());
    std::process::exit(if passed == tests.len() { 0 } else { 1 });
}
