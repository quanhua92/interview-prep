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

#include "cpptest.h"
#include <vector>

using namespace std;

vector<int> num_subarray_product_less_than_k(const vector<int>& nums, int k)
{
    if (k <= 1) return {0};
    int count = 0;
    double product = 1.0;
    int left = 0;
    for (int right = 0; right < (int)nums.size(); right++) {
        product *= nums[right];
        while (product >= k) {
            product /= nums[left];
            left++;
        }
        count += right - left + 1;
    }
    return {count};
}

int main()
{
    TestCase tests[] = {
        {"example 1", {10, 5, 2, 6}, 100, {8}},
        {"zero k", {1, 2, 3}, 0, {0}},
        {"all ones", {1, 1, 1}, 2, {6}},
        {"k equals 0", {1, 2, 3}, 0, {0}},
        {"k equals 1", {1, 2, 3}, 1, {0}},
        {"all large numbers", {1000, 1000, 1000}, 1000000, {3}},
        {"small k many singles", {10, 5, 2, 6}, 8, {3}},
    };
    int n = sizeof(tests) / sizeof(tests[0]);
    RUN_TESTS("713. Subarray Product Less Than K", num_subarray_product_less_than_k, tests, n);
}
