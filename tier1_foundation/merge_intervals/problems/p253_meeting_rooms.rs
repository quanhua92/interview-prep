/*
 * P253: Meeting Rooms II (Medium)
 * https://leetcode.com/problems/meeting-rooms-ii/
 * Topics: Array, Two Pointers, Sorting, Heap (Priority Queue), Prefix Sum
 *
 * Given an array of meeting time intervals intervals where intervals[i] = [starti, endi], return the minimum number of conference rooms required.
 *
 * Example 1:
 *     Input: intervals = [[0,30],[5,10],[15,20]]
 *     Output: 2
 *
 * Example 2:
 *     Input: intervals = [[7,10],[2,4]]
 *     Output: 1
 *
 * Hint: Sort start and end times separately, then use two pointers to count concurrent meetings.
 */

use wasm_libs::*;

fn solve(intervals: &Vec<[i32; 2]>) -> i32 {
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
    write_int(solve(&intervals));
    std::process::exit(0);
}
