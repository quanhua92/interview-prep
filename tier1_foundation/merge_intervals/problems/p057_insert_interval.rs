/*
 * P57: Insert Interval (Medium)
 * https://leetcode.com/problems/insert-interval/
 * Topics: Array
 *
 * You are given an array of non-overlapping intervals intervals where intervals[i] = [starti, endi] represent the start and the end of the ith interval and intervals is sorted in ascending order by starti. You are also given an interval newInterval = [start, end] that represents the start and end of another interval.
 * Insert newInterval into intervals such that intervals is still sorted in ascending order by starti and intervals still does not have any overlapping intervals (merge overlapping intervals if necessary).
 * Return intervals after the insertion.
 * Note that you don't need to modify intervals in-place. You can make a new array and return it.
 *
 * Example 1:
 *     Input: intervals = [[1,3],[6,9]], newInterval = [2,5]
 *     Output: [[1,5],[6,9]]
 *
 * Example 2:
 *     Input: intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
 *     Output: [[1,2],[3,10],[12,16]]
 *     Explanation: Because the new interval [4,8] overlaps with [3,5],[6,7],[8,10].
 *
 * Hint: Add non-overlapping before, merge overlapping, add non-overlapping after.
 */

use wasm_libs::*;

fn solve(intervals: &Vec<[i32; 2]>, new_interval: &mut [i32; 2]) -> Vec<[i32; 2]> {
    todo!()
}

fn main() {
    let n = read_int();
    let intervals: Vec<[i32; 2]> = (0..n)
        .map(|_| {
            let row = read_ints();
            [row[0], row[1]]
        })
        .collect();
    let ni = read_ints();
    let mut new_interval = [ni[0], ni[1]];
    let result = solve(&intervals, &mut new_interval);
    for row in &result {
        write_ints(row);
    }
    std::process::exit(0);
}
