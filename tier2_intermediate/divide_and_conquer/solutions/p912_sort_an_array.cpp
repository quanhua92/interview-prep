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
#include <vector>

static void merge_sort(std::vector<int> &arr, std::vector<int> &tmp, int l, int r)
{
    if (l >= r) return;
    int m = l + (r - l) / 2;
    merge_sort(arr, tmp, l, m);
    merge_sort(arr, tmp, m + 1, r);
    for (int i = l; i <= r; i++) tmp[i] = arr[i];
    int i = l, j = m + 1, k = l;
    while (i <= m && j <= r) {
        if (tmp[i] <= tmp[j]) arr[k++] = tmp[i++];
        else arr[k++] = tmp[j++];
    }
    while (i <= m) arr[k++] = tmp[i++];
    while (j <= r) arr[k++] = tmp[j++];
}

int main(void)
{
    std::vector<int> nums = read_ints();
    int n = (int)nums.size();
    if (n <= 1) { write_ints(nums); return 0; }
    std::vector<int> tmp(n);
    merge_sort(nums, tmp, 0, n - 1);
    write_ints(nums);
    return 0;
}
