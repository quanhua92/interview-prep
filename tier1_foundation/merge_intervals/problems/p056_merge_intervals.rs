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
 *     - 1 <= intervals.length <= 104
 *     - intervals[i].length == 2
 *     - 0 <= starti <= endi <= 104
 * 
 * Template (python3):
 *     class Solution:
 *         def merge(self, intervals: List[List[int]]) -> List[List[int]]:
 * 
 * Hint: Sort intervals by start time, then merge overlapping ones.
 */
use rstest::{TestCase, run_tests};

fn solve(flat: &[i32], _target: i32) -> Vec<i32> {
    todo!()
}

fn main() {
    static TESTS: &[TestCase] = &[
        TestCase { label: "example 1", input_arr: &[1,3,2,6,8,10,15,18], target: 0, expected: &[1,6,8,10,15,18] },
        TestCase { label: "example 2", input_arr: &[1,4,4,5], target: 0, expected: &[1,5] },
        TestCase { label: "overlapping start", input_arr: &[1,4,0,4], target: 0, expected: &[0,4] },
        TestCase { label: "single interval", input_arr: &[1,1], target: 0, expected: &[1,1] },
        TestCase { label: "all overlap into one", input_arr: &[1,4,2,3,3,5], target: 0, expected: &[1,5] },
        TestCase { label: "no overlaps", input_arr: &[1,2,3,4,5,6], target: 0, expected: &[1,2,3,4,5,6] },
        TestCase { label: "interval contains others", input_arr: &[1,10,2,3,4,5], target: 0, expected: &[1,10] },
        TestCase { label: "adjacent intervals touching", input_arr: &[1,2,2,3,3,4], target: 0, expected: &[1,4] },
    ];

    std::process::exit(run_tests!("P56: Merge Intervals", solve, TESTS));
}
