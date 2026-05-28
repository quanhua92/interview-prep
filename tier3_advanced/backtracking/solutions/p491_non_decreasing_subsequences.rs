/*
 * P491: Non-decreasing Subsequences [PREMIUM] (Medium)
 * https://leetcode.com/problems/non-decreasing-subsequences/
 * Topics: Array, Hash Table, Backtracking, Bit Manipulation
 *
 * Given an integer array nums, return all the different possible non-decreasing subsequences of the given array with at least two elements.
 * Example 1:
 *     Input: nums = [4,6,7,7]
 *     Output: [[4,6],[4,6,7],[4,6,7,7],[4,7],[4,7,7],[6,7],[6,7,7],[7,7]]
 *
 * Example 2:
 *     Input: nums = [4,4,3,2,1]
 *     Output: [[4,4]]
 *
 * Template (python3):
 *     class Solution:
 *         def findSubsequences(self, nums: List[int]) -> List[List[int]]:
 */

use wasm_libs::*;
use std::collections::HashSet;

fn find_subsequences(nums: &[i32]) -> Vec<Vec<i32>> {
    let mut result: Vec<Vec<i32>> = Vec::new();
    let mut path: Vec<i32> = Vec::new();
    let n = nums.len();

    fn bt(
        nums: &[i32],
        start: usize,
        n: usize,
        path: &mut Vec<i32>,
        result: &mut Vec<Vec<i32>>,
    ) {
        if path.len() >= 2 {
            result.push(path.clone());
        }
        let mut used: HashSet<i32> = HashSet::new();
        for i in start..n {
            if used.contains(&nums[i]) {
                continue;
            }
            if path.is_empty() || nums[i] >= *path.last().unwrap() {
                used.insert(nums[i]);
                path.push(nums[i]);
                bt(nums, i + 1, n, path, result);
                path.pop();
            }
        }
    }

    bt(nums, 0, n, &mut path, &mut result);
    result.sort();
    result
}

fn main() {
    let nums = read_ints();
    let result = find_subsequences(&nums);
    for seq in result {
        write_ints(&seq);
    }
}
