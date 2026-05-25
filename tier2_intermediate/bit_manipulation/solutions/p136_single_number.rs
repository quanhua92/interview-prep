/*
 * P136: Single Number (Easy)
 * https://leetcode.com/problems/single-number/
 * Topics: Array, Bit Manipulation
 *
 * Given a non-empty array of integers nums, every element appears twice except for one. Find that single one.
 * You must implement a solution with a linear runtime complexity and use only constant extra space.
 *
 * Example 1:
 *     Input: nums = [2,2,1]
 *     Output: 1
 *
 * Example 2:
 *     Input: nums = [4,1,2,1,2]
 *     Output: 4
 *
 * Example 3:
 *     Input: nums = [1]
 *     Output: 1
 *
 * Constraints:
 *     - 1 <= nums.length <= 3 * 104
 *     - -3 * 104 <= nums[i] <= 3 * 104
 *     - Each element in the array appears twice except for one element which appears only once.
 *
 * Hints:
 *     - Think about the XOR (^) operator's property.
 *
 * Template (python3):
 *     class Solution:
 *         def singleNumber(self, nums: List[int]) -> int:
 *
 * Hint: XOR all numbers — pairs cancel out, leaving the single number.
 */

#[allow(unused_imports)]
use rstest;

fn single_number(nums: &[i32]) -> i32 {
    let mut result = 0;
    for &num in nums {
        result ^= num;
    }
    result
}

fn main() {
    struct TestCase {
        label: &'static str,
        input: &'static [i32],
        expected: i32,
    }

    let tests: &[TestCase] = &[
        TestCase { label: "example 1", input: &[2, 2, 1], expected: 1 },
        TestCase { label: "example 2", input: &[4, 1, 2, 1, 2], expected: 4 },
        TestCase { label: "single element", input: &[1], expected: 1 },
        TestCase { label: "negative numbers", input: &[-1, -1, -2], expected: -2 },
        TestCase { label: "zero pairs", input: &[0, 0, 1], expected: 1 },
        TestCase { label: "single negative", input: &[-1], expected: -1 },
        TestCase { label: "many pairs", input: &[7, 7, 7, 7, 99, 3, 3, 4, 4], expected: 99 },
    ];

    println!("\n============================================================");
    println!("  136. Single Number");
    println!("============================================================");

    let mut passed = 0;
    for (i, tc) in tests.iter().enumerate() {
        let got = single_number(tc.input);
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
