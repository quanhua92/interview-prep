/*
 * P491: Non-decreasing Subsequences [PREMIUM] (Medium)
 * https://leetcode.com/problems/non-decreasing-subsequences/
 * Topics: Array, Hash Table, Backtracking, Bit Manipulation
 * 
 * Given an integer array nums, return all the different possible non-decreasing subsequences of the given array with at least two elements. You may return the answer in any order.
 * Example 1:
 *     Input: nums = [4,6,7,7]
 *     Output: [[4,6],[4,6,7],[4,6,7,7],[4,7],[4,7,7],[6,7],[6,7,7],[7,7]]
 * 
 * Example 2:
 *     Input: nums = [4,4,3,2,1]
 *     Output: [[4,4]]
 * 
 * Constraints:
 *     - 1 <= nums.length <= 15
 *     - -100 <= nums[i] <= 100
 * 
 * Template (python3):
 *     class Solution:
 *         def findSubsequences(self, nums: List[int]) -> List[List[int]]:
 */
#[allow(unused_imports)]
use rstest;
use std::collections::HashSet;

fn find_subsequences(nums: &[i32]) -> Vec<Vec<i32>> {
    todo!()
}

fn main() {
    println!("\n============================================================");
    println!("  491. Non-decreasing Subsequences");
    println!("============================================================");

    let mut passed = 0;

    {
        let got = find_subsequences(&[4, 6, 7, 7]);
        let exp: Vec<Vec<i32>> = vec![vec![4,6],vec![4,6,7],vec![4,6,7,7],vec![4,7],vec![4,7,7],vec![6,7],vec![6,7,7],vec![7,7]];
        if got == exp { passed += 1; println!("  Test 1 (example 1): PASS"); }
        else { println!("  Test 1 (example 1): FAIL\n    Expected: {:?}\n    Got:      {:?}", exp, got); }
    }
    {
        let got = find_subsequences(&[4, 4, 3, 2, 1]);
        let exp: Vec<Vec<i32>> = vec![vec![4, 4]];
        if got == exp { passed += 1; println!("  Test 2 (example 2): PASS"); }
        else { println!("  Test 2 (example 2): FAIL\n    Expected: {:?}\n    Got:      {:?}", exp, got); }
    }
    {
        let got = find_subsequences(&[2, 2, 2]);
        let exp: Vec<Vec<i32>> = vec![vec![2, 2], vec![2, 2, 2]];
        if got == exp { passed += 1; println!("  Test 3 (all same elements): PASS"); }
        else { println!("  Test 3 (all same elements): FAIL\n    Expected: {:?}\n    Got:      {:?}", exp, got); }
    }
    {
        let got = find_subsequences(&[5, 4, 3, 2, 1]);
        if got.is_empty() { passed += 1; println!("  Test 4 (strictly decreasing): PASS"); }
        else { println!("  Test 4 (strictly decreasing): FAIL"); }
    }
    {
        let got = find_subsequences(&[1, 2, 3]);
        let exp: Vec<Vec<i32>> = vec![vec![1, 2], vec![1, 2, 3], vec![1, 3], vec![2, 3]];
        if got == exp { passed += 1; println!("  Test 5 (strictly increasing): PASS"); }
        else { println!("  Test 5 (strictly increasing): FAIL\n    Expected: {:?}\n    Got:      {:?}", exp, got); }
    }
    {
        let got = find_subsequences(&[1]);
        if got.is_empty() { passed += 1; println!("  Test 6 (single element): PASS"); }
        else { println!("  Test 6 (single element): FAIL"); }
    }

    println!("\n  {}/6 passed", passed);
    println!("============================================================\n");

    std::process::exit(if passed == 6 { 0 } else { 1 });
}
