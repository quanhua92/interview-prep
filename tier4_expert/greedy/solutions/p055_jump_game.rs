/*
 * P55: Jump Game (Medium)
 * https://leetcode.com/problems/jump-game/
 * Topics: Array, Dynamic Programming, Greedy
 *
 * You are given an integer array nums. You are initially positioned at the array's first index, and each element in the array represents your maximum jump length at that position.
 * Return true if you can reach the last index, or false otherwise.
 *
 * Example 1:
 *     Input: nums = [2,3,1,1,4]
 *     Output: true
 *     Explanation: Jump 1 step from index 0 to 1, then 3 steps to the last index.
 *
 * Example 2:
 *     Input: nums = [3,2,1,0,4]
 *     Output: false
 *     Explanation: You will always arrive at index 3 no matter what. Its maximum jump length is 0, which makes it impossible to reach the last index.
 *
 * Constraints:
 *     - 1 <= nums.length <= 10^4
 *     - 0 <= nums[i] <= 10^5
 *
 * Template (python3):
 *     class Solution:
 *         def canJump(self, nums: List[int]) -> bool:
 *
 * Hint: Track the farthest reachable index; if you pass it, the end is unreachable.
 */

use wasm_libs::*;

fn can_jump(nums: &[i32]) -> bool {
    let mut max_reach: usize = 0;
    for (i, &jump) in nums.iter().enumerate() {
        if i > max_reach { return false; }
        let jump = jump as usize;
        if i + jump > max_reach { max_reach = i + jump; }
    }
    true
}

fn main() {
    let nums = read_ints();
    let result = can_jump(&nums);
    write_bool(result);
}
