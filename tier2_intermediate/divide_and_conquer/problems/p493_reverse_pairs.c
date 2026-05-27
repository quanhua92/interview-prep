/*
 * P493: Reverse Pairs [PREMIUM] (Hard)
 * https://leetcode.com/problems/reverse-pairs/
 * Topics: Array, Binary Search, Divide and Conquer, Binary Indexed Tree, Segment Tree, Merge Sort, Ordered Set
 *
 * Given an integer array nums, return the number of reverse pairs in the array.
 *
 * Example 1:
 *     Input: nums = [1,3,2,3,1]
 *     Output: 2
 *
 * Hint: Use the merge-sort technique.
 */

#include "io.h"
#include <stdlib.h>

int reversePairs(int *nums, int numsSize)
{
    abort();
}

int main(void)
{
    int n;
    int *nums = read_ints(&n);
    write_int(reversePairs(nums, n));
    free(nums);
    return 0;
}
