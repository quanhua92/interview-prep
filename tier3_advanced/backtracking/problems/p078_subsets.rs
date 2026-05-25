/*
 * P78: Subsets (Medium)
 * https://leetcode.com/problems/subsets/
 * Topics: Array, Backtracking, Bit Manipulation
 * 
 * Given an integer array nums of unique elements, return all possible subsets (the power set).
 * The solution set must not contain duplicate subsets. Return the solution in any order.
 * 
 * Example 1:
 *     Input: nums = [1,2,3]
 *     Output: [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
 * 
 * Example 2:
 *     Input: nums = [0]
 *     Output: [[],[0]]
 * 
 * Constraints:
 *     - 1 <= nums.length <= 10
 *     - -10 <= nums[i] <= 10
 *     - All the numbers of nums are unique.
 * 
 * Template (python3):
 *     class Solution:
 *         def subsets(self, nums: List[int]) -> List[List[int]]:
 * 
 * Hint: Use backtracking to generate all possible subsets by including/excluding each element.
 */
#[allow(unused_imports)]
use rstest;

fn subsets(nums: Vec<i32>) -> Vec<Vec<i32>> {
    todo!()
}

fn main() {
    println!("\n============================================================");
    println!("  78. Subsets");
    println!("============================================================");

    let mut passed = 0;

    {
        let got = subsets(vec![1, 2, 3]);
        let exp: Vec<Vec<i32>> = vec![vec![],vec![1],vec![1,2],vec![1,2,3],vec![1,3],vec![2],vec![2,3],vec![3]];
        if got == exp { passed += 1; println!("  Test 1 (example 1): PASS"); }
        else { println!("  Test 1 (example 1): FAIL\n    Expected: {:?}\n    Got:      {:?}", exp, got); }
    }
    {
        let got = subsets(vec![0]);
        let exp: Vec<Vec<i32>> = vec![vec![], vec![0]];
        if got == exp { passed += 1; println!("  Test 2 (example 2): PASS"); }
        else { println!("  Test 2 (example 2): FAIL\n    Expected: {:?}\n    Got:      {:?}", exp, got); }
    }
    {
        let got = subsets(vec![1, 2]);
        let exp: Vec<Vec<i32>> = vec![vec![], vec![1], vec![1, 2], vec![2]];
        if got == exp { passed += 1; println!("  Test 3 (two elements): PASS"); }
        else { println!("  Test 3 (two elements): FAIL\n    Expected: {:?}\n    Got:      {:?}", exp, got); }
    }
    {
        let got = subsets(vec![-1, 0, 1]);
        let exp: Vec<Vec<i32>> = vec![vec![],vec![-1],vec![-1,0],vec![-1,0,1],vec![-1,1],vec![0],vec![0,1],vec![1]];
        if got == exp { passed += 1; println!("  Test 4 (negative numbers): PASS"); }
        else { println!("  Test 4 (negative numbers): FAIL\n    Expected: {:?}\n    Got:      {:?}", exp, got); }
    }
    {
        let got = subsets(vec![1, 2, 3, 4]);
        let exp: Vec<Vec<i32>> = vec![
            vec![],vec![1],vec![1,2],vec![1,2,3],vec![1,2,3,4],vec![1,2,4],vec![1,3],vec![1,3,4],
            vec![1,4],vec![2],vec![2,3],vec![2,3,4],vec![2,4],vec![3],vec![3,4],vec![4]
        ];
        if got == exp { passed += 1; println!("  Test 5 (four elements): PASS"); }
        else { println!("  Test 5 (four elements): FAIL\n    Expected: {:?}\n    Got:      {:?}", exp, got); }
    }
    {
        let got = subsets(vec![3, 1]);
        let exp: Vec<Vec<i32>> = vec![vec![], vec![3], vec![3, 1], vec![1]];
        if got == exp { passed += 1; println!("  Test 6 (unsorted input): PASS"); }
        else { println!("  Test 6 (unsorted input): FAIL\n    Expected: {:?}\n    Got:      {:?}", exp, got); }
    }

    println!("\n  {}/6 passed", passed);
    println!("============================================================\n");

    std::process::exit(if passed == 6 { 0 } else { 1 });
}
