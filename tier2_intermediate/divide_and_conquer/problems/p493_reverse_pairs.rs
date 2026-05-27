/*
 * P493: Reverse Pairs [PREMIUM] (Hard)
 * https://leetcode.com/problems/reverse-pairs/
 * Topics: Array, Binary Search, Divide and Conquer, Binary Indexed Tree, Segment Tree, Merge Sort, Ordered Set
 *
 * Given an integer array nums, return the number of reverse pairs in the array.
 *
 * Example 1:
 *     Input: nums = [1,3,2,3,1]
 *     Output: 2
 *
 * Hint: Use the merge-sort technique.
 */

use wasm_libs::*;

fn reverse_pairs(nums: &mut [i32]) -> i32 {
    todo!()
}

fn main() {
    let mut nums = read_ints();
    write_int(reverse_pairs(&mut nums));
    std::process::exit(0);
}
