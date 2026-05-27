/*
 * P169: Majority Element (Easy)
 * https://leetcode.com/problems/majority-element/
 * Topics: Array, Hash Table, Divide and Conquer, Sorting, Counting
 *
 * Given an array nums of size n, return the majority element.
 * The majority element is the element that appears more than ⌊n / 2⌋ times. You may assume that the majority element always exists in the array.
 *
 * Example 1:
 *     Input: nums = [3,2,3]
 *     Output: 3
 *
 * Example 2:
 *     Input: nums = [2,2,1,1,1,2,2]
 *     Output: 2
 *
 * Hint: Use Boyer-Moore voting algorithm — maintain a candidate and count.
 */

#include "io.h"
#include <stdlib.h>

int majorityElement(int *nums, int n)
{
    abort();
}

int main(void)
{
    int n;
    int *nums = read_ints(&n);
    write_int(majorityElement(nums, n));
    free(nums);
    return 0;
}
