/*
 * P442: Find All Duplicates in an Array (Medium)
 * https://leetcode.com/problems/find-all-duplicates-in-an-array/
 * Topics: Array, Hash Table
 *
 * Given an integer array nums of length n where all the integers of nums are in the range [1, n] and each integer appears at most twice, return an array of all the integers that appears twice.
 * You must write an algorithm that runs in O(n) time and uses only constant auxiliary space, excluding the space needed to store the output
 *
 * Example 1:
 *     Input: nums = [4,3,2,7,8,2,3,1]
 *     Output: [2,3]
 *
 * Example 2:
 *     Input: nums = [1,1,2]
 *     Output: [1]
 *
 * Example 3:
 *     Input: nums = [1]
 *     Output: []
 *
 * Constraints:
 *     - n == nums.length
 *     - 1 <= n <= 105
 *     - 1 <= nums[i] <= n
 *     - Each element in nums appears once or twice.
 *
 * Template (python3):
 *     class Solution:
 *         def findDuplicates(self, nums: List[int]) -> List[int]:
 *
 * Hint: Negate the value at index abs(num)-1 to mark seen numbers in-place.
 */


fn find_duplicates(nums: &mut [i32]) -> Vec<i32> {
    let n = nums.len();
    let mut result = Vec::new();
    for i in 0..n {
        let idx = (nums[i].abs() - 1) as usize;
        if nums[idx] < 0 {
            result.push(nums[i].abs());
        } else {
            nums[idx] = -nums[idx];
        }
    }
    result
}

fn main() {
    let mut passed = 0;
    let total = 7;
    println!("\n============================================================");
    println!("  442. Find All Duplicates in an Array");
    println!("============================================================");

    {
        let mut nums = vec![4, 3, 2, 7, 8, 2, 3, 1];
        let got = find_duplicates(&mut nums);
        let expected = vec![2, 3];
        if got == expected { passed += 1; println!("  Test 1 (example 1): PASS"); }
        else { println!("  Test 1 (example 1): FAIL\n  Expected: {:?}, Got: {:?}", expected, got); }
    }
    {
        let mut nums = vec![1, 1, 2];
        let got = find_duplicates(&mut nums);
        let expected = vec![1];
        if got == expected { passed += 1; println!("  Test 2 (example 2): PASS"); }
        else { println!("  Test 2 (example 2): FAIL\n  Expected: {:?}, Got: {:?}", expected, got); }
    }
    {
        let mut nums = vec![1];
        let got = find_duplicates(&mut nums);
        let expected: Vec<i32> = vec![];
        if got == expected { passed += 1; println!("  Test 3 (single): PASS"); }
        else { println!("  Test 3 (single): FAIL\n  Expected: {:?}, Got: {:?}", expected, got); }
    }
    {
        let mut nums = vec![2, 2];
        let got = find_duplicates(&mut nums);
        let expected = vec![2];
        if got == expected { passed += 1; println!("  Test 4 (all same, n=2): PASS"); }
        else { println!("  Test 4 (all same, n=2): FAIL\n  Expected: {:?}, Got: {:?}", expected, got); }
    }
    {
        let mut nums = vec![1, 2, 2, 1];
        let got = find_duplicates(&mut nums);
        let expected = vec![2, 1];
        if got == expected { passed += 1; println!("  Test 5 (all duplicates, n=4): PASS"); }
        else { println!("  Test 5 (all duplicates, n=4): FAIL\n  Expected: {:?}, Got: {:?}", expected, got); }
    }
    {
        let mut nums = vec![1, 2];
        let got = find_duplicates(&mut nums);
        let expected: Vec<i32> = vec![];
        if got == expected { passed += 1; println!("  Test 6 (no duplicates): PASS"); }
        else { println!("  Test 6 (no duplicates): FAIL\n  Expected: {:?}, Got: {:?}", expected, got); }
    }
    {
        let mut nums = vec![10, 2, 5, 10, 9, 1, 1, 7, 9, 6];
        let got = find_duplicates(&mut nums);
        let expected = vec![10, 1, 9];
        if got == expected { passed += 1; println!("  Test 7 (large, multiple duplicates): PASS"); }
        else { println!("  Test 7 (large, multiple duplicates): FAIL\n  Expected: {:?}, Got: {:?}", expected, got); }
    }

    println!("\n  {}/{} passed", passed, total);
    println!("============================================================\n");
    std::process::exit(if passed == total { 0 } else { 1 });
}
