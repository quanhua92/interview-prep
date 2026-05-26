/*
 * P493: Reverse Pairs [PREMIUM] (Hard)
 * https://leetcode.com/problems/reverse-pairs/
 * Topics: Array, Binary Search, Divide and Conquer, Binary Indexed Tree, Segment Tree, Merge Sort, Ordered Set
 * 
 * Given an integer array nums, return the number of reverse pairs in the array.
 * A reverse pair is a pair (i, j) where:
 * Example 1:
 *     Input: nums = [1,3,2,3,1]
 *     Output: 2
 *     Explanation: The reverse pairs are:
 *     (1, 4) --> nums[1] = 3, nums[4] = 1, 3 > 2 * 1
 *     (3, 4) --> nums[3] = 3, nums[4] = 1, 3 > 2 * 1
 * 
 * Example 2:
 *     Input: nums = [2,4,3,5,1]
 *     Output: 3
 *     Explanation: The reverse pairs are:
 *     (1, 4) --> nums[1] = 4, nums[4] = 1, 4 > 2 * 1
 *     (2, 4) --> nums[2] = 3, nums[4] = 1, 3 > 2 * 1
 *     (3, 4) --> nums[3] = 5, nums[4] = 1, 5 > 2 * 1
 * 
 * Constraints:
 *     - 1 <= nums.length <= 5 * 104
 *     - -231 <= nums[i] <= 231 - 1
 * 
 * Hint: Use the merge-sort technique.
 * Hint: Divide the array into two parts and sort them.
 * Hint: For each integer in the first part, count the number of integers that satisfy the condition from the second part. Use the pointer to help you in the counting process.
 * 
 * Template (python3):
 *     class Solution:
 *         def reversePairs(self, nums: List[int]) -> int:
 */
fn merge_sort(arr: &mut [i32], tmp: &mut [i32], left: usize, right: usize) -> i32 {
    todo!()
}

fn reverse_pairs(nums: &mut [i32]) -> i32 {
    todo!()
}

fn main() {
    let tests: Vec<(&str, Vec<i32>, i32)> = vec![
        ("example 1", vec![1,3,2,3,1], 2),
        ("example 2", vec![2,4,3,5,1], 3),
        ("single element", vec![1], 0),
        ("all descending", vec![5,4,3,2,1], 4),
        ("sorted ascending", vec![1,2,3,4,5], 0),
        ("negative numbers", vec![2,1,-1], 2),
        ("all equal", vec![1,1,1,1], 0),
    ];

    let mut passed = 0;
    println!("\n============================================================");
    println!("  493. Reverse Pairs");
    println!("============================================================");
    for (i, (label, nums, expected)) in tests.iter().enumerate() {
        let mut buf = nums.clone();
        let got = reverse_pairs(&mut buf);
        let ok = got == *expected;
        if ok { passed += 1; }
        println!("  Test {} ({}): {}", i + 1, label, if ok { "PASS" } else { "FAIL" });
    }
    println!("\n  {}/{} passed", passed, tests.len());
    println!("============================================================\n");
    std::process::exit(if passed == tests.len() { 0 } else { 1 });
}
