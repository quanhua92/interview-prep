/*
 * P46: Permutations (Medium)
 * https://leetcode.com/problems/permutations/
 * Topics: Array, Backtracking
 *
 * Given an array nums of distinct integers, return all the possible permutations. You can return the answer in any order.
 *
 * Example 1:
 *     Input: nums = [1,2,3]
 *     Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
 *
 * Example 2:
 *     Input: nums = [0,1]
 *     Output: [[0,1],[1,0]]
 *
 * Example 3:
 *     Input: nums = [1]
 *     Output: [[1]]
 *
 * Constraints:
 *     - 1 <= nums.length <= 6
 *     - -10 <= nums[i] <= 10
 *     - All the integers of nums are unique.
 *
 * Template (python3):
 *     class Solution:
 *         def permute(self, nums: List[int]) -> List[List[int]]:
 *
 * Hint: Use backtracking with swapping to generate all permutations in-place.
 */


#[allow(unused_imports)]
use rstest;

fn permute(nums: Vec<i32>) -> Vec<Vec<i32>> {
    let mut nums = nums;
    let mut res: Vec<Vec<i32>> = Vec::new();
    fn backtrack(nums: &mut Vec<i32>, first: usize, res: &mut Vec<Vec<i32>>) {
        if first == nums.len() {
            res.push(nums.clone());
            return;
        }
        for i in first..nums.len() {
            nums.swap(first, i);
            backtrack(nums, first + 1, res);
            nums.swap(first, i);
        }
    }
    backtrack(&mut nums, 0, &mut res);
    res.sort();
    res
}

fn main() {
    println!("\n============================================================");
    println!("  46. Permutations");
    println!("============================================================");

    let mut passed = 0;

    {
        let got = permute(vec![1, 2, 3]);
        let exp: Vec<Vec<i32>> = vec![vec![1,2,3],vec![1,3,2],vec![2,1,3],vec![2,3,1],vec![3,1,2],vec![3,2,1]];
        if got == exp { passed += 1; println!("  Test 1 (example 1): PASS"); }
        else { println!("  Test 1 (example 1): FAIL\n    Expected: {:?}\n    Got:      {:?}", exp, got); }
    }
    {
        let got = permute(vec![0, 1]);
        let exp: Vec<Vec<i32>> = vec![vec![0,1],vec![1,0]];
        if got == exp { passed += 1; println!("  Test 2 (example 2): PASS"); }
        else { println!("  Test 2 (example 2): FAIL\n    Expected: {:?}\n    Got:      {:?}", exp, got); }
    }
    {
        let got = permute(vec![1]);
        let exp: Vec<Vec<i32>> = vec![vec![1]];
        if got == exp { passed += 1; println!("  Test 3 (single element): PASS"); }
        else { println!("  Test 3 (single element): FAIL\n    Expected: {:?}\n    Got:      {:?}", exp, got); }
    }
    {
        let got = permute(vec![-1, 0, 1]);
        let exp: Vec<Vec<i32>> = vec![vec![-1,0,1],vec![-1,1,0],vec![0,-1,1],vec![0,1,-1],vec![1,-1,0],vec![1,0,-1]];
        if got == exp { passed += 1; println!("  Test 4 (negative and zero mix): PASS"); }
        else { println!("  Test 4 (negative and zero mix): FAIL\n    Expected: {:?}\n    Got:      {:?}", exp, got); }
    }
    {
        let got = permute(vec![-3, -1]);
        let exp: Vec<Vec<i32>> = vec![vec![-3,-1],vec![-1,-3]];
        if got == exp { passed += 1; println!("  Test 5 (two negative elements): PASS"); }
        else { println!("  Test 5 (two negative elements): FAIL\n    Expected: {:?}\n    Got:      {:?}", exp, got); }
    }
    {
        let got = permute(vec![1, 2, 3, 4]);
        let exp: Vec<Vec<i32>> = vec![
            vec![1,2,3,4],vec![1,2,4,3],vec![1,3,2,4],vec![1,3,4,2],vec![1,4,2,3],vec![1,4,3,2],
            vec![2,1,3,4],vec![2,1,4,3],vec![2,3,1,4],vec![2,3,4,1],vec![2,4,1,3],vec![2,4,3,1],
            vec![3,1,2,4],vec![3,1,4,2],vec![3,2,1,4],vec![3,2,4,1],vec![3,4,1,2],vec![3,4,2,1],
            vec![4,1,2,3],vec![4,1,3,2],vec![4,2,1,3],vec![4,2,3,1],vec![4,3,1,2],vec![4,3,2,1],
        ];
        if got == exp { passed += 1; println!("  Test 6 (four elements): PASS"); }
        else { println!("  Test 6 (four elements): FAIL\n    Expected: {:?}\n    Got:      {:?}", exp, got); }
    }
    {
        let got = permute(vec![-5]);
        let exp: Vec<Vec<i32>> = vec![vec![-5]];
        if got == exp { passed += 1; println!("  Test 7 (single negative element): PASS"); }
        else { println!("  Test 7 (single negative element): FAIL\n    Expected: {:?}\n    Got:      {:?}", exp, got); }
    }

    println!("\n  {}/7 passed", passed);
    println!("============================================================\n");

    std::process::exit(if passed == 7 { 0 } else { 1 });
}
