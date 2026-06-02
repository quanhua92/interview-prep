/*
 * P912: Sort an Array (Medium)
 * https://leetcode.com/problems/sort-an-array/
 * Topics: Array, Divide and Conquer, Sorting, Heap (Priority Queue), Merge Sort, Bucket Sort, Radix Sort, Counting Sort
 *
 * Given an array of integers nums, sort the array in ascending order and return it.
 * You must solve the problem without using any built-in functions in O(nlog(n)) time complexity and with the smallest space complexity possible.
 *
 * Example 1:
 *     Input: nums = [5,2,3,1]
 *     Output: [1,2,3,5]
 *
 * Example 2:
 *     Input: nums = [5,1,1,2,0,0]
 *     Output: [0,0,1,1,2,5]
 *
 * Constraints:
 *     - 1 <= nums.length <= 5 * 10^4
 *     - -5 * 10^4 <= nums[i] <= 5 * 10^4
 *
 * Hint: Implement merge sort — divide array in half, sort recursively, merge.
 */


#include "io.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void merge(int *arr, int *tmp, int l, int m, int r)
{
    abort();
}

static void merge_sort(int *arr, int *tmp, int l, int r)
{
    abort();
}

int main(void)
{
    int n;
    int *nums = read_ints(&n);
    if (n > 0) {
        int *tmp = malloc(n * sizeof(int));
        merge_sort(nums, tmp, 0, n - 1);
        free(tmp);
        write_ints(nums, n);
    } else {
        printf("\n");
    }
    free(nums);
    return 0;
}
