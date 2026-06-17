/*
 * P352: Data Stream as Disjoint Intervals [PREMIUM] (Hard)
 * https://leetcode.com/problems/data-stream-as-disjoint-intervals/
 * Topics: Binary Search, Design, Ordered Set
 *
 * Given a data stream input of non-negative integers a1, a2, ..., an, summarize the numbers seen so far as a list of disjoint intervals.
 * Implement the SummaryRanges class:
 * Example 1:
 * Follow up: What if there are lots of merges and the number of disjoint intervals is small compared to the size of the data stream?
 *     Input
 * Example 1:
 *     ["SummaryRanges", "addNum", "getIntervals", "addNum", "getIntervals", "addNum", "getIntervals", "addNum", "getIntervals", "addNum", "getIntervals"]
 *     [[], [1], [], [3], [], [7], [], [2], [], [6], []]
 *     Output
 *     [null, null, [[1, 1]], null, [[1, 1], [3, 3]], null, [[1, 1], [3, 3], [7, 7]], null, [[1, 3], [7, 7]], null, [[1, 3], [6, 7]]]
 *
 *     Explanation
 *     SummaryRanges summaryRanges = new SummaryRanges();
 *     summaryRanges.addNum(1);      // arr = [1]
 *     summaryRanges.getIntervals(); // return [[1, 1]]
 *     summaryRanges.addNum(3);      // arr = [1, 3]
 *     summaryRanges.getIntervals(); // return [[1, 1], [3, 3]]
 *     summaryRanges.addNum(7);      // arr = [1, 3, 7]
 *     summaryRanges.getIntervals(); // return [[1, 1], [3, 3], [7, 7]]
 *     summaryRanges.addNum(2);      // arr = [1, 2, 3, 7]
 *     summaryRanges.getIntervals(); // return [[1, 3], [7, 7]]
 *     summaryRanges.addNum(6);      // arr = [1, 2, 3, 6, 7]
 *     summaryRanges.getIntervals(); // return [[1, 3], [6, 7]]
 *
 * Constraints:
 *     - 0 <= value <= 10^4
 *     - At most 3 * 10^4 calls will be made to addNum and getIntervals.
 *     - At most 10^2 calls will be made to getIntervals.
 *
 * Template (python3):
 *     class SummaryRanges:
 *
 *         def __init__(self):
 *
 *
 *         def addNum(self, value: int) -> None:
 *
 *
 *         def getIntervals(self) -> List[List[int]]:
 *
 *
 *
 *     # Your SummaryRanges object will be instantiated and called as such:
 *     # obj = SummaryRanges()
 *     # obj.addNum(value)
 *     # param_2 = obj.getIntervals()
 */

use wasm_libs::*;

struct SummaryRanges {
    intervals: Vec<(i32, i32)>,
}

impl SummaryRanges {
    fn new() -> Self {
        SummaryRanges { intervals: Vec::new() }
    }

    fn add_num(&mut self, value: i32) {
        let mut lo = value;
        let mut hi = value;
        let mut pos = self.intervals.partition_point(|&(s, _)| s < lo);
        if pos > 0 && self.intervals[pos - 1].1 >= lo - 1 {
            pos -= 1;
            lo = self.intervals[pos].0;
        }
        while pos < self.intervals.len() && self.intervals[pos].0 <= hi + 1 {
            hi = hi.max(self.intervals[pos].1);
            self.intervals.remove(pos);
        }
        self.intervals.insert(pos, (lo, hi));
    }

    fn get_intervals(&self) -> Vec<Vec<i32>> {
        self.intervals.iter().map(|&(s, e)| vec![s, e]).collect()
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
