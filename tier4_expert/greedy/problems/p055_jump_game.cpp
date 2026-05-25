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
 *     - 1 <= nums.length <= 104
 *     - 0 <= nums[i] <= 105
 * 
 * Template (python3):
 *     class Solution:
 *         def canJump(self, nums: List[int]) -> bool:
 * 
 * Hint: Track the farthest reachable index; if you pass it, the end is unreachable.
 */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#include "cpptest.h"
#pragma GCC diagnostic pop

bool canJump(const std::vector<int> &nums) {
    abort();
}

int main() {
    printf("\n============================================================\n");
    printf("  55. Jump Game\n");
    printf("============================================================\n");
    struct T { const char *label; std::vector<int> nums; bool expected; };
    std::vector<T> tests = {
        {"example 1", {2,3,1,1,4}, true},
        {"example 2", {3,2,1,0,4}, false},
        {"single element", {0}, true},
        {"all ones", {1,1,1,1,1}, true},
        {"big jump from start", {5,0,0,0,0}, true},
        {"stuck at start", {0,1}, false},
        {"two elements reachable", {2,0}, true},
    };
    int passed = 0;
    for (int i = 0; i < (int)tests.size(); i++) {
        bool got = canJump(tests[i].nums);
        if (got == tests[i].expected) {
            passed++;
            printf("  Test %d (%s): PASS\n", i + 1, tests[i].label);
        } else {
            printf("  Test %d (%s): FAIL\n", i + 1, tests[i].label);
            printf("    Expected: %d, Got: %d\n", tests[i].expected, got);
        }
    }
    printf("\n  %d/%d passed\n", passed, (int)tests.size());
    printf("============================================================\n\n");
    return passed == (int)tests.size() ? 0 : 1;
}
