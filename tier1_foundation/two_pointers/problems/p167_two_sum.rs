/*
 * P167: Two Sum II - Input Array Is Sorted (Medium)
 * https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/
 * Topics: Array, Two Pointers, Binary Search
 * 
 * Given a 1-indexed array of integers numbers that is already sorted in non-decreasing order, find two numbers such that they add up to a specific target number. Let these two numbers be numbers[index1] and numbers[index2] where 1 <= index1 < index2 <= numbers.length.
 * Return the indices of the two numbers, index1 and index2, added by one as an integer array [index1, index2] of length 2.
 * The tests are generated such that there is exactly one solution. You may not use the same element twice.
 * Your solution must use only constant extra space.
 * 
 * Example 1:
 *     Input: numbers = [2,7,11,15], target = 9
 *     Output: [1,2]
 *     Explanation: The sum of 2 and 7 is 9. Therefore, index1 = 1, index2 = 2. We return [1, 2].
 * 
 * Example 2:
 *     Input: numbers = [2,3,4], target = 6
 *     Output: [1,3]
 *     Explanation: The sum of 2 and 4 is 6. Therefore index1 = 1, index2 = 3. We return [1, 3].
 * 
 * Example 3:
 *     Input: numbers = [-1,0], target = -1
 *     Output: [1,2]
 *     Explanation: The sum of -1 and 0 is -1. Therefore index1 = 1, index2 = 2. We return [1, 2].
 * 
 * Constraints:
 *     - 2 <= numbers.length <= 3 * 104
 *     - -1000 <= numbers[i] <= 1000
 *     - numbers is sorted in non-decreasing order.
 *     - -1000 <= target <= 1000
 *     - The tests are generated such that there is exactly one solution.
 * 
 * Template (python3):
 *     class Solution:
 *         def twoSum(self, numbers: List[int], target: int) -> List[int]:
 * 
 * Hint: Use two pointers from both ends of the sorted array.
 */
use rstest::{run_tests, TestCase};

fn two_sum(numbers: &[i32], target: i32) -> Vec<i32> {
    todo!()
}

fn main() {
    let tests: &[TestCase] = &[
        TestCase { label: "example 1", input_arr: &[2, 7, 11, 15], target: 9, expected: &[1, 2] },
        TestCase { label: "example 2", input_arr: &[2, 3, 4], target: 6, expected: &[1, 3] },
        TestCase { label: "example 3", input_arr: &[-1, 0], target: -1, expected: &[1, 2] },
        TestCase { label: "all negatives", input_arr: &[-10, -6, -4, -2], target: -10, expected: &[2, 3] },
        TestCase { label: "exactly two elements", input_arr: &[1, 2], target: 3, expected: &[1, 2] },
        TestCase { label: "negative positive cross", input_arr: &[-5, -3, 0, 2, 4, 6], target: 1, expected: &[1, 6] },
        TestCase { label: "middle elements", input_arr: &[1, 3, 4, 5, 7, 10, 11], target: 9, expected: &[3, 4] },
    ];
    std::process::exit(run_tests!("167. Two Sum II - Input Array Is Sorted", two_sum, tests));
}
