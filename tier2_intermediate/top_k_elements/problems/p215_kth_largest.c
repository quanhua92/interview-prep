/*
 * P215: Kth Largest Element in an Array (Medium)
 * https://leetcode.com/problems/kth-largest-element-in-an-array/
 * Topics: Array, Divide and Conquer, Sorting, Heap (Priority Queue), Quickselect
 *
 * Given an integer array nums and an integer k, return the kth largest element in the array.
 * Note that it is the kth largest element in the sorted order, not the kth distinct element.
 * Can you solve it without sorting?
 *
 * Example 1:
 *     Input: nums = [3,2,1,5,6,4], k = 2
 *     Output: 5
 *
 * Example 2:
 *     Input: nums = [3,2,3,1,2,4,5,5,6], k = 4
 *     Output: 4
 *
 * Constraints:
 *     - 1 <= k <= nums.length <= 10^5
 *     - -10^4 <= nums[i] <= 10^4
 *
 * Template (python3):
 *     class Solution:
 *         def findKthLargest(self, nums: List[int], k: int) -> int:
 *
 * Hint: Use a min-heap of size k to efficiently find the kth largest element.
 */

#include "io.h"
#include <stdlib.h>
#include <string.h>

static void swap(int *a, int *b) {
    abort();
}

static int partition(int *a, int lo, int hi)
{
    abort();
}

static int findKthLargest(int *nums, int numsSize, int k)
{
    abort();
}

int main(void)
{
    int n;
    int *nums = read_ints(&n);
    int k_len;
    int *k_arr = read_ints(&k_len);
    int k = k_arr[0];
    free(k_arr);
    int result = findKthLargest(nums, n, k);
    write_int(result);
    free(nums);
    return 0;
}
