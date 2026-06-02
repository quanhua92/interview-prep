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
 * Example 2:
 *     Input: nums = [5,1,1,2,0,0]
 *     Output: [0,0,1,1,2,5]
 *
 * Constraints:
 *     - 1 <= nums.length <= 5 * 10^4
 *     - -5 * 10^4 <= nums[i] <= 5 * 10^4
 *
 * Hint: Implement merge sort — divide array in half, sort recursively, merge.
 */

use wasm_libs::*;

fn merge_sort(arr: &mut [i32], tmp: &mut [i32], l: usize, r: usize) {
    if l >= r { return; }
    let m = l + (r - l) / 2;
    merge_sort(arr, tmp, l, m);
    merge_sort(arr, tmp, m + 1, r);
    for i in l..=r { tmp[i] = arr[i]; }
    let mut i = l;
    let mut j = m + 1;
    let mut k = l;
    while i <= m && j <= r {
        if tmp[i] <= tmp[j] { arr[k] = tmp[i]; i += 1; }
        else { arr[k] = tmp[j]; j += 1; }
        k += 1;
    }
    while i <= m { arr[k] = tmp[i]; i += 1; k += 1; }
    while j <= r { arr[k] = tmp[j]; j += 1; k += 1; }
}

fn main() {
    let mut nums = read_ints();
    let n = nums.len();
    if n <= 1 { write_ints(&nums); std::process::exit(0); }
    let mut tmp = vec![0i32; n];
    merge_sort(&mut nums, &mut tmp, 0, n - 1);
    write_ints(&nums);
    std::process::exit(0);
}
