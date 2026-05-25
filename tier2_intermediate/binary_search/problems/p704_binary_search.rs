/*
 * P704: Binary Search (Easy)
 * https://leetcode.com/problems/binary-search/
 * Topics: Array, Binary Search
 * 
 * Given an array of integers nums which is sorted in ascending order, and an integer target, write a function to search target in nums. If target exists, then return its index. Otherwise, return -1.
 * You must write an algorithm with O(log n) runtime complexity.
 * 
 * Example 1:
 *     Input: nums = [-1,0,3,5,9,12], target = 9
 *     Output: 4
 *     Explanation: 9 exists in nums and its index is 4
 * 
 * Example 2:
 *     Input: nums = [-1,0,3,5,9,12], target = 2
 *     Output: -1
 *     Explanation: 2 does not exist in nums so return -1
 * 
 * Constraints:
 *     - 1 <= nums.length <= 104
 *     - -104 < nums[i], target < 104
 *     - All the integers in nums are unique.
 *     - nums is sorted in ascending order.
 * 
 * Template (python3):
 *     class Solution:
 *         def search(self, nums: List[int], target: int) -> int:
 * 
 * Hint: Use the classic binary search pattern with left and right pointers.
 */
fn search(nums: &[i32], target: i32) -> i32 {
    todo!()
}

fn main() {
    let tests: Vec<(&str, Vec<i32>, i32, i32)> = vec![
        ("example 1", vec![-1,0,3,5,9,12], 9, 4),
        ("example 2", vec![-1,0,3,5,9,12], 2, -1),
        ("single element", vec![5], 5, 0),
        ("below range", vec![-1,0,3,5,9,12], -2, -1),
        ("last element", vec![-1,0,3,5,9,12], 12, 5),
        ("two elements first", vec![1,2], 1, 0),
        ("two elements last", vec![1,2], 2, 1),
        ("large array middle target", (-5000..=5000).collect(), 0, 5000),
        ("target between elements", vec![2,4,6,8,10], 5, -1),
        ("all negative found last", vec![-3,-2,-1], -1, 2),
    ];

    let mut passed = 0;
    println!("\n============================================================");
    println!("  704. Binary Search");
    println!("============================================================");
    for (i, (label, nums, target, expected)) in tests.iter().enumerate() {
        let got = search(nums, *target);
        let ok = got == *expected;
        if ok { passed += 1; }
        println!("  Test {} ({}): {}", i + 1, label, if ok { "PASS" } else { "FAIL" });
    }
    println!("\n  {}/{} passed", passed, tests.len());
    println!("============================================================\n");
    std::process::exit(if passed == tests.len() { 0 } else { 1 });
}
