/*
 * P480: Sliding Window Median (Hard)
 * https://leetcode.com/problems/sliding-window-median/
 * Topics: Array, Hash Table, Sliding Window, Heap (Priority Queue)
 *
 * You are given an integer array nums and an integer k. There is a sliding window of size k.
 * Return the median array for each window.
 *
 * Constraints:
 *     - 1 <= k <= nums.length <= 105
 *     - -231 <= nums[i] <= 231 - 1
 *
 * Template (python3):
 *     class Solution:
 *         def medianSlidingWindow(self, nums: List[int], k: int) -> List[float]:
 *
 * Hint: Use a max-heap for the small half and a min-heap for the large half with lazy deletion.
 */

use wasm_libs::*;

impl Solution {
    fn solve(nums: &[i32], k: usize) -> Vec<f64> {
        todo!()
    }
}

struct Solution;

fn main() {
    let nums = read_ints();
    let kline = read_ints();
    let k = kline[0] as usize;
    let result = Solution::solve(&nums, k);
    for m in &result {
        println!("{:.6}", m);
    }
    std::process::exit(0);
}
