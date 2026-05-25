/*
 * P560: Subarray Sum Equals K (Medium)
 * https://leetcode.com/problems/subarray-sum-equals-k/
 * Topics: Array, Hash Table, Prefix Sum
 *
 * Given an array of integers nums and an integer k, return the total number of subarrays whose sum equals to k.
 * A subarray is a contiguous non-empty sequence of elements within an array.
 *
 * Example 1:
 *     Input: nums = [1,1,1], k = 2
 *     Output: 2
 *
 * Example 2:
 *     Input: nums = [1,2,3], k = 3
 *     Output: 2
 *
 * Constraints:
 *     - 1 <= nums.length <= 2 * 104
 *     - -1000 <= nums[i] <= 1000
 *     - -107 <= k <= 107
 *
 * Hints:
 *     - Will Brute force work here? Try to optimize it.
 *     - Can we optimize it by using some extra space?
 *     - What about storing sum frequencies in a hash table? Will it be useful?
 *     - sum(i,j)=sum(0,j)-sum(0,i), where sum(i,j) represents the sum of all the elements from index i to j-1.
 *
 * Can we use this property to optimize it.
 *
 * Template (python3):
 *     class Solution:
 *         def subarraySum(self, nums: List[int], k: int) -> int:
 *
 * Hint: Use a hash map with prefix sums to count subarrays summing to k.
 */

use std::collections::HashMap;
use rstest::TestCase;
use rstest::run_tests;

fn subarray_sum(nums: &[i32], k: i32) -> Vec<i32> {
    let mut freq: HashMap<i64, i32> = HashMap::new();
    freq.insert(0, 1);
    let mut count = 0;
    let mut curr: i64 = 0;
    for &num in nums {
        curr += num as i64;
        count += freq.get(&(curr - k as i64)).unwrap_or(&0);
        *freq.entry(curr).or_insert(0) += 1;
    }
    vec![count]
}

fn main() {
    let tests: &[TestCase] = &[
        TestCase { label: "example 1", input_arr: &[1, 1, 1], target: 2, expected: &[2] },
        TestCase { label: "example 2", input_arr: &[1, 2, 3], target: 3, expected: &[2] },
        TestCase { label: "empty array", input_arr: &[], target: 0, expected: &[0] },
        TestCase { label: "single element equals k", input_arr: &[1], target: 1, expected: &[1] },
        TestCase { label: "single element not k", input_arr: &[1], target: 2, expected: &[0] },
        TestCase { label: "negatives with zero sum", input_arr: &[1, -1, 0], target: 0, expected: &[3] },
        TestCase { label: "all zeros", input_arr: &[0, 0, 0], target: 0, expected: &[6] },
    ];
    std::process::exit(run_tests!("560. Subarray Sum Equals K", subarray_sum, tests));
}
