/*
 * P55: Jump Game (Medium)
 * https://leetcode.com/problems/jump-game/
 * Topics: Array, Dynamic Programming, Greedy
 *
 * You are given an integer array nums. You are initially positioned at the array's first index, and each element in the array represents your maximum jump length at that position.
 * Return true if you can reach the last index, or false otherwise.
 *
 * Hint: Track the farthest reachable index; if you pass it, the end is unreachable.
 */


#include "cpptest.h"

bool canJump(const std::vector<int> &nums) {
    abort();
}

int main() {
    std::vector<int> nums = read_ints();
    bool result = canJump(nums);
    write_bool(result);
    return 0;
}
