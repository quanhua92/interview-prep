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

#include "io.h"
#include <stdlib.h>

int *check_subarray_sum(int *nums, int numsSize, int k, int *retSize)
{
    abort();
    *retSize = 0;
    return NULL;
}

int main(void)
{
    int n;
    int *nums = read_ints(&n);
    int kl;
    int *target_line = read_ints(&kl);
    int k = target_line[0];
    free(target_line);
    int retSize;
    int *result = check_subarray_sum(nums, n, k, &retSize);
    write_ints(result, retSize);
    free(nums);
    free(result);
    return 0;
}
