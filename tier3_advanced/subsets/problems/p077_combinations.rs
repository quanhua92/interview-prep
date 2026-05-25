/*
 * P77: Combinations (Medium)
 * https://leetcode.com/problems/combinations/
 * Topics: Backtracking
 * 
 * Given two integers n and k, return all possible combinations of k numbers chosen from the range [1, n].
 * You may return the answer in any order.
 * 
 * Example 1:
 *     Input: n = 4, k = 2
 *     Output: [[1,2],[1,3],[1,4],[2,3],[2,4],[3,4]]
 *     Explanation: There are 4 choose 2 = 6 total combinations.
 *     Note that combinations are unordered, i.e., [1,2] and [2,1] are considered to be the same combination.
 * 
 * Example 2:
 *     Input: n = 1, k = 1
 *     Output: [[1]]
 *     Explanation: There is 1 choose 1 = 1 total combination.
 * 
 * Constraints:
 *     - 1 <= n <= 20
 *     - 1 <= k <= n
 * 
 * Template (python3):
 *     class Solution:
 *         def combine(self, n: int, k: int) -> List[List[int]]:
 * 
 * Hint: Use backtracking with a start index to generate all k-length combinations from 1..n.
 */
#[allow(unused_imports)]
use rstest;

fn combine(n: i32, k: i32) -> Vec<Vec<i32>> {
    todo!()
}

fn main() {
    println!("\n============================================================");
    println!("  77. Combinations");
    println!("============================================================");

    let mut passed = 0;

    {
        let got = combine(4, 2);
        let exp: Vec<Vec<i32>> = vec![vec![1,2],vec![1,3],vec![1,4],vec![2,3],vec![2,4],vec![3,4]];
        if got == exp { passed += 1; println!("  Test 1 (example 1): PASS"); }
        else { println!("  Test 1 (example 1): FAIL\n    Expected: {:?}\n    Got:      {:?}", exp, got); }
    }
    {
        let got = combine(1, 1);
        let exp: Vec<Vec<i32>> = vec![vec![1]];
        if got == exp { passed += 1; println!("  Test 2 (example 2): PASS"); }
        else { println!("  Test 2 (example 2): FAIL\n    Expected: {:?}\n    Got:      {:?}", exp, got); }
    }
    {
        let got = combine(3, 1);
        let exp: Vec<Vec<i32>> = vec![vec![1],vec![2],vec![3]];
        if got == exp { passed += 1; println!("  Test 3 (example 3): PASS"); }
        else { println!("  Test 3 (example 3): FAIL\n    Expected: {:?}\n    Got:      {:?}", exp, got); }
    }
    {
        let got = combine(5, 5);
        let exp: Vec<Vec<i32>> = vec![vec![1,2,3,4,5]];
        if got == exp { passed += 1; println!("  Test 4 (k equals n): PASS"); }
        else { println!("  Test 4 (k equals n): FAIL\n    Expected: {:?}\n    Got:      {:?}", exp, got); }
    }
    {
        let got = combine(5, 3);
        let exp: Vec<Vec<i32>> = vec![
            vec![1,2,3],vec![1,2,4],vec![1,2,5],vec![1,3,4],vec![1,3,5],vec![1,4,5],
            vec![2,3,4],vec![2,3,5],vec![2,4,5],vec![3,4,5],
        ];
        if got == exp { passed += 1; println!("  Test 5 (mid range): PASS"); }
        else { println!("  Test 5 (mid range): FAIL\n    Expected: {:?}\n    Got:      {:?}", exp, got); }
    }
    {
        let got = combine(2, 2);
        let exp: Vec<Vec<i32>> = vec![vec![1,2]];
        if got == exp { passed += 1; println!("  Test 6 (smallest k equals n): PASS"); }
        else { println!("  Test 6 (smallest k equals n): FAIL\n    Expected: {:?}\n    Got:      {:?}", exp, got); }
    }
    {
        let got = combine(6, 1);
        let exp: Vec<Vec<i32>> = vec![vec![1],vec![2],vec![3],vec![4],vec![5],vec![6]];
        if got == exp { passed += 1; println!("  Test 7 (k equals 1 larger n): PASS"); }
        else { println!("  Test 7 (k equals 1 larger n): FAIL\n    Expected: {:?}\n    Got:      {:?}", exp, got); }
    }

    println!("\n  {}/7 passed", passed);
    println!("============================================================\n");

    std::process::exit(if passed == 7 { 0 } else { 1 });
}
