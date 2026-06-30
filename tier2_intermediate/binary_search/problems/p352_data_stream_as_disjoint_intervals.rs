/*
 * P352: Data Stream as Disjoint Intervals [PREMIUM] (Hard)
 * https://leetcode.com/problems/data-stream-as-disjoint-intervals/
 * Topics: Binary Search, Design, Ordered Set
 *
 * Given a data stream input of non-negative integers a1, a2, ..., an, summarize the numbers seen so far as a list of disjoint intervals.
 *
 * Implement the SummaryRanges class:
 *
 * SummaryRanges() Initializes the object with an empty stream.
 * void addNum(int value) Adds the integer value to the stream.
 * int[][] getIntervals() Returns a summary of the integers in the stream currently as a list of disjoint intervals [starti, endi]. The answer should be sorted by starti.
 *
 *
 * Example 1:
 *
 * Input
 * ["SummaryRanges", "addNum", "getIntervals", "addNum", "getIntervals", "addNum", "getIntervals", "addNum", "getIntervals", "addNum", "getIntervals"]
 * [[], [1], [], [3], [], [7], [], [2], [], [6], []]
 * Output
 * [null, null, [[1, 1]], null, [[1, 1], [3, 3]], null, [[1, 1], [3, 3], [7, 7]], null, [[1, 3], [7, 7]], null, [[1, 3], [6, 7]]]
 *
 * Explanation
 * SummaryRanges summaryRanges = new SummaryRanges();
 * summaryRanges.addNum(1);      // arr = [1]
 * summaryRanges.getIntervals(); // return [[1, 1]]
 * summaryRanges.addNum(3);      // arr = [1, 3]
 * summaryRanges.getIntervals(); // return [[1, 1], [3, 3]]
 * summaryRanges.addNum(7);      // arr = [1, 3, 7]
 * summaryRanges.getIntervals(); // return [[1, 1], [3, 3], [7, 7]]
 * summaryRanges.addNum(2);      // arr = [1, 2, 3, 7]
 * summaryRanges.getIntervals(); // return [[1, 3], [7, 7]]
 * summaryRanges.addNum(6);      // arr = [1, 2, 3, 6, 7]
 * summaryRanges.getIntervals(); // return [[1, 3], [6, 7]]
 *
 *
 *
 * Constraints:
 *
 * 0 <= value <= 10^4
 * At most 3 * 10^4 calls will be made to addNum and getIntervals.
 * At most 10^2 calls will be made to getIntervals.
 *
 *
 * Follow up: What if there are lots of merges and the number of disjoint intervals is small compared to the size of the data stream?
 */

use wasm_libs::*;

struct SummaryRanges {
    intervals: Vec<(i32, i32)>,
}

impl SummaryRanges {
    fn new() -> Self {
        todo!();
    }

    fn add_num(&mut self, value: i32) {
        todo!();
    }

    fn get_intervals(&self) -> Vec<Vec<i32>> {
        todo!();
    }
}

fn solve(num_ops: i32) {
    let mut sr = SummaryRanges::new();
    for _ in 0..num_ops {
        let op = read_line();
        let argc = read_int();
        let args = if argc > 0 { read_ints() } else { Vec::new() };
        if op == "getIntervals" {
            let iv = sr.get_intervals();
            write_int(iv.len() as i32);
            for row in iv {
                write_ints(&row);
            }
        } else if op == "addNum" {
            sr.add_num(args[0]);
        }
    }
}

fn main() {
    solve(read_int());
    std::process::exit(0);
}
