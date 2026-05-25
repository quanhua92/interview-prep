/*
 * P525: Contiguous Array [PREMIUM] (Medium)
 * https://leetcode.com/problems/contiguous-array/
 * Topics: Array, Hash Table, Prefix Sum
 * 
 * Given a binary array nums, return the maximum length of a contiguous subarray with an equal number of 0 and 1.
 * Example 1:
 *     Input: nums = [0,1]
 *     Output: 2
 *     Explanation: [0, 1] is the longest contiguous subarray with an equal number of 0 and 1.
 * 
 * Example 2:
 *     Input: nums = [0,1,0]
 *     Output: 2
 *     Explanation: [0, 1] (or [1, 0]) is a longest contiguous subarray with equal number of 0 and 1.
 * 
 * Example 3:
 *     Input: nums = [0,1,1,1,1,1,0,0,0]
 *     Output: 6
 *     Explanation: [1,1,1,0,0,0] is the longest contiguous subarray with equal number of 0 and 1.
 * 
 * Constraints:
 *     - 1 <= nums.length <= 105
 *     - nums[i] is either 0 or 1.
 * 
 * Template (python3):
 *     class Solution:
 *         def findMaxLength(self, nums: List[int]) -> int:
 */
#include "ctest.h"
#include <stdlib.h>

typedef struct Entry {
    int key;
    int value;
    struct Entry *next;
} Entry;

#define HM_SIZE 20003

static Entry *hm[HM_SIZE];

static void hm_init(void)
{
    abort();
}

static void hm_set(int key, int val)
{
    abort();
}

static int hm_get(int key, int *found)
{
    abort();
}

static void hm_clear(void)
{
    abort();
}

int *find_max_length(int *nums, int numsSize, int target, int *retSize)
{
    abort();
}

int main(void)
{
    TestCase tests[] = {
        {"example 1", {0, 1}, 2, 0, {2}, 1},
        {"example 2", {0, 1, 0}, 3, 0, {2}, 1},
        {"example 3", {0, 1, 1, 1, 1, 1, 0, 0, 0}, 9, 0, {6}, 1},
        {"single element", {1}, 1, 0, {0}, 1},
        {"balanced halves", {0, 0, 0, 0, 1, 1, 1, 1}, 8, 0, {8}, 1},
        {"middle balanced", {0, 0, 1, 0, 0, 0, 1, 1}, 8, 0, {6}, 1},
    };
    int n = sizeof(tests) / sizeof(tests[0]);
    RUN_TESTS("525. Contiguous Array", find_max_length, tests, n);
}
