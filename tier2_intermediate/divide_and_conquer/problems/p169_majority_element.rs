/*
 * P169: Majority Element (Easy)
 * https://leetcode.com/problems/majority-element/
 * Topics: Array, Hash Table, Divide and Conquer, Sorting, Counting
 * 
 * Given an array nums of size n, return the majority element.
 * The majority element is the element that appears more than ⌊n / 2⌋ times. You may assume that the majority element always exists in the array.
 * 
 * Example 1:
 *     Input: nums = [3,2,3]
 *     Output: 3
 * 
 * Example 2:
 *     Input: nums = [2,2,1,1,1,2,2]
 *     Output: 2
 * 
 * Constraints:
 *     - n == nums.length
 *     - 1 <= n <= 5 * 104
 *     - -109 <= nums[i] <= 109
 * 
 * Template (python3):
 *     class Solution:
 *         def majorityElement(self, nums: List[int]) -> int:
 * 
 * Hint: Use Boyer-Moore voting algorithm — maintain a candidate and count.
 */
fn majority_element(nums: &[i32]) -> i32 {
    todo!()
}

fn main() {
    struct Case<'a> { label: &'a str, input: &'a [i32], expected: i32 }
    let tests: &[Case] = &[
        Case { label: "example 1", input: &[3, 2, 3], expected: 3 },
        Case { label: "example 2", input: &[2, 2, 1, 1, 1, 2, 2], expected: 2 },
        Case { label: "single element", input: &[1], expected: 1 },
        Case { label: "majority at end", input: &[1, 2, 3, 2, 2], expected: 2 },
        Case { label: "all same", input: &[5, 5, 5, 5, 5], expected: 5 },
        Case { label: "negative majority", input: &[-1, -1, 2], expected: -1 },
        Case { label: "two elements", input: &[3, 3], expected: 3 },
    ];

    println!("\n============================================================");
    println!("  169. Majority Element");
    println!("============================================================");
    let mut passed = 0;
    for (i, tc) in tests.iter().enumerate() {
        let got = majority_element(tc.input);
        if got == tc.expected {
            passed += 1;
            println!("  Test {} ({}): PASS", i + 1, tc.label);
        } else {
            println!("  Test {} ({}): FAIL", i + 1, tc.label);
            println!("    Expected: {}\n    Got:      {}", tc.expected, got);
        }
    }
    println!("\n  {}/{} passed", passed, tests.len());
    println!("============================================================\n");
    std::process::exit(if passed == tests.len() { 0 } else { 1 });
}
