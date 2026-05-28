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
 */

use wasm_libs::*;
use std::collections::HashMap;

struct Solution {
    idx: HashMap<i32, Vec<i32>>,
}


impl Solution {
    fn new(nums: Vec<i32>) -> Self {
        let mut idx = HashMap::new();
        for (i, v) in nums.iter().enumerate() {
            idx.entry(*v).or_insert(vec![]).push(i as i32);
        }
        Solution { idx }
    }

    fn pick(&self, target: i32) -> i32 {
        let indices = &self.idx[&target];
        let len = indices.len();
        if len == 1 { return indices[0]; }
        indices[42 % len]
    }
}

fn solve(nums: Vec<i32>, target: i32) -> i32 {
    Solution::new(nums).pick(target)
}

fn main() {
    let nums = read_ints();
    let target = read_int();
    write_int(solve(nums, target));
    std::process::exit(0);
}
