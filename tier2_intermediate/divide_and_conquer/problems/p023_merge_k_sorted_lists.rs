/*
 * P23: Merge k Sorted Lists (Hard)
 * https://leetcode.com/problems/merge-k-sorted-lists/
 * Topics: Linked List, Divide and Conquer, Heap (Priority Queue), Merge Sort
 *
 * You are given an array of k linked-lists lists, each linked-list is sorted in ascending order.
 * Merge all the linked-lists into one sorted linked-list and return it.
 *
 * Example 1:
 *     Input: lists = [[1,4,5],[1,3,4],[2,6]]
 *     Output: [1,1,2,3,4,4,5,6]
 *
 * Constraints:
 *     - k == lists.length
 *     - 0 <= k <= 10^4
 *     - 0 <= lists[i].length <= 500
 *
 * Hint: Use divide & conquer: merge pairs of lists recursively until one remains.
 */

use wasm_libs::*;

fn merge_sorted(a: &[i32], b: &[i32]) -> Vec<i32> {
    todo!();
}

fn divide_merge(lists: &[Vec<i32>], left: usize, right: usize) -> Vec<i32> {
    todo!();
}

fn main() {
    let k = read_int() as usize;
    let mut lists: Vec<Vec<i32>> = Vec::with_capacity(k);
    for _ in 0..k {
        lists.push(read_ints());
    }
    let result = if lists.is_empty() {
        vec![]
    } else {
        divide_merge(&lists, 0, lists.len() - 1)
    };
    write_ints(&result);
    std::process::exit(0);
}
