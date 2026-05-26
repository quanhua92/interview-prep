/*
 * P398: Random Pick Index [PREMIUM] (Medium)
 * https://leetcode.com/problems/random-pick-index/
 * Topics: Hash Table, Math, Reservoir Sampling, Randomized
 * 
 * Given an integer array nums with possible duplicates, randomly output the index of a given target number. You can assume that the given target number must exist in the array.
 * Implement the Solution class:
 * Example 1:
 *     Input
 * Example 1:
 *     ["Solution", "pick", "pick", "pick"]
 *     [[[1, 2, 3, 3, 3]], [3], [1], [3]]
 *     Output
 *     [null, 4, 0, 2]
 * 
 *     Explanation
 *     Solution solution = new Solution([1, 2, 3, 3, 3]);
 *     solution.pick(3); // It should return either index 2, 3, or 4 randomly. Each index should have equal probability of returning.
 *     solution.pick(1); // It should return 0. Since in the array only nums[0] is equal to 1.
 *     solution.pick(3); // It should return either index 2, 3, or 4 randomly. Each index should have equal probability of returning.
 * 
 * Constraints:
 *     - 1 <= nums.length <= 2 * 104
 *     - -231 <= nums[i] <= 231 - 1
 *     - target is an integer from nums.
 *     - At most 104 calls will be made to pick.
 *
 * Template (python3):
 *     class Solution:
 *
 *         def __init__(self, nums: List[int]):
 *
 *
 *         def pick(self, target: int) -> int:
 *
 *
 *
 *     # Your Solution object will be instantiated and called as such:
 *     # obj = Solution(nums)
 *     # param_1 = obj.pick(target)
 */

use std::collections::HashMap;

struct Solution {
    idx: HashMap<i32, Vec<i32>>,
}

impl Solution {
    fn new(nums: Vec<i32>) -> Self {
        todo!()
    }

    fn pick(&self, target: i32) -> i32 {
        todo!()
    }
}

fn main() {
    let tests: &[(&str, &[i32], i32, &[i32])] = &[
        ("returns valid index for target 3", &[1, 2, 3, 3, 3], 3, &[2, 3, 4]),
        ("single occurrence", &[1, 2, 3, 3, 3], 1, &[0]),
        ("single element array", &[5], 5, &[0]),
        ("non-contiguous duplicates", &[1, 2, 1, 2, 1], 1, &[0, 2, 4]),
        ("negative numbers with duplicates", &[-1, -2, -1, -3, -1], -1, &[0, 2, 4]),
        ("all same elements", &[1, 1, 1, 1, 1], 1, &[0, 1, 2, 3, 4]),
    ];

    println!("\n============================================================");
    println!("  398. Random Pick Index");
    println!("============================================================");
    let mut passed = 0;
    for (i, (label, input, target, valid)) in tests.iter().enumerate() {
        let sol = Solution::new(input.to_vec());
        let got = sol.pick(*target);
        let ok = valid.contains(&got);
        if ok {
            passed += 1;
            println!("  Test {} ({}): PASS", i + 1, label);
        } else {
            println!("  Test {} ({}): FAIL", i + 1, label);
            println!("    Expected one of: {:?}\n    Got:              {}", valid, got);
        }
    }
    println!("\n  {}/{} passed", passed, tests.len());
    println!("============================================================\n");
    std::process::exit(if passed == tests.len() { 0 } else { 1 });
}
