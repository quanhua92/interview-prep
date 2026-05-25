/*
 * P552: Student Attendance Record II [PREMIUM] (Hard)
 * https://leetcode.com/problems/student-attendance-record-ii/
 * Topics: Dynamic Programming
 *
 * An attendance record for a student can be represented as a string where each character signifies whether the student was absent, late, or present on that day. The record only contains the following three characters:
 * Any student is eligible for an attendance award if they meet both of the following criteria:
 * Given an integer n, return the number of possible attendance records of length n that make a student eligible for an attendance award. The answer may be very large, so return it modulo 109 + 7.
 * Example 1:
 *     Input: n = 2
 *     Output: 8
 *     Explanation: There are 8 records with length 2 that are eligible for an award:
 *     "PP", "AP", "PA", "LP", "PL", "AL", "LA", "LL"
 *     Only "AA" is not eligible because there are 2 absences (there need to be fewer than 2).
 *
 * Example 2:
 *     Input: n = 1
 *     Output: 3
 *
 * Example 3:
 *     Input: n = 10101
 *     Output: 183236316
 *
 * Constraints:
 *     - 1 <= n <= 105
 *
 * Template (python3):
 *     class Solution:
 *         def checkRecord(self, n: int) -> int:
 */


use rstest;

fn check_record(n: i32) -> i32 {
    let mod_val = 1_000_000_007i64;
    let mut dp = [[[0i64; 3]; 2]; 2];
    dp[0][0][0] = 1;
    for i in 0..n as usize {
        let cur = i % 2;
        let nxt = 1 - cur;
        for a in 0..2 {
            for l in 0..3 {
                dp[nxt][a][l] = 0;
            }
        }
        for a in 0..2 {
            for l in 0..3 {
                let val = dp[cur][a][l];
                if val == 0 { continue; }
                dp[nxt][a][0] = (dp[nxt][a][0] + val) % mod_val;
                if a < 1 { dp[nxt][a + 1][0] = (dp[nxt][a + 1][0] + val) % mod_val; }
                if l < 2 { dp[nxt][a][l + 1] = (dp[nxt][a][l + 1] + val) % mod_val; }
            }
        }
    }
    let last = (n as usize) % 2;
    let mut result = 0i64;
    for a in 0..2 {
        for l in 0..3 {
            result = (result + dp[last][a][l]) % mod_val;
        }
    }
    result as i32
}

fn main() {
    struct TC { label: &'static str, n: i32, expected: i32 }
    let tests: &[TC] = &[
        TC { label: "example 1", n: 2, expected: 8 },
        TC { label: "example 2", n: 1, expected: 3 },
        TC { label: "example 3", n: 10101, expected: 183236316 },
        TC { label: "n=3", n: 3, expected: 19 },
        TC { label: "n=4", n: 4, expected: 43 },
        TC { label: "n=10", n: 10, expected: 3536 },
    ];
    let mut passed = 0;
    for (i, tc) in tests.iter().enumerate() {
        let got = check_record(tc.n);
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
