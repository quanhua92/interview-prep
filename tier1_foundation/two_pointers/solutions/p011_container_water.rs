/*
 * P11: Container With Most Water (Medium)
 * https://leetcode.com/problems/container-with-most-water/
 * Topics: Array, Two Pointers, Greedy
 *
 * You are given an integer array height of length n. There are n vertical lines drawn such that the two endpoints of the ith line are (i, 0) and (i, height[i]).
 * Find two lines that together with the x-axis form a container, such that the container contains the most water.
 * Return the maximum amount of water a container can store.
 * Notice that you may not slant the container.
 *
 * Example 1:
 *     Input: height = [1,8,6,2,5,4,8,3,7]
 *     Output: 49
 *     Explanation: The above vertical lines are represented by array [1,8,6,2,5,4,8,3,7]. In this case, the max area of water (blue section) the container can contain is 49.
 *
 * Example 2:
 *     Input: height = [1,1]
 *     Output: 1
 *
 * Constraints:
 *     - n == height.length
 *     - 2 <= n <= 105
 *     - 0 <= height[i] <= 104
 *
 * Hints:
 *     - If you simulate the problem, it will be O(n^2) which is not efficient.
 *     - Try to use two-pointers. Set one pointer to the left and one to the right of the array. Always move the pointer that points to the lower line.
 *     - How can you calculate the amount of water at each step?
 *
 * Template (python3):
 *     class Solution:
 *         def maxArea(self, height: List[int]) -> int:
 *
 * Hint: Start with pointers at both ends and move the shorter one inward.
 */


fn max_area(height: &[i32]) -> i32 {
    let (mut left, mut right) = (0, height.len() - 1);
    let mut max_a = 0;
    while left < right {
        let h = if height[left] < height[right] { height[left] } else { height[right] };
        let area = h * (right - left) as i32;
        if area > max_a { max_a = area; }
        if height[left] < height[right] {
            left += 1;
        } else {
            right -= 1;
        }
    }
    max_a
}

fn main() {
    struct Case<'a> { label: &'a str, input: &'a [i32], expected: i32 }
    let tests: &[Case] = &[
        Case { label: "example 1", input: &[1, 8, 6, 2, 5, 4, 8, 3, 7], expected: 49 },
        Case { label: "example 2", input: &[1, 1], expected: 1 },
        Case { label: "symmetric", input: &[4, 3, 2, 1, 4], expected: 16 },
        Case { label: "all zeros", input: &[0, 0, 0, 0], expected: 0 },
        Case { label: "strictly increasing", input: &[1, 2, 3, 4, 5], expected: 6 },
        Case { label: "strictly decreasing", input: &[5, 4, 3, 2, 1], expected: 6 },
        Case { label: "max height two elements", input: &[10000, 10000], expected: 10000 },
        Case { label: "all same height", input: &[2, 2, 2, 2, 2], expected: 8 },
    ];

    println!("\n============================================================");
    println!("  11. Container With Most Water");
    println!("============================================================");
    let mut passed = 0;
    for (i, tc) in tests.iter().enumerate() {
        let got = max_area(tc.input);
        if got == tc.expected {
            passed += 1;
            println!("  Test {} ({}): PASS", i + 1, tc.label);
        } else {
            println!("  Test {} ({}): FAIL", i + 1, tc.label);
            println!("    Expected: {}\n    Got:      {}", tc.expected, got);
        }
    }
    println!("\n  {}/{} passed", passed, tests.len());
    println!("============================================================\n");
    std::process::exit(if passed == tests.len() { 0 } else { 1 });
}
