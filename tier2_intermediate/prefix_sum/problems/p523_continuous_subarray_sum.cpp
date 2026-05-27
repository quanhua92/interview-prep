/*
 * P523: Continuous Subarray Sum [PREMIUM] (Medium)
 * https://leetcode.com/problems/continuous-subarray-sum/
 * Topics: Array, Hash Table, Math, Prefix Sum
 *
 * Given an integer array nums and an integer k, return true if nums has a good subarray or false otherwise.
 * A good subarray is a subarray where:
 * Note that:
 * Example 1:
 *     Input: nums = [23,2,4,6,7], k = 6
 *     Output: true
 *     Explanation: [2, 4] is a continuous subarray of size 2 whose elements sum up to 6.
 *
 * Example 2:
 *     Input: nums = [23,2,6,4,7], k = 6
 *     Output: true
 *     Explanation: [23, 2, 6, 4, 7] is an continuous subarray of size 5 whose elements sum up to 42.
 *     42 is a multiple of 6 because 42 = 7 * 6 and 7 is an integer.
 *
 * Example 3:
 *     Input: nums = [23,2,6,4,7], k = 13
 *     Output: false
 *
 * Constraints:
 *     - 1 <= nums.length <= 105
 *     - 0 <= nums[i] <= 109
 *     - 0 <= sum(nums[i]) <= 231 - 1
 *     - 1 <= k <= 231 - 1
 *
 * Template (python3):
 *     class Solution:
 *         def checkSubarraySum(self, nums: List[int], k: int) -> bool:
 */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#include "cpptest.h"
#pragma GCC diagnostic pop
#include <string>
#include <vector>

bool check_subarray_sum(const std::vector<int>& nums, int k)
{
    abort();
}

int main(void)
{
    struct {
        const char *label;
        std::vector<int> input;
        int target;
        bool expected;
    } tests[] = {
        {"example 1",              {23, 2, 4, 6, 7},   6,  true},
        {"example 2",              {23, 2, 6, 4, 7},   6,  true},
        {"example 3",              {23, 2, 6, 4, 7},   13, false},
        {"two zeros sum to 0",     {5, 0, 0},           3,  true},
        {"no valid subarray",      {1, 2},              4,  false},
        {"two zeros always valid", {0, 0},              1,  true},
    };
    int n_tests = sizeof(tests) / sizeof(tests[0]);

    printf("\n============================================================\n");
    printf("  523. Continuous Subarray Sum\n");
    printf("============================================================\n");
    int passed = 0;
    for (int i = 0; i < n_tests; i++) {
        bool got = check_subarray_sum(tests[i].input, tests[i].target);
        if (got == tests[i].expected) {
            passed++;
            printf("  Test %d (%s): PASS\n", i + 1, tests[i].label);
        } else {
            printf("  Test %d (%s): FAIL\n", i + 1, tests[i].label);
            printf("    Expected: %s\n    Got:      %s\n", tests[i].expected ? "true" : "false", got ? "true" : "false");
        }
    }
    printf("\n  %d/%d passed\n", passed, n_tests);
    printf("============================================================\n\n");
    return passed == n_tests ? 0 : 1;
}
