/*
 * P56: Merge Intervals (Medium)
 * https://leetcode.com/problems/merge-intervals/
 * Topics: Array, Sorting
 *
 * Given an array of intervals where intervals[i] = [starti, endi], merge all overlapping intervals, and return an array of the non-overlapping intervals that cover all the intervals in the input.
 *
 * Example 1:
 *     Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
 *     Output: [[1,6],[8,10],[15,18]]
 *     Explanation: Since intervals [1,3] and [2,6] overlap, merge them into [1,6].
 *
 * Example 2:
 *     Input: intervals = [[1,4],[4,5]]
 *     Output: [[1,5]]
 *     Explanation: Intervals [1,4] and [4,5] are considered overlapping.
 *
 * Constraints:
 *     - 1 <= intervals.length <= 10^4
 *     - intervals[i].length == 2
 *     - 0 <= starti <= endi <= 10^4
 *
 * Template (python3):
 *     class Solution:
 *         def merge(self, intervals: List[List[int]]) -> List[List[int]]:
 *
 * Hint: Sort intervals by start time, then merge overlapping ones.
 */

use wasm_libs::*;

fn solve(intervals: &mut Vec<[i32; 2]>) {
    todo!();
}

fn main() {
    let n = read_int();
    let mut intervals: Vec<[i32; 2]> = (0..n)
        .map(|_| {
            let row = read_ints();
            [row[0], row[1]]
        })
        .collect();
    solve(&mut intervals);
    std::process::exit(0);
}
