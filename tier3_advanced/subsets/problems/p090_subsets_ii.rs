/*
 * P90: Subsets II (Medium)
 * https://leetcode.com/problems/subsets-ii/
 * Topics: Array, Backtracking, Bit Manipulation
 * 
 * Given an integer array nums that may contain duplicates, return all possible subsets (the power set).
 * The solution set must not contain duplicate subsets. Return the solution in any order.
 * 
 * Example 1:
 *     Input: nums = [1,2,2]
 *     Output: [[],[1],[1,2],[1,2,2],[2],[2,2]]
 * 
 * Example 2:
 *     Input: nums = [0]
 *     Output: [[],[0]]
 * 
 * Constraints:
 *     - 1 <= nums.length <= 10
 *     - -10 <= nums[i] <= 10
 * 
 * Template (python3):
 *     class Solution:
 *         def subsetsWithDup(self, nums: List[int]) -> List[List[int]]:
 * 
 * Hint: Sort first, then skip duplicates at the same recursion level during backtracking.
 */
#[allow(unused_imports)]
use rstest;

fn subsets_with_dup(mut nums: Vec<i32>) -> Vec<Vec<i32>> {
    todo!()
}

fn main() {
    println!("\n============================================================");
    println!("  90. Subsets II");
    println!("============================================================");

    let mut passed = 0;

    {
        let got = subsets_with_dup(vec![1, 2, 2]);
        let exp: Vec<Vec<i32>> = vec![vec![], vec![1], vec![1,2], vec![1,2,2], vec![2], vec![2,2]];
        if got == exp { passed += 1; println!("  Test 1 (example 1): PASS"); }
        else { println!("  Test 1 (example 1): FAIL\n    Expected: {:?}\n    Got:      {:?}", exp, got); }
    }
    {
        let got = subsets_with_dup(vec![0]);
        let exp: Vec<Vec<i32>> = vec![vec![], vec![0]];
        if got == exp { passed += 1; println!("  Test 2 (example 2): PASS"); }
        else { println!("  Test 2 (example 2): FAIL\n    Expected: {:?}\n    Got:      {:?}", exp, got); }
    }
    {
        let got = subsets_with_dup(vec![2, 2, 2]);
        let exp: Vec<Vec<i32>> = vec![vec![], vec![2], vec![2,2], vec![2,2,2]];
        if got == exp { passed += 1; println!("  Test 3 (all duplicates): PASS"); }
        else { println!("  Test 3 (all duplicates): FAIL\n    Expected: {:?}\n    Got:      {:?}", exp, got); }
    }
    {
        let got = subsets_with_dup(vec![1, 1, 2, 2]);
        let exp: Vec<Vec<i32>> = vec![vec![], vec![1], vec![1,1], vec![1,1,2], vec![1,1,2,2], vec![1,2], vec![1,2,2], vec![2], vec![2,2]];
        if got == exp { passed += 1; println!("  Test 4 (multiple duplicates): PASS"); }
        else { println!("  Test 4 (multiple duplicates): FAIL\n    Expected: {:?}\n    Got:      {:?}", exp, got); }
    }
    {
        let got = subsets_with_dup(vec![-1, -1, 0]);
        let exp: Vec<Vec<i32>> = vec![vec![], vec![-1], vec![-1,-1], vec![-1,-1,0], vec![-1,0], vec![0]];
        if got == exp { passed += 1; println!("  Test 5 (negative duplicates): PASS"); }
        else { println!("  Test 5 (negative duplicates): FAIL\n    Expected: {:?}\n    Got:      {:?}", exp, got); }
    }
    {
        let got = subsets_with_dup(vec![1, 1, 1, 1]);
        let exp: Vec<Vec<i32>> = vec![vec![], vec![1], vec![1,1], vec![1,1,1], vec![1,1,1,1]];
        if got == exp { passed += 1; println!("  Test 6 (all same element): PASS"); }
        else { println!("  Test 6 (all same element): FAIL\n    Expected: {:?}\n    Got:      {:?}", exp, got); }
    }

    println!("\n  {}/6 passed", passed);
    println!("============================================================\n");

    std::process::exit(if passed == 6 { 0 } else { 1 });
}
