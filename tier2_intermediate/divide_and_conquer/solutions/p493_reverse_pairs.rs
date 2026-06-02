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
    if right - left <= 1 { return 0; }
    let mid = left + (right - left) / 2;
    let mut count = merge_sort(arr, tmp, left, mid) + merge_sort(arr, tmp, mid, right);
    let mut j = mid;
    for i in left..mid {
        while j < right && (arr[i] as i64) > 2 * (arr[j] as i64) {
            j += 1;
        }
        count += (j - mid) as i32;
    }
    let mut p = left;
    let mut q = mid;
    let mut k = left;
    while p < mid && q < right {
        if arr[p] <= arr[q] {
            tmp[k] = arr[p]; p += 1;
        } else {
            tmp[k] = arr[q]; q += 1;
        }
        k += 1;
    }
    while p < mid { tmp[k] = arr[p]; p += 1; k += 1; }
    while q < right { tmp[k] = arr[q]; q += 1; k += 1; }
    for i in left..right { arr[i] = tmp[i]; }
    count
}

fn reverse_pairs(nums: &mut [i32]) -> i32 {
    if nums.len() <= 1 { return 0; }
    let mut tmp = vec![0; nums.len()];
    merge_sort(nums, &mut tmp, 0, nums.len())
}

fn main() {
    let mut nums = read_ints();
    write_int(reverse_pairs(&mut nums));
    std::process::exit(0);
}
