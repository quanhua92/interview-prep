/*
 * P84: Largest Rectangle in Histogram (Hard)
 * https://leetcode.com/problems/largest-rectangle-in-histogram/
 * Topics: Array, Stack, Monotonic Stack
 *
 * Given an array of integers heights representing the histogram's bar height where the width of each bar is 1, return the area of the largest rectangle in the histogram.
 *
 * Example 1:
 *     Input: heights = [2,1,5,6,2,3]
 *     Output: 10
 *     Explanation: The above is a histogram where width of each bar is 1.
 *     The largest rectangle is shown in the red area, which has an area = 10 units.
 *
 * Example 2:
 *     Input: heights = [2,4]
 *     Output: 4
 *
 * Constraints:
 *     - 1 <= heights.length <= 10^5
 *     - 0 <= heights[i] <= 10^4
 *
 * Template (python3):
 *     class Solution:
 *         def largestRectangleArea(self, heights: List[int]) -> int:
 *
 * Hint: Use a monotonic increasing stack with a sentinel to compute max rectangle area.
 */

use wasm_libs::*;

impl Solution {
    fn largest_rectangle_area(heights: &[i32]) -> i32 {
        let n = heights.len();
        let mut stack: Vec<usize> = Vec::new();
        let mut max_area = 0i32;
        for i in 0..=n {
            let h = if i < n { heights[i] } else { 0 };
            while !stack.is_empty() && h < heights[*stack.last().unwrap()] {
                let height = heights[stack.pop().unwrap()];
                let width = if stack.is_empty() { i as i32 } else { (i - stack.last().unwrap() - 1) as i32 };
                max_area = std::cmp::max(max_area, height * width);
            }
            stack.push(i);
        }
        max_area
    }
}

struct Solution;

fn main() {
    let heights = read_ints();
    write_int(Solution::largest_rectangle_area(&heights));
    std::process::exit(0);
}
