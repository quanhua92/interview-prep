/*
 * P493: Reverse Pairs [PREMIUM] (Hard)
 * https://leetcode.com/problems/reverse-pairs/
 * Topics: Array, Binary Search, Divide and Conquer, Binary Indexed Tree, Segment Tree, Merge Sort, Ordered Set
 *
 * Given an integer array nums, return the number of reverse pairs in the array.
 * A reverse pair is a pair (i, j) where:
 *
 * Example 1:
 *     Input: nums = [1,3,2,3,1]
 *     Output: 2
 *
 * Example 2:
 *     Input: nums = [2,4,3,5,1]
 *     Output: 3
 *
 * Constraints:
 *     - 1 <= nums.length <= 5 * 10^4
 *     - -2^31 <= nums[i] <= 2^31 - 1
 *
 * Hint: Use the merge-sort technique.
 */

use wasm_libs::*;

fn merge_sort(arr: &mut [i32], tmp: &mut [i32], left: usize, right: usize) -> i32 {
    todo!();
}

fn reverse_pairs(nums: &mut [i32]) -> i32 {
    todo!();
}

fn main() {
    let mut nums = read_ints();
    write_int(reverse_pairs(&mut nums));
    std::process::exit(0);
}
