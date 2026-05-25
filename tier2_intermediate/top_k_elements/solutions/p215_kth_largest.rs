/*
 * P215: Kth Largest Element in an Array (Medium)
 * https://leetcode.com/problems/kth-largest-element-in-an-array/
 * Topics: Array, Divide and Conquer, Sorting, Heap (Priority Queue), Quickselect
 *
 * Given an integer array nums and an integer k, return the kth largest element in the array.
 * Note that it is the kth largest element in the sorted order, not the kth distinct element.
 * Can you solve it without sorting?
 *
 * Example 1:
 *     Input: nums = [3,2,1,5,6,4], k = 2
 *     Output: 5
 *
 * Example 2:
 *     Input: nums = [3,2,3,1,2,4,5,5,6], k = 4
 *     Output: 4
 *
 * Constraints:
 *     - 1 <= k <= nums.length <= 105
 *     - -104 <= nums[i] <= 104
 *
 * Template (python3):
 *     class Solution:
 *         def findKthLargest(self, nums: List[int], k: int) -> int:
 *
 * Hint: Use a min-heap of size k to efficiently find the kth largest element.
 */


fn find_kth_largest(nums: &mut Vec<i32>, k: i32) -> i32 {
    let k = k as usize;
    nums.select_nth_unstable_by(k - 1, |a, b| b.cmp(a));
    nums[k - 1]
}

fn main() {
    struct Case { label: &'static str, input: &'static [i32], k: i32, expected: i32 }
    let tests: &[Case] = &[
        Case { label: "example 1", input: &[3, 2, 1, 5, 6, 4], k: 2, expected: 5 },
        Case { label: "example 2", input: &[3, 2, 3, 1, 2, 4, 5, 5, 6], k: 4, expected: 4 },
        Case { label: "single element", input: &[1], k: 1, expected: 1 },
        Case { label: "negative numbers", input: &[-1, -2, -3], k: 1, expected: -1 },
        Case { label: "all duplicates", input: &[5, 5, 5, 5], k: 2, expected: 5 },
        Case { label: "k equals length", input: &[1, 2, 3], k: 3, expected: 1 },
        Case { label: "mixed negatives and zero", input: &[-100, 0, 100], k: 2, expected: 0 },
        Case { label: "all negative duplicates", input: &[-1, -1, -1, -1], k: 3, expected: -1 },
    ];

    println!("\n============================================================");
    println!("  215. Kth Largest Element in an Array");
    println!("============================================================");
    let mut passed = 0;
    let n_tests = tests.len();
    for (i, tc) in tests.iter().enumerate() {
        let mut nums = tc.input.to_vec();
        let got = find_kth_largest(&mut nums, tc.k);
        if got == tc.expected {
            passed += 1;
            println!("  Test {} ({}): PASS", i + 1, tc.label);
        } else {
            println!("  Test {} ({}): FAIL", i + 1, tc.label);
            println!("    Expected: {}\n    Got:      {}", tc.expected, got);
        }
    }

    let mut nums_100: Vec<i32> = (1..=100).collect();
    let got_100 = find_kth_largest(&mut nums_100, 50);
    let total = n_tests + 1;
    if got_100 == 51 {
        passed += 1;
        println!("  Test {} (100 elements k=50): PASS", n_tests + 1);
    } else {
        println!("  Test {} (100 elements k=50): FAIL", n_tests + 1);
        println!("    Expected: 51\n    Got:      {}", got_100);
    }

    println!("\n  {}/{} passed", passed, total);
    println!("============================================================\n");
    std::process::exit(if passed == total { 0 } else { 1 });
}
