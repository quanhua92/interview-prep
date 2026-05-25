/*
 * P198: House Robber (Medium)
 * https://leetcode.com/problems/house-robber/
 * Topics: Array, Dynamic Programming
 * 
 * You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed, the only constraint stopping you from robbing each of them is that adjacent houses have security systems connected and it will automatically contact the police if two adjacent houses were broken into on the same night.
 * Given an integer array nums representing the amount of money of each house, return the maximum amount of money you can rob tonight without alerting the police.
 * 
 * Example 1:
 *     Input: nums = [1,2,3,1]
 *     Output: 4
 *     Explanation: Rob house 1 (money = 1) and then rob house 3 (money = 3).
 *     Total amount you can rob = 1 + 3 = 4.
 * 
 * Example 2:
 *     Input: nums = [2,7,9,3,1]
 *     Output: 12
 *     Explanation: Rob house 1 (money = 2), rob house 3 (money = 9) and rob house 5 (money = 1).
 *     Total amount you can rob = 2 + 9 + 1 = 12.
 * 
 * Constraints:
 *     - 1 <= nums.length <= 100
 *     - 0 <= nums[i] <= 400
 * 
 * Template (python3):
 *     class Solution:
 *         def rob(self, nums: List[int]) -> int:
 * 
 * Hint: Use two variables (prev, curr) -- for each house decide to rob or skip.
 */
use rstest;

fn rob(nums: &[i32]) -> i32 {
    todo!()
}

fn main() {
    struct TC<'a> { label: &'a str, nums: &'static [i32], expected: i32 }
    static MAX_VALS: [i32; 100] = [400; 100];
    let tests: &[TC] = &[
        TC { label: "example 1", nums: &[1,2,3,1], expected: 4 },
        TC { label: "example 2", nums: &[2,7,9,3,1], expected: 12 },
        TC { label: "single house", nums: &[1], expected: 1 },
        TC { label: "no houses", nums: &[], expected: 0 },
        TC { label: "alternate houses equal", nums: &[2,1,1,2], expected: 4 },
        TC { label: "all zeros", nums: &[0,0,0], expected: 0 },
        TC { label: "two houses", nums: &[1,2], expected: 2 },
        TC { label: "alternating high low", nums: &[10,1,10,1,10], expected: 30 },
        TC { label: "three peaks", nums: &[100,1,1,100,1,1,100], expected: 300 },
        TC { label: "max values large array", nums: &MAX_VALS, expected: 20000 },
    ];
    let mut passed = 0;
    for (i, tc) in tests.iter().enumerate() {
        let got = rob(tc.nums);
        if got == tc.expected {
            passed += 1;
            println!("  Test {} ({}): PASS", i + 1, tc.label);
        } else {
            println!("  Test {} ({}): FAIL (expected {}, got {})", i + 1, tc.label, tc.expected, got);
        }
    }
    println!("\n  {}/{} passed", passed, tests.len());
    std::process::exit(if passed == tests.len() { 0 } else { 1 });
}
