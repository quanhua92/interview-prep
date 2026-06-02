/*
 * P493: Reverse Pairs [PREMIUM] (Hard)
 * https://leetcode.com/problems/reverse-pairs/
 * Topics: Array, Binary Search, Divide and Conquer, Binary Indexed Tree, Segment Tree, Merge Sort, Ordered Set
 *
 * Given an integer array nums, return the number of reverse pairs in the array.
 * A reverse pair is a pair (i, j) where:
 *
 * Example 1:
 *     Input: nums = [1,3,2,3,1]
 *     Output: 2
 *
 * Example 2:
 *     Input: nums = [2,4,3,5,1]
 *     Output: 3
 *
 * Constraints:
 *     - 1 <= nums.length <= 5 * 10^4
 *     - -2^31 <= nums[i] <= 2^31 - 1
 *
 * Hint: Use the merge-sort technique.
 */


#include "io.h"
#include <stdlib.h>
#include <string.h>

static int merge_sort(int *arr, int *tmp, int left, int right)
{
    if (right - left <= 1) return 0;
    int mid = left + (right - left) / 2;
    int count = merge_sort(arr, tmp, left, mid) + merge_sort(arr, tmp, mid, right);
    int j = mid;
    for (int i = left; i < mid; i++) {
        while (j < right && (long long)arr[i] > 2LL * arr[j])
            j++;
        count += j - mid;
    }
    int p = left, q = mid, k = left;
    while (p < mid && q < right)
        tmp[k++] = arr[p] <= arr[q] ? arr[p++] : arr[q++];
    while (p < mid) tmp[k++] = arr[p++];
    while (q < right) tmp[k++] = arr[q++];
    for (int i = left; i < right; i++) arr[i] = tmp[i];
    return count;
}

static int reversePairs(int *nums, int numsSize)
{
    if (numsSize <= 1) return 0;
    int *tmp = (int *)malloc(numsSize * sizeof(int));
    int result = merge_sort(nums, tmp, 0, numsSize);
    free(tmp);
    return result;
}

int main(void)
{
    int n;
    int *nums = read_ints(&n);
    write_int(reversePairs(nums, n));
    free(nums);
    return 0;
}
