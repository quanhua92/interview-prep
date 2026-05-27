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
 *     - 1 <= nums.length <= 5 * 104
 *     - -5 * 104 <= nums[i] <= 5 * 104
 *
 * Hint: Implement merge sort — divide array in half, sort recursively, merge.
 */


#include "io.h"
#include <stdlib.h>
#include <string.h>

static void merge(int *arr, int *tmp, int l, int m, int r)
{
    memcpy(tmp + l, arr + l, (r - l + 1) * sizeof(int));
    int i = l, j = m + 1, k = l;
    while (i <= m && j <= r) {
        if (tmp[i] <= tmp[j]) arr[k++] = tmp[i++];
        else arr[k++] = tmp[j++];
    }
    while (i <= m) arr[k++] = tmp[i++];
    while (j <= r) arr[k++] = tmp[j++];
}

static void merge_sort(int *arr, int *tmp, int l, int r)
{
    if (l >= r) return;
    int m = l + (r - l) / 2;
    merge_sort(arr, tmp, l, m);
    merge_sort(arr, tmp, m + 1, r);
    merge(arr, tmp, l, m, r);
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
