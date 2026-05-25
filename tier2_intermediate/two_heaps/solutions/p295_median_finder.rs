/*
 * P295: Find Median from Data Stream (Hard)
 * https://leetcode.com/problems/find-median-from-data-stream/
 * Topics: Two Pointers, Design, Sorting, Heap (Priority Queue), Data Stream
 *
 * The median is the middle value in an ordered integer list. If the size of the list is even, there is no middle value, and the median is the mean of the two middle values.
 * Implement the MedianFinder class:
 *
 * Example 1:
 *     Input
 *     ["MedianFinder", "addNum", "addNum", "findMedian", "addNum", "findMedian"]
 *     [[], [1], [2], [], [3], []]
 *     Output
 *     [null, null, null, 1.5, null, 2.0]
 *
 *     Explanation
 *     MedianFinder medianFinder = new MedianFinder();
 *     medianFinder.addNum(1);    // arr = [1]
 *     medianFinder.addNum(2);    // arr = [1, 2]
 *     medianFinder.findMedian(); // return 1.5 (i.e., (1 + 2) / 2)
 *     medianFinder.addNum(3);    // arr[1, 2, 3]
 *     medianFinder.findMedian(); // return 2.0
 *
 * Constraints:
 *     - -105 <= num <= 105
 *     - There will be at least one element in the data structure before calling findMedian.
 *     - At most 5 * 104 calls will be made to addNum and findMedian.
 *
 * Template (python3):
 *     class MedianFinder:
 *
 *         def __init__(self):
 *
 *
 *         def addNum(self, num: int) -> None:
 *
 *
 *         def findMedian(self) -> float:
 *
 *
 *
 *     # Your MedianFinder object will be instantiated and called as such:
 *     # obj = MedianFinder()
 *     # obj.addNum(num)
 *     # param_2 = obj.findMedian()
 *
 * Hint: Use a max-heap for the lower half and a min-heap for the upper half.
 */


use std::collections::BinaryHeap;
use std::cmp::Reverse;

struct MedianFinder {
    small: BinaryHeap<i32>,
    large: BinaryHeap<Reverse<i32>>,
}

impl MedianFinder {
    fn new() -> Self {
        MedianFinder { small: BinaryHeap::new(), large: BinaryHeap::new() }
    }
    fn add_num(&mut self, num: i32) {
        self.small.push(num);
        self.large.push(Reverse(self.small.pop().unwrap()));
        if self.large.len() > self.small.len() {
            self.small.push(self.large.pop().unwrap().0);
        }
    }
    fn find_median(&self) -> f64 {
        if self.small.len() > self.large.len() {
            *self.small.peek().unwrap() as f64
        } else {
            (*self.small.peek().unwrap() as f64 + self.large.peek().unwrap().0 as f64) / 2.0
        }
    }
}

fn solve(stream: &[i32]) -> Vec<f64> {
    let mut mf = MedianFinder::new();
    let mut res = Vec::with_capacity(stream.len());
    for &num in stream {
        mf.add_num(num);
        res.push(mf.find_median());
    }
    res
}

fn feq(a: f64, b: f64) -> bool { (a - b).abs() < 1e-9 }

fn main() {
    struct Case<'a> { label: &'a str, input: &'a [i32], expected: &'a [f64] }
    let tests: &[Case] = &[
        Case { label: "stream median", input: &[5, 15, 1, 3], expected: &[5.0, 10.0, 5.0, 4.0] },
        Case { label: "two elements", input: &[1, 2], expected: &[1.0, 1.5] },
        Case { label: "single element", input: &[42], expected: &[42.0] },
        Case { label: "all same", input: &[3, 3, 3, 3], expected: &[3.0, 3.0, 3.0, 3.0] },
        Case { label: "negative numbers", input: &[-5, -3, -1, 0], expected: &[-5.0, -4.0, -3.0, -2.0] },
        Case { label: "alternating high low", input: &[100, 0, 100, 0, 100, 0], expected: &[100.0, 50.0, 100.0, 50.0, 100.0, 50.0] },
        Case { label: "descending order", input: &[10, 9, 8, 7, 6, 5], expected: &[10.0, 9.5, 9.0, 8.5, 8.0, 7.5] },
        Case { label: "extreme values", input: &[-100000, 100000], expected: &[-100000.0, 0.0] },
    ];

    println!("\n============================================================");
    println!("  295. Find Median from Data Stream");
    println!("============================================================");
    let mut passed = 0;
    for (i, tc) in tests.iter().enumerate() {
        let got = solve(tc.input);
        let ok = got.len() == tc.expected.len() && got.iter().zip(tc.expected.iter()).all(|(a, b)| feq(*a, *b));
        if ok {
            passed += 1;
            println!("  Test {} ({}): PASS", i + 1, tc.label);
        } else {
            println!("  Test {} ({}): FAIL", i + 1, tc.label);
            println!("    Expected: {:?}", tc.expected);
            println!("    Got:      {:?}", got);
        }
    }
    println!("\n  {}/{} passed", passed, tests.len());
    println!("============================================================\n");
    std::process::exit(if passed == tests.len() { 0 } else { 1 });
}
