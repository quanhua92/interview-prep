/*
 * P410: Split Array Largest Sum (Hard)
 * https://leetcode.com/problems/split-array-largest-sum/
 * Topics: Array, Binary Search, Dynamic Programming, Greedy, Prefix Sum
 *
 * Given an integer array nums and an integer k, split nums into k non-empty subarrays such that the largest sum of any subarray is minimized.
 * Return the minimized largest sum of the split.
 * A subarray is a contiguous part of the array.
 *
 * Example 1:
 *     Input: nums = [7,2,5,10,8], k = 2
 *     Output: 18
 *     Explanation: There are four ways to split nums into two subarrays.
 *     The best way is to split it into [7,2,5] and [10,8], where the largest sum among the two subarrays is only 18.
 *
 * Example 2:
 *     Input: nums = [1,2,3,4,5], k = 2
 *     Output: 9
 *     Explanation: There are four ways to split nums into two subarrays.
 *     The best way is to split it into [1,2,3] and [4,5], where the largest sum among the two subarrays is only 9.
 *
 * Constraints:
 *     - 1 <= nums.length <= 1000
 *     - 0 <= nums[i] <= 106
 *     - 1 <= k <= min(50, nums.length)
 *
 * Template (python3):
 *     class Solution:
 *         def splitArray(self, nums: List[int], k: int) -> int:
 *
 * Hint: Binary search the answer in [max(nums), sum(nums)] and check feasibility greedily.
 */

#include "io.h"
#include <stdlib.h>

static int feasible(int *nums, int nums_n, long long max_sum, int k)
{
    int count = 1;
    long long current = 0;
    for (int i = 0; i < nums_n; i++) {
        current += nums[i];
        if (current > max_sum) {
            count++;
            current = nums[i];
            if (count > k) return 0;
        }
    }
    return 1;
}

long long splitArray(int *nums, int numsSize, int k)
{
    long long left = 0, right = 0;
    for (int i = 0; i < numsSize; i++) {
        if ((long long)nums[i] > left) left = nums[i];
        right += nums[i];
    }
    while (left < right) {
        long long mid = left + (right - left) / 2;
        if (feasible(nums, numsSize, mid, k))
            right = mid;
        else
            left = mid + 1;
    }
    return left;
}

int main(void)
{
    int n;
    int *nums = read_ints(&n);
    int kk;
    int *k_line = read_ints(&kk);
    int k = k_line[0];
    free(k_line);
    write_int((int)splitArray(nums, n, k));
    free(nums);
    return 0;
}
