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
 *     - 1 <= heights.length <= 105
 *     - 0 <= heights[i] <= 104
 *
 * Template (python3):
 *     class Solution:
 *         def largestRectangleArea(self, heights: List[int]) -> int:
 *
 * Hint: Use a monotonic increasing stack with a sentinel to compute max rectangle area.
 */


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

fn main() {
    struct Case { label: &'static str, input: &'static [i32], expected: i32 }
    let tests: &[Case] = &[
        Case { label: "example 1", input: &[2, 1, 5, 6, 2, 3], expected: 10 },
        Case { label: "example 2", input: &[2, 4], expected: 4 },
        Case { label: "single element", input: &[5], expected: 5 },
        Case { label: "all same heights", input: &[3, 3, 3], expected: 9 },
        Case { label: "contains zero height", input: &[2, 0, 2], expected: 2 },
        Case { label: "strictly increasing", input: &[1, 2, 3, 4, 5], expected: 9 },
    ];

    println!("\n============================================================");
    println!("  84. Largest Rectangle in Histogram");
    println!("============================================================");
    let mut passed = 0;
    for (i, tc) in tests.iter().enumerate() {
        let got = largest_rectangle_area(tc.input);
        if got == tc.expected {
            passed += 1;
            println!("  Test {} ({}): PASS", i + 1, tc.label);
        } else {
            println!("  Test {} ({}): FAIL", i + 1, tc.label);
            println!("    Expected: {}, Got: {}", tc.expected, got);
        }
    }
    println!("\n  {}/{} passed", passed, tests.len());
    println!("============================================================\n");
    std::process::exit(if passed == tests.len() { 0 } else { 1 });
}
