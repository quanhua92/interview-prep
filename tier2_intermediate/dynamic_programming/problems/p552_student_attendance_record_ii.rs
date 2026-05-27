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

use wasm_libs::*;

impl Solution {
    fn check_record(n: i32) -> i32 {
        todo!()
    }
}

struct Solution;

fn main() {
    let n = read_int();
    write_int(check_record(n));
}
