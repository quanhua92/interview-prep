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
 *     - 0 <= value <= 104
 *     - At most 3 * 104 calls will be made to addNum and getIntervals.
 *     - At most 102 calls will be made to getIntervals.
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


fn solve_intervals(values: &[i32]) -> Vec<Vec<i32>> {
    let mut intervals: Vec<Vec<i32>> = Vec::new();
    for &v in values {
        let mut lo = v;
        let mut hi = v;
        let mut pos = intervals.iter().position(|iv| iv[0] >= lo).unwrap_or(intervals.len());
        if pos > 0 && intervals[pos - 1][1] >= lo - 1 {
            pos -= 1;
            lo = intervals[pos][0];
        }
        while pos < intervals.len() && intervals[pos][0] <= hi + 1 {
            hi = hi.max(intervals[pos][1]);
            intervals.remove(pos);
        }
        intervals.insert(pos, vec![lo, hi]);
    }
    intervals
}

fn main() {
    let tests: Vec<(&str, Vec<i32>, Vec<i32>)> = vec![
        ("example from problem", vec![1,3,7,2,6], vec![1,3,6,7]),
        ("adjacent values merge", vec![1,0], vec![0,1]),
        ("single zero", vec![0], vec![0,0]),
        ("no merges sorted output", vec![100,1,50], vec![1,1,50,50,100,100]),
        ("empty stream", vec![], vec![]),
    ];

    let mut passed = 0;
    println!("\n============================================================");
    println!("  352. Data Stream as Disjoint Intervals");
    println!("============================================================");
    for (i, (label, values, expected_flat)) in tests.iter().enumerate() {
        let got = solve_intervals(values);
        let got_flat: Vec<i32> = got.iter().flat_map(|iv| iv.iter().copied()).collect();
        let ok = got_flat == *expected_flat;
        if ok { passed += 1; }
        println!("  Test {} ({}): {}", i + 1, label, if ok { "PASS" } else { "FAIL" });
    }
    println!("\n  {}/{} passed", passed, tests.len());
    println!("============================================================\n");
    std::process::exit(if passed == tests.len() { 0 } else { 1 });
}
