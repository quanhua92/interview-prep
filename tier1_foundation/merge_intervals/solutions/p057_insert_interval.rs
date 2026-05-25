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
 * Constraints:
 *     - 0 <= intervals.length <= 104
 *     - intervals[i].length == 2
 *     - 0 <= starti <= endi <= 105
 *     - intervals is sorted by starti in ascending order.
 *     - newInterval.length == 2
 *     - 0 <= start <= end <= 105
 *
 * Hints:
 *     - Intervals Array is sorted. Can you use Binary Search to find the correct position to insert the new Interval.?
 *     - Can you try merging the overlapping intervals while inserting the new interval?
 *     - This can be done by comparing the end of the last interval with the start of the new interval and vice versa.
 *
 * Template (python3):
 *     class Solution:
 *         def insert(self, intervals: List[List[int]], newInterval: List[int]) -> List[List[int]]:
 *
 * Hint: Add non-overlapping before, merge overlapping, add non-overlapping after.
 */


use rstest::{TestCase, run_tests};

fn solve(arr: &[i32], num_intervals: i32) -> Vec<i32> {
    let num_intervals = num_intervals as usize;
    let mut new_start = arr[2 * num_intervals];
    let mut new_end = arr[2 * num_intervals + 1];
    let mut result = Vec::with_capacity((num_intervals + 1) * 2);
    let mut i = 0;

    while i < num_intervals && arr[2 * i + 1] < new_start {
        result.push(arr[2 * i]);
        result.push(arr[2 * i + 1]);
        i += 1;
    }

    while i < num_intervals && arr[2 * i] <= new_end {
        new_start = new_start.min(arr[2 * i]);
        new_end = new_end.max(arr[2 * i + 1]);
        i += 1;
    }

    result.push(new_start);
    result.push(new_end);

    while i < num_intervals {
        result.push(arr[2 * i]);
        result.push(arr[2 * i + 1]);
        i += 1;
    }

    result
}

fn main() {
    let tests: &[TestCase] = &[
        TestCase { label: "example 1", input_arr: &[1,3,6,9,2,5], target: 2, expected: &[1,5,6,9] },
        TestCase { label: "example 2", input_arr: &[1,2,3,5,6,7,8,10,12,16,4,8], target: 5, expected: &[1,2,3,10,12,16] },
        TestCase { label: "empty intervals", input_arr: &[5,7], target: 0, expected: &[5,7] },
        TestCase { label: "contained", input_arr: &[1,5,2,3], target: 1, expected: &[1,5] },
        TestCase { label: "insert before all", input_arr: &[3,5,6,9,1,2], target: 2, expected: &[1,2,3,5,6,9] },
        TestCase { label: "insert after all", input_arr: &[1,2,3,5,6,9], target: 2, expected: &[1,2,3,5,6,9] },
        TestCase { label: "merge with first interval", input_arr: &[1,3,6,9,0,2], target: 2, expected: &[0,3,6,9] },
        TestCase { label: "merge with last interval", input_arr: &[1,3,6,9,8,10], target: 2, expected: &[1,3,6,10] },
        TestCase { label: "bridge gap between intervals", input_arr: &[1,2,4,5,2,4], target: 2, expected: &[1,5] },
    ];

    std::process::exit(run_tests!("57. Insert Interval", solve, tests));
}
