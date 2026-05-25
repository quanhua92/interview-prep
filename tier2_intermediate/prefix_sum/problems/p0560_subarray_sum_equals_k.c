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
#include "ctest.h"
#include <stdlib.h>

typedef struct Entry {
    long long key;
    int value;
    struct Entry *next;
} Entry;

static Entry *hm[40007];

static unsigned hm_hash(long long key)
{
    /* TODO: Implement */
    return 0;
}

static void hm_set(long long key, int val)
{
    /* TODO: Implement */
    return 0;
}

static int hm_get(long long key)
{
    /* TODO: Implement */
    return 0;
}

static void hm_clear(void)
{
    /* TODO: Implement */
    return 0;
}

int *subarray_sum(int *nums, int numsSize, int k, int *retSize)
{
    /* TODO: Implement */
    return 0;
}

int main(void)
{
    TestCase tests[] = {
        {"example 1", {1, 1, 1}, 3, 2, {2}, 1},
        {"example 2", {1, 2, 3}, 3, 3, {2}, 1},
        {"empty array", {}, 0, 0, {0}, 1},
        {"single element equals k", {1}, 1, 1, {1}, 1},
        {"single element not k", {1}, 1, 2, {0}, 1},
        {"negatives with zero sum", {1, -1, 0}, 3, 0, {3}, 1},
        {"all zeros", {0, 0, 0}, 3, 0, {6}, 1},
    };
    int n = sizeof(tests) / sizeof(tests[0]);
    RUN_TESTS("560. Subarray Sum Equals K", subarray_sum, tests, n);
}
