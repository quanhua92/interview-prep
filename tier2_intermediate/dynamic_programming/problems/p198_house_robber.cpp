/*
 * P198: House Robber (Medium)
 * https://leetcode.com/problems/house-robber/
 * Topics: Array, Dynamic Programming
 * 
 * You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed, the only constraint stopping you from robbing each of them is that adjacent houses have security systems connected and it will automatically contact the police if two adjacent houses were broken into on the same night.
 * Given an integer array nums representing the amount of money of each house, return the maximum amount of money you can rob tonight without alerting the police.
 * 
 * Example 1:
 *     Input: nums = [1,2,3,1]
 *     Output: 4
 *     Explanation: Rob house 1 (money = 1) and then rob house 3 (money = 3).
 *     Total amount you can rob = 1 + 3 = 4.
 * 
 * Example 2:
 *     Input: nums = [2,7,9,3,1]
 *     Output: 12
 *     Explanation: Rob house 1 (money = 2), rob house 3 (money = 9) and rob house 5 (money = 1).
 *     Total amount you can rob = 2 + 9 + 1 = 12.
 * 
 * Constraints:
 *     - 1 <= nums.length <= 100
 *     - 0 <= nums[i] <= 400
 * 
 * Template (python3):
 *     class Solution:
 *         def rob(self, nums: List[int]) -> int:
 * 
 * Hint: Use two variables (prev, curr) -- for each house decide to rob or skip.
 */
#include "cpptest.h"
#include <vector>

int rob(std::vector<int> nums) {
    abort();
}

int main() {
    struct TC { const char *label; std::vector<int> nums; int expected; };
    std::vector<TC> tests = {
        {"example 1", {1,2,3,1}, 4},
        {"example 2", {2,7,9,3,1}, 12},
        {"single house", {1}, 1},
        {"no houses", {}, 0},
        {"alternate houses equal", {2,1,1,2}, 4},
        {"all zeros", {0,0,0}, 0},
        {"two houses", {1,2}, 2},
        {"alternating high low", {10,1,10,1,10}, 30},
        {"three peaks", {100,1,1,100,1,1,100}, 300},
        {"max values large array", std::vector<int>(100, 400), 20000},
    };
    int total = (int)tests.size();
    int passed = 0;
    for (int i = 0; i < total; i++) {
        int got = rob(tests[i].nums);
        if (got == tests[i].expected) {
            passed++;
            printf("  Test %d (%s): PASS\n", i + 1, tests[i].label);
        } else {
            printf("  Test %d (%s): FAIL (expected %d, got %d)\n", i + 1, tests[i].label, tests[i].expected, got);
        }
    }
    printf("\n  %d/%d passed\n", passed, total);
    return passed == total ? 0 : 1;
}
