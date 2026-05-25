/*
 * P238: Product of Array Except Self (Medium)
 * https://leetcode.com/problems/product-of-array-except-self/
 * Topics: Array, Prefix Sum
 *
 * Given an integer array nums, return an array answer such that answer[i] is equal to the product of all the elements of nums except nums[i].
 * The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit integer.
 * You must write an algorithm that runs in O(n) time and without using the division operation.
 *
 * Example 1:
 *     Input: nums = [1,2,3,4]
 *     Output: [24,12,8,6]
 *
 * Example 2:
 *     Input: nums = [-1,1,0,-3,3]
 *     Output: [0,0,9,0,0]
 *
 * Constraints:
 *     - 2 <= nums.length <= 105
 *     - -30 <= nums[i] <= 30
 *     - The input is generated such that answer[i] is guaranteed to fit in a 32-bit integer.
 *
 * Follow up:
 *     - Can you solve the problem in O(1) extra space complexity? (The output array does not count as extra space for space complexity analysis.)
 *
 * Hints:
 *     - Think how you can efficiently utilize prefix and suffix products to calculate the product of all elements except self for each index. Can you pre-compute the prefix and suffix products in linear time to avoid redundant calculations?
 *     - Can you minimize additional space usage by reusing memory or modifying the input array to store intermediate results?
 *
 * Template (python3):
 *     class Solution:
 *         def productExceptSelf(self, nums: List[int]) -> List[int]:
 *
 * Hint: Build left and right product arrays, then combine.
 */

use rstest::TestCase;
use rstest::run_tests;

fn product_except_self(nums: &[i32], _target: i32) -> Vec<i32> {
    let n = nums.len();
    let mut output = vec![1i64; n];

    let mut left: i64 = 1;
    for i in 0..n {
        output[i] = left;
        left *= nums[i] as i64;
    }

    let mut right: i64 = 1;
    for i in (0..n).rev() {
        output[i] *= right;
        right *= nums[i] as i64;
    }

    output.iter().map(|&x| x as i32).collect()
}

fn main() {
    let tests: &[TestCase] = &[
        TestCase { label: "example 1", input_arr: &[1, 2, 3, 4], target: 0, expected: &[24, 12, 8, 6] },
        TestCase { label: "example 2", input_arr: &[-1, 1, 0, -3, 3], target: 0, expected: &[0, 0, 9, 0, 0] },
        TestCase { label: "two elements", input_arr: &[1, 2], target: 0, expected: &[2, 1] },
        TestCase { label: "all ones", input_arr: &[1, 1, 1], target: 0, expected: &[1, 1, 1] },
        TestCase { label: "all negatives", input_arr: &[-1, -1, -1], target: 0, expected: &[1, 1, 1] },
        TestCase { label: "two elements negative", input_arr: &[1, -1], target: 0, expected: &[-1, 1] },
        TestCase { label: "all zeros", input_arr: &[0, 0, 0, 0], target: 0, expected: &[0, 0, 0, 0] },
    ];
    std::process::exit(run_tests!("238. Product of Array Except Self", product_except_self, tests));
}
