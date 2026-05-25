/*
 * P503: Next Greater Element II [PREMIUM] (Medium)
 * https://leetcode.com/problems/next-greater-element-ii/
 * Topics: Array, Stack, Monotonic Stack
 * 
 * Given a circular integer array nums (i.e., the next element of nums[nums.length - 1] is nums[0]), return the next greater number for every element in nums.
 * The next greater number of a number x is the first greater number to its traversing-order next in the array, which means you could search circularly to find its next greater number. If it doesn't exist, return -1 for this number.
 * Example 1:
 *     Input: nums = [1,2,1]
 *     Output: [2,-1,2]
 *     Explanation: The first 1's next greater number is 2;
 *     The number 2 can't find next greater number.
 *     The second 1's next greater number needs to search circularly, which is also 2.
 * 
 * Example 2:
 *     Input: nums = [1,2,3,4,3]
 *     Output: [2,3,4,-1,4]
 * 
 * Constraints:
 *     - 1 <= nums.length <= 104
 *     - -109 <= nums[i] <= 109
 * 
 * Template (python3):
 *     class Solution:
 *         def nextGreaterElements(self, nums: List[int]) -> List[int]:
 */
fn next_greater_elements(nums: &[i32]) -> Vec<i32> {
    todo!()
}

fn main() {
    struct Case { label: &'static str, input: &'static [i32], expected: &'static [i32] }
    let tests: &[Case] = &[
        Case { label: "example 1", input: &[1, 2, 1], expected: &[2, -1, 2] },
        Case { label: "example 2", input: &[1, 2, 3, 4, 3], expected: &[2, 3, 4, -1, 4] },
        Case { label: "single element", input: &[5], expected: &[-1] },
        Case { label: "all same", input: &[2, 2, 2], expected: &[-1, -1, -1] },
        Case { label: "strictly decreasing wraps", input: &[5, 4, 3, 2], expected: &[-1, 5, 5, 5] },
        Case { label: "with negatives", input: &[-3, -2, -1], expected: &[-2, -1, -1] },
    ];

    println!("\n============================================================");
    println!("  503. Next Greater Element II");
    println!("============================================================");
    let mut passed = 0;
    for (i, tc) in tests.iter().enumerate() {
        let got = next_greater_elements(tc.input);
        if got == tc.expected {
            passed += 1;
            println!("  Test {} ({}): PASS", i + 1, tc.label);
        } else {
            println!("  Test {} ({}): FAIL", i + 1, tc.label);
            println!("    Expected: {:?}\n    Got:      {:?}", tc.expected, got);
        }
    }
    println!("\n  {}/{} passed", passed, tests.len());
    println!("============================================================\n");
    std::process::exit(if passed == tests.len() { 0 } else { 1 });
}
