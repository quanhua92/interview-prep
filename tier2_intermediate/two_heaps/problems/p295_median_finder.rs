/*
 * P295: Find Median from Data Stream (Hard)
 * https://leetcode.com/problems/find-median-from-data-stream/
 * Topics: Two Pointers, Design, Sorting, Heap (Priority Queue), Data Stream
 *
 * The median is the middle value in an ordered integer list. If the size of the list is even, there is no middle value, and the median is the mean of the two middle values.
 * Implement the MedianFinder class:
 *
 * Constraints:
 *     - -105 <= num <= 105
 *     - There will be at least one element in the data structure before calling findMedian.
 *     - At most 5 * 104 calls will be made to addNum and findMedian.
 *
 * Template (python3):
 *     class MedianFinder:
 *         def __init__(self):
 *         def addNum(self, num: int) -> None:
 *         def findMedian(self) -> float:
 *
 * Hint: Use a max-heap for the lower half and a min-heap for the upper half.
 */

use wasm_libs::*;

impl Solution {
    fn solve(stream: &[i32]) -> Vec<f64> {
        todo!()
    }
}

struct Solution;

fn main() {
    let stream = read_ints();
    let result = Solution::solve(&stream);
    for m in &result {
        println!("{:.6}", m);
    }
    std::process::exit(0);
}
