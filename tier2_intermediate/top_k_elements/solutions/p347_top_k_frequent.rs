/*
 * P347: Top K Frequent Elements (Medium)
 * https://leetcode.com/problems/top-k-frequent-elements/
 * Topics: Array, Hash Table, Divide and Conquer, Sorting, Heap (Priority Queue), Bucket Sort, Counting, Quickselect
 *
 * Given an integer array nums and an integer k, return the k most frequent elements. You may return the answer in any order.
 *
 * Example 1:
 *     Input: nums = [1,1,1,2,2,3], k = 2
 *     Output: [1,2]
 *
 * Example 2:
 *     Input: nums = [1], k = 1
 *     Output: [1]
 *
 * Constraints:
 *     - 1 <= nums.length <= 105
 *     - -104 <= nums[i] <= 104
 *     - k is in the range [1, the number of unique elements in the array].
 *     - It is guaranteed that the answer is unique.
 *
 * Follow up:
 *     - Your algorithm's time complexity must be better than O(n log n), where n is the array's size.
 *
 * Template (python3):
 *     class Solution:
 *         def topKFrequent(self, nums: List[int], k: int) -> List[int]:
 *
 * Hint: Use a frequency counter and a min-heap of size k.
 */


use std::collections::HashMap;

fn top_k_frequent(nums: &[i32], k: i32) -> Vec<i32> {
    let k = k as usize;
    let mut freq: HashMap<i32, i32> = HashMap::new();
    for &x in nums {
        *freq.entry(x).or_insert(0) += 1;
    }
    let mut items: Vec<(i32, i32)> = freq.into_iter().collect();
    items.sort_by(|a, b| b.1.cmp(&a.1).then(b.0.cmp(&a.0)));
    items.into_iter().take(k).map(|(v, _)| v).collect()
}

fn main() {
    struct Case { label: &'static str, input: &'static [i32], k: i32, expected: &'static [i32] }
    let tests: &[Case] = &[
        Case { label: "example 1", input: &[1, 1, 1, 2, 2, 3], k: 2, expected: &[1, 2] },
        Case { label: "example 2", input: &[1], k: 1, expected: &[1] },
        Case { label: "distinct frequencies", input: &[7, 7, 7, 7, 1, 2, 2, 2], k: 2, expected: &[7, 2] },
        Case { label: "all freq 1", input: &[1, 2, 3, 4, 5, 6], k: 3, expected: &[6, 5, 4] },
        Case { label: "all same element", input: &[1, 1, 1, 1], k: 1, expected: &[1] },
        Case { label: "clear frequency ranking", input: &[1, 1, 2, 2, 2, 3, 3, 3, 3], k: 2, expected: &[3, 2] },
        Case { label: "negative numbers", input: &[-1, -1, -1, 2, 2], k: 1, expected: &[-1] },
        Case { label: "zero values", input: &[0, 0, 0, 0, 1, 1, 2], k: 2, expected: &[0, 1] },
    ];

    println!("\n============================================================");
    println!("  347. Top K Frequent Elements");
    println!("============================================================");
    let mut passed = 0;
    for (i, tc) in tests.iter().enumerate() {
        let got = top_k_frequent(tc.input, tc.k);
        if got == tc.expected {
            passed += 1;
            println!("  Test {} ({}): PASS", i + 1, tc.label);
        } else {
            println!("  Test {} ({}): FAIL", i + 1, tc.label);
            println!("    Expected: {:?}", tc.expected);
            println!("    Got:      {:?}", got);
        }
    }

    println!("\n  {}/{} passed", passed, tests.len());
    println!("============================================================\n");
    std::process::exit(if passed == tests.len() { 0 } else { 1 });
}
