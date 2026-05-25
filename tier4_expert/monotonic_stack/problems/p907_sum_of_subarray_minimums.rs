/*
 * P907: Sum of Subarray Minimums (Medium)
 * https://leetcode.com/problems/sum-of-subarray-minimums/
 * Topics: Array, Dynamic Programming, Stack, Monotonic Stack
 * 
 * Given an array of integers arr, find the sum of min(b), where b ranges over every (contiguous) subarray of arr. Since the answer may be large, return the answer modulo 109 + 7.
 * 
 * Example 1:
 *     Input: arr = [3,1,2,4]
 *     Output: 17
 *     Explanation:
 *     Subarrays are [3], [1], [2], [4], [3,1], [1,2], [2,4], [3,1,2], [1,2,4], [3,1,2,4].
 *     Minimums are 3, 1, 2, 4, 1, 1, 2, 1, 1, 1.
 *     Sum is 17.
 * 
 * Example 2:
 *     Input: arr = [11,81,94,43,3]
 *     Output: 444
 * 
 * Constraints:
 *     - 1 <= arr.length <= 3 * 104
 *     - 1 <= arr[i] <= 3 * 104
 * 
 * Template (python3):
 *     class Solution:
 *         def sumSubarrayMins(self, arr: List[int]) -> int:
 * 
 * Hint: Use a monotonic stack to find the number of subarrays where each element is the minimum.
 */
const MOD: i64 = 1_000_000_007;

fn sum_subarray_mins(arr: &[i32]) -> i32 {
    todo!()
}

fn main() {
    struct Case { label: &'static str, input: &'static [i32], expected: i32 }
    let tests: &[Case] = &[
        Case { label: "example 1", input: &[3, 1, 2, 4], expected: 17 },
        Case { label: "example 2", input: &[11, 81, 94, 43, 3], expected: 444 },
        Case { label: "single element", input: &[1], expected: 1 },
        Case { label: "two elements", input: &[2, 1], expected: 4 },
        Case { label: "all same", input: &[3, 3, 3], expected: 18 },
        Case { label: "strictly increasing", input: &[1, 2, 3], expected: 10 },
        Case { label: "strictly decreasing", input: &[3, 2, 1], expected: 10 },
    ];

    println!("\n============================================================");
    println!("  907. Sum of Subarray Minimums");
    println!("============================================================");
    let mut passed = 0;
    for (i, tc) in tests.iter().enumerate() {
        let got = sum_subarray_mins(tc.input);
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
