/*
 * P912: Sort an Array (Medium)
 * https://leetcode.com/problems/sort-an-array/
 * Topics: Array, Divide and Conquer, Sorting, Heap (Priority Queue), Merge Sort, Bucket Sort, Radix Sort, Counting Sort
 *
 * Given an array of integers nums, sort the array in ascending order and return it.
 * You must solve the problem without using any built-in functions in O(nlog(n)) time complexity and with the smallest space complexity possible.
 *
 * Example 1:
 *     Input: nums = [5,2,3,1]
 *     Output: [1,2,3,5]
 *
 * Hint: Implement merge sort — divide array in half, sort recursively, merge.
 */

use wasm_libs::*;

fn sort_array(nums: &mut [i32]) -> Vec<i32> {
    todo!()
}

fn main() {
    let mut nums = read_ints();
    let result = sort_array(&mut nums);
    write_ints(&result);
    std::process::exit(0);
}
