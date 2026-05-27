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
 * Hint: Use divide & conquer: merge pairs of lists recursively until one remains.
 */

use wasm_libs::*;

fn merge_k_lists(lists: &[Vec<i32>]) -> Vec<i32> {
    todo!()
}

fn main() {
    let k = read_int() as usize;
    let mut lists: Vec<Vec<i32>> = Vec::with_capacity(k);
    for _ in 0..k {
        lists.push(read_ints());
    }
    let result = merge_k_lists(&lists);
    write_ints(&result);
    std::process::exit(0);
}
