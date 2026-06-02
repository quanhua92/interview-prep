/*
 * P347: Top K Frequent Elements (Medium)
 * https://leetcode.com/problems/top-k-frequent-elements/
 * Topics: Array, Hash Table, Divide and Conquer, Sorting, Heap (Priority Queue), Bucket Sort, Counting, Quickselect
 *
 * Given an integer array nums and an integer k, return the k most frequent elements. You may return the answer in any order.
 *
 * Example 1:
 *     Input: nums = [1,1,1,2,2,3], k = 2
 *     Output: [1,2]
 *
 * Example 2:
 *     Input: nums = [1], k = 1
 *     Output: [1]
 *
 * Constraints:
 *     - 1 <= nums.length <= 10^5
 *     - -10^4 <= nums[i] <= 10^4
 *     - k is in the range [1, the number of unique elements in the array].
 *     - It is guaranteed that the answer is unique.
 *
 * Follow up:
 *     - Your algorithm's time complexity must be better than O(n log n), where n is the array's size.
 *
 * Template (python3):
 *     class Solution:
 *         def topKFrequent(self, nums: List[int], k: int) -> List[int]:
 *
 * Hint: Use a frequency counter and a min-heap of size k.
 */

use wasm_libs::*;
use std::collections::HashMap;

fn top_k_frequent(nums: &[i32], k: i32) -> Vec<i32> {
    todo!();
}

fn main() {
    let nums = read_ints();
    let k = read_int();
    let result = top_k_frequent(&nums, k);
    write_ints(&result);
    std::process::exit(0);
}
