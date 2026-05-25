/*
 * P448: Find All Numbers Disappeared in an Array (Easy)
 * https://leetcode.com/problems/find-all-numbers-disappeared-in-an-array/
 * Topics: Array, Hash Table
 * 
 * Given an array nums of n integers where nums[i] is in the range [1, n], return an array of all the integers in the range [1, n] that do not appear in nums.
 * 
 * Example 1:
 *     Input: nums = [4,3,2,7,8,2,3,1]
 *     Output: [5,6]
 * 
 * Example 2:
 *     Input: nums = [1,1]
 *     Output: [2]
 * 
 * Constraints:
 *     - n == nums.length
 *     - 1 <= n <= 105
 *     - 1 <= nums[i] <= n
 * 
 * Follow up:
 *     - Could you do it without extra space and in O(n) runtime? You may assume the returned list does not count as extra space.
 * 
 * Hints:
 *     - This is a really easy problem if you decide to use additional memory. For those trying to write an initial solution using additional memory, think <b>counters!</b>
 *     - However, the trick really is to not use any additional space than what is already available to use. Sometimes, multiple passes over the input array help find the solution. However, there's an interesting piece of information in this problem that makes it easy to re-use the input array itself for the solution.
 *     - The problem specifies that the numbers in the array will be in the range [1, n] where n is the number of elements in the array. Can we use this information and modify the array in-place somehow to find what we need?
 * 
 * Template (python3):
 *     class Solution:
 *         def findDisappearedNumbers(self, nums: List[int]) -> List[int]:
 * 
 * Hint: Negate the value at index abs(n)-1 for each number. Indices with positive values are missing.
 */
fn find_disappeared_numbers(nums: &mut [i32]) -> Vec<i32> {
    todo!()
}

fn main() {
    let mut passed = 0;
    let total = 7;
    println!("\n============================================================");
    println!("  448. Find All Numbers Disappeared in an Array");
    println!("============================================================");

    {
        let mut nums = vec![4, 3, 2, 7, 8, 2, 3, 1];
        let got = find_disappeared_numbers(&mut nums);
        let expected = vec![5, 6];
        if got == expected { passed += 1; println!("  Test 1 (example 1): PASS"); }
        else { println!("  Test 1 (example 1): FAIL\n  Expected: {:?}, Got: {:?}", expected, got); }
    }
    {
        let mut nums = vec![1, 1];
        let got = find_disappeared_numbers(&mut nums);
        let expected = vec![2];
        if got == expected { passed += 1; println!("  Test 2 (example 2): PASS"); }
        else { println!("  Test 2 (example 2): FAIL\n  Expected: {:?}, Got: {:?}", expected, got); }
    }
    {
        let mut nums = vec![2, 2];
        let got = find_disappeared_numbers(&mut nums);
        let expected = vec![1];
        if got == expected { passed += 1; println!("  Test 3 (example 3): PASS"); }
        else { println!("  Test 3 (example 3): FAIL\n  Expected: {:?}, Got: {:?}", expected, got); }
    }
    {
        let mut nums = vec![1];
        let got = find_disappeared_numbers(&mut nums);
        let expected: Vec<i32> = vec![];
        if got == expected { passed += 1; println!("  Test 4 (single element, none missing): PASS"); }
        else { println!("  Test 4 (single element, none missing): FAIL\n  Expected: {:?}, Got: {:?}", expected, got); }
    }
    {
        let mut nums = vec![1, 1, 1, 1];
        let got = find_disappeared_numbers(&mut nums);
        let expected = vec![2, 3, 4];
        if got == expected { passed += 1; println!("  Test 5 (all same value): PASS"); }
        else { println!("  Test 5 (all same value): FAIL\n  Expected: {:?}, Got: {:?}", expected, got); }
    }
    {
        let mut nums = vec![1, 2, 3, 4, 5];
        let got = find_disappeared_numbers(&mut nums);
        let expected: Vec<i32> = vec![];
        if got == expected { passed += 1; println!("  Test 6 (identity permutation, none missing): PASS"); }
        else { println!("  Test 6 (identity permutation, none missing): FAIL\n  Expected: {:?}, Got: {:?}", expected, got); }
    }
    {
        let mut nums = vec![5, 4, 6, 7, 9, 10, 9, 6, 5, 4];
        let got = find_disappeared_numbers(&mut nums);
        let expected = vec![1, 2, 3, 8];
        if got == expected { passed += 1; println!("  Test 7 (large, many disappeared): PASS"); }
        else { println!("  Test 7 (large, many disappeared): FAIL\n  Expected: {:?}, Got: {:?}", expected, got); }
    }

    println!("\n  {}/{} passed", passed, total);
    println!("============================================================\n");
    std::process::exit(if passed == total { 0 } else { 1 });
}
