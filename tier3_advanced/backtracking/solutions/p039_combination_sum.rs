/*
 * P39: Combination Sum (Medium)
 * https://leetcode.com/problems/combination-sum/
 * Topics: Array, Backtracking
 *
 * Given an array of distinct integers candidates and a target integer target, return a list of all unique combinations of candidates where the chosen numbers sum to target. You may return the combinations in any order.
 * The same number may be chosen from candidates an unlimited number of times. Two combinations are unique if the frequency of at least one of the chosen numbers is different.
 * The test cases are generated such that the number of unique combinations that sum up to target is less than 150 combinations for the given input.
 *
 * Example 1:
 *     Input: candidates = [2,3,6,7], target = 7
 *     Output: [[2,2,3],[7]]
 *     Explanation:
 *     2 and 3 are candidates, and 2 + 2 + 3 = 7. Note that 2 can be used multiple times.
 *     7 is a candidate, and 7 = 7.
 *     These are the only two combinations.
 *
 * Example 2:
 *     Input: candidates = [2,3,5], target = 8
 *     Output: [[2,2,2,2],[2,3,3],[3,5]]
 *
 * Example 3:
 *     Input: candidates = [2], target = 1
 *     Output: []
 *
 * Constraints:
 *     - 1 <= candidates.length <= 30
 *     - 2 <= candidates[i] <= 40
 *     - All elements of candidates are distinct.
 *     - 1 <= target <= 40
 *
 * Template (python3):
 *     class Solution:
 *         def combinationSum(self, candidates: List[int], target: int) -> List[List[int]]:
 *
 * Hint: Use backtracking with early pruning when the remaining sum goes negative.
 */


#[allow(unused_imports)]
use rstest;

fn combination_sum(mut candidates: Vec<i32>, target: i32) -> Vec<Vec<i32>> {
    candidates.sort();
    let mut result: Vec<Vec<i32>> = Vec::new();
    let mut path: Vec<i32> = Vec::new();

    fn bt(
        cands: &[i32],
        start: usize,
        rem: i32,
        path: &mut Vec<i32>,
        result: &mut Vec<Vec<i32>>,
    ) {
        if rem == 0 {
            result.push(path.clone());
            return;
        }
        for i in start..cands.len() {
            if cands[i] > rem {
                break;
            }
            path.push(cands[i]);
            bt(cands, i, rem - cands[i], path, result);
            path.pop();
        }
    }

    bt(&candidates, 0, target, &mut path, &mut result);
    result
}

fn main() {
    println!("\n============================================================");
    println!("  39. Combination Sum");
    println!("============================================================");

    let mut passed = 0;

    {
        let got = combination_sum(vec![2, 3, 6, 7], 7);
        let exp = vec![vec![2, 2, 3], vec![7]];
        if got == exp { passed += 1; println!("  Test 1 (example 1): PASS"); }
        else { println!("  Test 1 (example 1): FAIL\n    Expected: {:?}\n    Got:      {:?}", exp, got); }
    }
    {
        let got = combination_sum(vec![2, 3, 5], 8);
        let exp = vec![vec![2, 2, 2, 2], vec![2, 3, 3], vec![3, 5]];
        if got == exp { passed += 1; println!("  Test 2 (example 2): PASS"); }
        else { println!("  Test 2 (example 2): FAIL\n    Expected: {:?}\n    Got:      {:?}", exp, got); }
    }
    {
        let got = combination_sum(vec![2], 1);
        if got.is_empty() { passed += 1; println!("  Test 3 (no solution): PASS"); }
        else { println!("  Test 3 (no solution): FAIL"); }
    }
    {
        let got = combination_sum(vec![5], 5);
        let exp = vec![vec![5]];
        if got == exp { passed += 1; println!("  Test 4 (single candidate equals target): PASS"); }
        else { println!("  Test 4 (single candidate equals target): FAIL\n    Expected: {:?}\n    Got:      {:?}", exp, got); }
    }
    {
        let got = combination_sum(vec![2], 4);
        let exp = vec![vec![2, 2]];
        if got == exp { passed += 1; println!("  Test 5 (reuse single candidate): PASS"); }
        else { println!("  Test 5 (reuse single candidate): FAIL\n    Expected: {:?}\n    Got:      {:?}", exp, got); }
    }
    {
        let got = combination_sum(vec![8, 7, 4, 3], 11);
        let exp = vec![vec![3, 4, 4], vec![3, 8], vec![4, 7]];
        if got == exp { passed += 1; println!("  Test 6 (unsorted candidates multiple combos): PASS"); }
        else { println!("  Test 6 (unsorted candidates multiple combos): FAIL\n    Expected: {:?}\n    Got:      {:?}", exp, got); }
    }
    {
        let got = combination_sum(vec![3, 5], 7);
        if got.is_empty() { passed += 1; println!("  Test 7 (no valid combination): PASS"); }
        else { println!("  Test 7 (no valid combination): FAIL"); }
    }
    {
        let got = combination_sum(vec![3], 9);
        let exp = vec![vec![3, 3, 3]];
        if got == exp { passed += 1; println!("  Test 8 (triple reuse): PASS"); }
        else { println!("  Test 8 (triple reuse): FAIL\n    Expected: {:?}\n    Got:      {:?}", exp, got); }
    }

    println!("\n  {}/8 passed", passed);
    println!("============================================================\n");

    std::process::exit(if passed == 8 { 0 } else { 1 });
}
