/*
 * P713: Subarray Product Less Than K (Medium)
 * https://leetcode.com/problems/subarray-product-less-than-k/
 * Topics: Array, Binary Search, Sliding Window, Prefix Sum
 *
 * Given an array of integers nums and an integer k, return the number of contiguous subarrays where the product of all the elements in the subarray is strictly less than k.
 *
 * Example 1:
 *     Input: nums = [10,5,2,6], k = 100
 *     Output: 8
 *     Explanation: The 8 subarrays that have product less than 100 are:
 *     [10], [5], [2], [6], [10, 5], [5, 2], [2, 6], [5, 2, 6]
 *     Note that [10, 5, 2] is not included as the product of 100 is not strictly less than k.
 *
 * Example 2:
 *     Input: nums = [1,2,3], k = 0
 *     Output: 0
 *
 * Constraints:
 *     - 1 <= nums.length <= 3 * 104
 *     - 1 <= nums[i] <= 1000
 *     - 0 <= k <= 106
 *
 * Hints:
 *     - For each j, let opt(j) be the smallest i so that nums[i] * nums[i+1] * ... * nums[j] is less than k.  opt is an increasing function.
 *
 * Template (python3):
 *     class Solution:
 *         def numSubarrayProductLessThanK(self, nums: List[int], k: int) -> int:
 *
 * Hint: Use a sliding window where you shrink from the left when product >= k.
 */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#include "cpptest.h"
#pragma GCC diagnostic pop
#include <vector>

int num_subarray_product_less_than_k(const std::vector<int>& nums, int k)
{
    abort();
}

int main(void)
{
    struct {
        const char *label;
        std::vector<int> input;
        int target;
        int expected;
    } tests[] = {
        {"example 1",         {10, 5, 2, 6},       100,     8},
        {"zero k",            {1, 2, 3},           0,       0},
        {"all ones",          {1, 1, 1},           2,       6},
        {"k equals 0",        {1, 2, 3},           0,       0},
        {"k equals 1",        {1, 2, 3},           1,       0},
        {"all large numbers", {1000, 1000, 1000},  1000000, 3},
        {"small k many singles", {10, 5, 2, 6},    8,       3},
    };
    int n_tests = sizeof(tests) / sizeof(tests[0]);

    printf("\n============================================================\n");
    printf("  713. Subarray Product Less Than K\n");
    printf("============================================================\n");
    int passed = 0;
    for (int i = 0; i < n_tests; i++) {
        int got = num_subarray_product_less_than_k(tests[i].input, tests[i].target);
        if (got == tests[i].expected) {
            passed++;
            printf("  Test %d (%s): PASS\n", i + 1, tests[i].label);
        } else {
            printf("  Test %d (%s): FAIL\n", i + 1, tests[i].label);
            printf("    Expected: %d\n    Got:      %d\n", tests[i].expected, got);
        }
    }
    printf("\n  %d/%d passed\n", passed, n_tests);
    printf("============================================================\n\n");
    return passed == n_tests ? 0 : 1;
}
