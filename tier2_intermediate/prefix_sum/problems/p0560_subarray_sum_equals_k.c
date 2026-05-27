/*
 * P560: Subarray Sum Equals K (Medium)
 * https://leetcode.com/problems/subarray-sum-equals-k/
 * Topics: Array, Hash Table, Prefix Sum
 *
 * Given an array of integers nums and an integer k, return the total number of subarrays whose sum equals to k.
 * A subarray is a contiguous non-empty sequence of elements within an array.
 *
 * Example 1:
 *     Input: nums = [1,1,1], k = 2
 *     Output: 2
 *
 * Example 2:
 *     Input: nums = [1,2,3], k = 3
 *     Output: 2
 *
 * Constraints:
 *     - 1 <= nums.length <= 2 * 104
 *     - -1000 <= nums[i] <= 1000
 *     - -107 <= k <= 107
 *
 * Hints:
 *     - Will Brute force work here? Try to optimize it.
 *     - Can we optimize it by using some extra space?
 *     - What about storing sum frequencies in a hash table? Will it be useful?
 *     - sum(i,j)=sum(0,j)-sum(0,i), where sum(i,j) represents the sum of all the elements from index i to j-1.
 *
 * Can we use this property to optimize it.
 *
 * Template (python3):
 *     class Solution:
 *         def subarraySum(self, nums: List[int], k: int) -> int:
 *
 * Hint: Use a hash map with prefix sums to count subarrays summing to k.
 */

#include "io.h"
#include <stdlib.h>

int *subarray_sum(int *nums, int numsSize, int k, int *retSize)
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
    int *result = subarray_sum(nums, n, k, &retSize);
    write_ints(result, retSize);
    free(nums);
    free(result);
    return 0;
}
