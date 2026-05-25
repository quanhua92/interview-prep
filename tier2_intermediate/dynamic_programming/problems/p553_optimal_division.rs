/*
 * P553: Optimal Division [PREMIUM] (Medium)
 * https://leetcode.com/problems/optimal-division/
 * Topics: Array, Math, Dynamic Programming
 * 
 * You are given an integer array nums. The adjacent integers in nums will perform the float division.
 * However, you can add any number of parenthesis at any position to change the priority of operations. You want to add these parentheses such the value of the expression after the evaluation is maximum.
 * Return the corresponding expression that has the maximum value in string format.
 * Note: your expression should not contain redundant parenthesis.
 * Example 1:
 *     Input: nums = [1000,100,10,2]
 *     Output: "1000/(100/10/2)"
 *     Explanation: 1000/(100/10/2) = 1000/((100/10)/2) = 200
 *     However, the bold parenthesis in "1000/((100/10)/2)" are redundant since they do not influence the operation priority.
 *     So you should return "1000/(100/10/2)".
 *     Other cases:
 *     1000/(100/10)/2 = 50
 *     1000/(100/(10/2)) = 50
 *     1000/100/10/2 = 0.5
 *     1000/100/(10/2) = 2
 * 
 * Example 2:
 *     Input: nums = [2,3,4]
 *     Output: "2/(3/4)"
 *     Explanation: (2/(3/4)) = 8/3 = 2.667
 *     It can be shown that after trying all possibilities, we cannot get an expression with evaluation greater than 2.667
 * 
 * Constraints:
 *     - 1 <= nums.length <= 10
 *     - 2 <= nums[i] <= 1000
 *     - There is only one optimal division for the given input.
 * 
 * Template (python3):
 *     class Solution:
 *         def optimalDivision(self, nums: List[int]) -> str:
 */
use rstest;

fn optimal_division(nums: &[i32]) -> String {
    todo!()
}

fn main() {
    struct TC<'a> { label: &'a str, nums: &'static [i32], expected: &'a str }
    let tests: &[TC] = &[
        TC { label: "example 1", nums: &[1000,100,10,2], expected: "1000/(100/10/2)" },
        TC { label: "example 2", nums: &[2,3,4], expected: "2/(3/4)" },
        TC { label: "two elements no parens", nums: &[2,3], expected: "2/3" },
        TC { label: "single element", nums: &[2], expected: "2" },
        TC { label: "three elements", nums: &[10,2,5], expected: "10/(2/5)" },
    ];
    let mut passed = 0;
    for (i, tc) in tests.iter().enumerate() {
        let got = optimal_division(tc.nums);
        if got == tc.expected {
            passed += 1;
            println!("  Test {} ({}): PASS", i + 1, tc.label);
        } else {
            println!("  Test {} ({}): FAIL (expected \"{}\", got \"{}\")", i + 1, tc.label, tc.expected, got);
        }
    }
    println!("\n  {}/{} passed", passed, tests.len());
    std::process::exit(if passed == tests.len() { 0 } else { 1 });
}
