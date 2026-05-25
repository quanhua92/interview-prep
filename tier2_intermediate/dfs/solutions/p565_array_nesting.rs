/*
 * P565: Array Nesting [PREMIUM] (Medium)
 * https://leetcode.com/problems/array-nesting/
 * Topics: Array, Depth-First Search
 *
 * You are given an integer array nums of length n where nums is a permutation of the numbers in the range [0, n - 1].
 * You should build a set s[k] = {nums[k], nums[nums[k]], nums[nums[nums[k]]], ... } subjected to the following rule:
 * Return the longest length of a set s[k].
 * Example 1:
 *     Input: nums = [5,4,0,3,1,6,2]
 *     Output: 4
 *     Explanation:
 *     nums[0] = 5, nums[1] = 4, nums[2] = 0, nums[3] = 3, nums[4] = 1, nums[5] = 6, nums[6] = 2.
 *     One of the longest sets s[k]:
 *     s[0] = {nums[0], nums[5], nums[6], nums[2]} = {5, 6, 2, 0}
 *
 * Example 2:
 *     Input: nums = [0,1,2]
 *     Output: 1
 *
 * Constraints:
 *     - 1 <= nums.length <= 105
 *     - 0 <= nums[i] < nums.length
 *     - All the values of nums are unique.
 *
 * Template (python3):
 *     class Solution:
 *         def arrayNesting(self, nums: List[int]) -> int:
 */


#[allow(unused_imports)]
use rstest;

fn array_nesting(nums: &[i32]) -> i32 {
    let mut visited = vec![false; nums.len()];
    let mut max_len = 0;
    for i in 0..nums.len() {
        if !visited[i] {
            let mut count = 0;
            let mut j = i;
            while !visited[j] {
                visited[j] = true;
                j = nums[j] as usize;
                count += 1;
            }
            max_len = max_len.max(count);
        }
    }
    max_len
}

fn main() {
    struct TestCase {
        label: &'static str,
        input: &'static [i32],
        expected: i32,
    }

    let tests: &[TestCase] = &[
        TestCase { label: "example 1", input: &[5, 4, 0, 3, 1, 6, 2], expected: 4 },
        TestCase { label: "example 2", input: &[0, 1, 2], expected: 1 },
        TestCase { label: "single element", input: &[0], expected: 1 },
        TestCase { label: "two element cycle", input: &[1, 0], expected: 2 },
        TestCase { label: "full single cycle", input: &[2, 0, 1], expected: 3 },
        TestCase { label: "two separate cycles", input: &[0, 2, 1], expected: 2 },
    ];

    println!("\n============================================================");
    println!("  565. Array Nesting");
    println!("============================================================");

    let mut passed = 0;
    for (i, tc) in tests.iter().enumerate() {
        let got = array_nesting(tc.input);
        if got == tc.expected {
            passed += 1;
            println!("  Test {} ({}): PASS", i + 1, tc.label);
        } else {
            println!("  Test {} ({}): FAIL", i + 1, tc.label);
            println!("    Expected: {}", tc.expected);
            println!("    Got:      {}", got);
        }
    }

    println!("\n  {}/{} passed", passed, tests.len());
    println!("============================================================\n");

    std::process::exit(if passed == tests.len() { 0 } else { 1 });
}
