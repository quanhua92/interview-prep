/*
 * P456: 132 Pattern [PREMIUM] (Medium)
 * https://leetcode.com/problems/132-pattern/
 * Topics: Array, Binary Search, Stack, Monotonic Stack, Ordered Set
 *
 * Given an array of n integers nums, a 132 pattern is a subsequence of three integers nums[i], nums[j] and nums[k] such that i < j < k and nums[i] < nums[k] < nums[j].
 * Return true if there is a 132 pattern in nums, otherwise, return false.
 * Example 1:
 *     Input: nums = [1,2,3,4]
 *     Output: false
 *     Explanation: There is no 132 pattern in the sequence.
 *
 * Example 2:
 *     Input: nums = [3,1,4,2]
 *     Output: true
 *     Explanation: There is a 132 pattern in the sequence: [1, 4, 2].
 *
 * Example 3:
 *     Input: nums = [-1,3,2,0]
 *     Output: true
 *     Explanation: There are three 132 patterns in the sequence: [-1, 3, 2], [-1, 3, 0] and [-1, 2, 0].
 *
 * Constraints:
 *     - n == nums.length
 *     - 1 <= n <= 2 * 105
 *     - -109 <= nums[i] <= 109
 *
 * Template (python3):
 *     class Solution:
 *         def find132pattern(self, nums: List[int]) -> bool:
 */


fn find132pattern(nums: &[i32]) -> bool {
    let mut third: i64 = i64::MIN;
    let mut stack: Vec<i32> = Vec::new();
    for i in (0..nums.len()).rev() {
        if (nums[i] as i64) < third {
            return true;
        }
        while !stack.is_empty() && *stack.last().unwrap() < nums[i] {
            third = stack.pop().unwrap() as i64;
        }
        stack.push(nums[i]);
    }
    false
}

fn main() {
    struct Case { label: &'static str, input: &'static [i32], expected: bool }
    let tests: &[Case] = &[
        Case { label: "example 1", input: &[1, 2, 3, 4], expected: false },
        Case { label: "example 2", input: &[3, 1, 4, 2], expected: true },
        Case { label: "example 3", input: &[-1, 3, 2, 0], expected: true },
        Case { label: "two elements", input: &[1, 2], expected: false },
        Case { label: "all same", input: &[2, 2, 2], expected: false },
        Case { label: "strictly decreasing", input: &[5, 4, 3, 2, 1], expected: false },
        Case { label: "pattern near end", input: &[1, 3, 0, 2], expected: true },
    ];

    println!("\n============================================================");
    println!("  456. 132 Pattern");
    println!("============================================================");
    let mut passed = 0;
    for (i, tc) in tests.iter().enumerate() {
        let got = find132pattern(tc.input);
        if got == tc.expected {
            passed += 1;
            println!("  Test {} ({}): PASS", i + 1, tc.label);
        } else {
            println!("  Test {} ({}): FAIL", i + 1, tc.label);
            println!("    Expected: {}, Got: {}", tc.expected, got);
        }
    }
    println!("\n  {}/{} passed", passed, tests.len());
    println!("============================================================\n");
    std::process::exit(if passed == tests.len() { 0 } else { 1 });
}
