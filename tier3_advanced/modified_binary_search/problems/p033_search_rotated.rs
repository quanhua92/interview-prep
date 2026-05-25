/*
 * P33: Search in Rotated Sorted Array (Medium)
 * https://leetcode.com/problems/search-in-rotated-sorted-array/
 * Topics: Array, Binary Search
 * 
 * There is an integer array nums sorted in ascending order (with distinct values).
 * Prior to being passed to your function, nums is possibly rotated at an unknown pivot index k (1 <= k < nums.length) such that the resulting array is [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]] (0-indexed). For example, [0,1,2,4,5,6,7] might be rotated at pivot index 3 and become [4,5,6,7,0,1,2].
 * Given the array nums after the possible rotation and an integer target, return the index of target if it is in nums, or -1 if it is not in nums.
 * You must write an algorithm with O(log n) runtime complexity.
 * 
 * Example 1:
 *     Input: nums = [4,5,6,7,0,1,2], target = 0
 *     Output: 4
 * 
 * Example 2:
 *     Input: nums = [4,5,6,7,0,1,2], target = 3
 *     Output: -1
 * 
 * Example 3:
 *     Input: nums = [1], target = 0
 *     Output: -1
 * 
 * Constraints:
 *     - 1 <= nums.length <= 5000
 *     - -104 <= nums[i] <= 104
 *     - All values of nums are unique.
 *     - nums is an ascending array that is possibly rotated.
 *     - -104 <= target <= 104
 * 
 * Template (python3):
 *     class Solution:
 *         def search(self, nums: List[int], target: int) -> int:
 * 
 * Hint: Determine which half is sorted, then check if target lies in that half.
 */
fn search(nums: &[i32], target: i32) -> i32 {
    todo!()
}

struct TestCase {
    label: &'static str,
    nums: &'static [i32],
    target: i32,
    expected: i32,
}

fn main() {
    let tests: &[TestCase] = &[
        TestCase { label: "example 1", nums: &[4,5,6,7,0,1,2], target: 0, expected: 4 },
        TestCase { label: "example 2", nums: &[4,5,6,7,0,1,2], target: 3, expected: -1 },
        TestCase { label: "single element", nums: &[1], target: 0, expected: -1 },
        TestCase { label: "single element found", nums: &[1], target: 1, expected: 0 },
        TestCase { label: "two elements rotated at pivot", nums: &[1,3], target: 3, expected: 1 },
        TestCase { label: "two elements no rotation", nums: &[1,3], target: 1, expected: 0 },
        TestCase { label: "target at first index", nums: &[5,1,3], target: 5, expected: 0 },
        TestCase { label: "target at last index", nums: &[5,1,3], target: 3, expected: 2 },
        TestCase { label: "large rotated target at start", nums: &[6,7,0,1,2,3,4,5], target: 6, expected: 0 },
        TestCase { label: "large rotated target at end", nums: &[6,7,0,1,2,3,4,5], target: 5, expected: 7 },
        TestCase { label: "no rotation sorted", nums: &[1,2,3,4,5], target: 3, expected: 2 },
        TestCase { label: "negative values target at start", nums: &[-10,-5,0,1,2,3,-9], target: -10, expected: 0 },
    ];

    println!("\n============================================================");
    println!("  33. Search in Rotated Sorted Array");
    println!("============================================================");
    let mut passed = 0;
    for (i, tc) in tests.iter().enumerate() {
        let got = search(tc.nums, tc.target);
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
