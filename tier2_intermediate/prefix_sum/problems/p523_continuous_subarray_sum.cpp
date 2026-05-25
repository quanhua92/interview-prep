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
#include "cpptest.h"
#include <vector>
#include <unordered_map>

using namespace std;

vector<int> check_subarray_sum(const vector<int>& nums, int k)
{
    abort();
}

int main()
{
    TestCase tests[] = {
        {"example 1", {23, 2, 4, 6, 7}, 6, {1}},
        {"example 2", {23, 2, 6, 4, 7}, 6, {1}},
        {"example 3", {23, 2, 6, 4, 7}, 13, {0}},
        {"two zeros sum to 0", {5, 0, 0}, 3, {1}},
        {"no valid subarray", {1, 2}, 4, {0}},
        {"two zeros always valid", {0, 0}, 1, {1}},
    };
    int n = sizeof(tests) / sizeof(tests[0]);
    RUN_TESTS("523. Continuous Subarray Sum", check_subarray_sum, tests, n);
}
