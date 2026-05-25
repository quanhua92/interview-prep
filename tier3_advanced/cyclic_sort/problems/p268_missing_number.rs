/*
 * P268: Missing Number (Easy)
 * https://leetcode.com/problems/missing-number/
 * Topics: Array, Hash Table, Math, Binary Search, Bit Manipulation, Sorting
 * 
 * Given an array nums containing n distinct numbers in the range [0, n], return the only number in the range that is missing from the array.
 * 
 * Example 1:
 *     Input: nums = [3,0,1]
 *     Output: 2
 *     Explanation:
 *     n = 3 since there are 3 numbers, so all numbers are in the range [0,3] . 2 is the missing number in the range since it does not appear in nums .
 * 
 * Example 2:
 *     Input: nums = [0,1]
 *     Output: 2
 *     Explanation:
 *     n = 2 since there are 2 numbers, so all numbers are in the range [0,2] . 2 is the missing number in the range since it does not appear in nums .
 * 
 * Example 3:
 *     Input: nums = [9,6,4,2,3,5,7,0,1]
 *     Output: 8
 *     Explanation:
 *     n = 9 since there are 9 numbers, so all numbers are in the range [0,9] . 8 is the missing number in the range since it does not appear in nums .
 * 
 * Constraints:
 *     - n == nums.length
 *     - 1 <= n <= 104
 *     - 0 <= nums[i] <= n
 *     - All the numbers of nums are unique.
 * 
 * Follow up:
 *     - Could you implement a solution using only O(1) extra space complexity and O(n) runtime complexity?
 * 
 * Template (python3):
 *     class Solution:
 *         def missingNumber(self, nums: List[int]) -> int:
 * 
 * Hint: Use the sum formula n*(n+1)//2 minus the actual sum to find the missing number.
 */
fn missing_number(nums: &mut [i32]) -> i32 {
    todo!()
}

fn main() {
    let mut passed = 0;
    let total = 7;
    println!("\n============================================================");
    println!("  268. Missing Number");
    println!("============================================================");

    {
        let mut nums = vec![3, 0, 1];
        let got = missing_number(&mut nums);
        if got == 2 { passed += 1; println!("  Test 1 (example 1): PASS"); }
        else { println!("  Test 1 (example 1): FAIL\n  Expected: 2, Got: {}", got); }
    }
    {
        let mut nums = vec![0, 1];
        let got = missing_number(&mut nums);
        if got == 2 { passed += 1; println!("  Test 2 (example 2): PASS"); }
        else { println!("  Test 2 (example 2): FAIL\n  Expected: 2, Got: {}", got); }
    }
    {
        let mut nums = vec![9, 6, 4, 2, 3, 5, 7, 0, 1];
        let got = missing_number(&mut nums);
        if got == 8 { passed += 1; println!("  Test 3 (example 3): PASS"); }
        else { println!("  Test 3 (example 3): FAIL\n  Expected: 8, Got: {}", got); }
    }
    {
        let mut nums = vec![1];
        let got = missing_number(&mut nums);
        if got == 0 { passed += 1; println!("  Test 4 (missing 0, n=1): PASS"); }
        else { println!("  Test 4 (missing 0, n=1): FAIL\n  Expected: 0, Got: {}", got); }
    }
    {
        let mut nums = vec![0];
        let got = missing_number(&mut nums);
        if got == 1 { passed += 1; println!("  Test 5 (missing n, n=1): PASS"); }
        else { println!("  Test 5 (missing n, n=1): FAIL\n  Expected: 1, Got: {}", got); }
    }
    {
        let mut nums = vec![0, 1, 2, 3];
        let got = missing_number(&mut nums);
        if got == 4 { passed += 1; println!("  Test 6 (missing last, sorted): PASS"); }
        else { println!("  Test 6 (missing last, sorted): FAIL\n  Expected: 4, Got: {}", got); }
    }
    {
        let mut nums = vec![1, 2, 3, 4, 5];
        let got = missing_number(&mut nums);
        if got == 0 { passed += 1; println!("  Test 7 (missing 0, n=5): PASS"); }
        else { println!("  Test 7 (missing 0, n=5): FAIL\n  Expected: 0, Got: {}", got); }
    }

    println!("\n  {}/{} passed", passed, total);
    println!("============================================================\n");
    std::process::exit(if passed == total { 0 } else { 1 });
}
