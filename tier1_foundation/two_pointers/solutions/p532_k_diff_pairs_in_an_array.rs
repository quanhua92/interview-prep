/*
 * P532: K-diff Pairs in an Array [PREMIUM] (Medium)
 * https://leetcode.com/problems/k-diff-pairs-in-an-array/
 * Topics: Array, Hash Table, Two Pointers, Binary Search, Sorting
 *
 * Given an array of integers nums and an integer k, return the number of unique k-diff pairs in the array.
 * A k-diff pair is an integer pair (nums[i], nums[j]), where the following are true:
 *
 *   0 <= i, j < nums.length
 *   i != j
 *   |nums[i] - nums[j]| == k
 *   
 * Notice that |val| denotes the absolute value of val.
 * 
 * Example 1:
 *     Input: nums = [3,1,4,1,5], k = 2
 *     Output: 2
 *     Explanation: There are two 2-diff pairs in the array, (1, 3) and (3, 5).
 *     Although we have two 1s in the input, we should only return the number of unique pairs.
 *
 * Example 2:
 *     Input: nums = [1,2,3,4,5], k = 1
 *     Output: 4
 *     Explanation: There are four 1-diff pairs in the array, (1, 2), (2, 3), (3, 4) and (4, 5).
 *
 * Example 3:
 *     Input: nums = [1,3,1,5,4], k = 0
 *     Output: 1
 *     Explanation: There is one 0-diff pair in the array, (1, 1).
 *
 * Constraints:
 *     - 1 <= nums.length <= 10^4
 *     - -10^7 <= nums[i] <= 10^7
 *     - 0 <= k <= 10^7
 *
 * Template (python3):
 *     class Solution:
 *         def findPairs(self, nums: List[int], k: int) -> int:
 */

use wasm_libs::*;

impl Solution {
    fn find_pairs(nums: &[i32], k: i32) -> i32 {
        if k < 0 { return 0; }
        let mut arr: Vec<i32> = nums.to_vec();
        arr.sort();
        let n = arr.len();
        let mut count = 0;
        let mut left: usize = 0;
        let mut right: usize = 1;
        while right < n {
            let diff = arr[right] - arr[left];
            if diff < k {
                right += 1;
            } else if diff > k {
                left += 1;
            } else {
                count += 1;
                let lv = arr[left];
                let rv = arr[right];
                while left < n && arr[left] == lv { left += 1; }
                while right < n && arr[right] == rv { right += 1; }
            }
            if left == right { right += 1; }
        }
        count
    }
}

struct Solution;

fn main() {
    let nums = read_ints();
    let k = read_int();
    write_int(Solution::find_pairs(&nums, k));
    std::process::exit(0);
}
