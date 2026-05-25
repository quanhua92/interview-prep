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
 *     Explanation: After sorting the array, the positions of some numbers are not changed (for example, 2 and 3), while the positions of other numbers are changed (for example, 1 and 5).
 *
 * Example 2:
 *     Input: nums = [5,1,1,2,0,0]
 *     Output: [0,0,1,1,2,5]
 *     Explanation: Note that the values of nums are not necessarily unique.
 *
 * Constraints:
 *     - 1 <= nums.length <= 5 * 104
 *     - -5 * 104 <= nums[i] <= 5 * 104
 *
 * Template (python3):
 *     class Solution:
 *         def sortArray(self, nums: List[int]) -> List[int]:
 *
 * Hint: Implement merge sort — divide array in half, sort recursively, merge.
 */


#include <stdio.h>
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

int *sortArray(int *nums, int n, int *ret_size)
{
    if (n <= 0) {
        *ret_size = 0;
        return calloc(1, sizeof(int));
    }
    int *out = malloc(n * sizeof(int));
    memcpy(out, nums, n * sizeof(int));
    int *tmp = malloc(n * sizeof(int));
    merge_sort(out, tmp, 0, n - 1);
    free(tmp);
    *ret_size = n;
    return out;
}

int main(void)
{
    printf("\n============================================================\n");
    printf("  912. Sort an Array\n");
    printf("============================================================\n");
    int passed = 0, total = 8;

    {
        int input[] = {5, 2, 3, 1}, exp[] = {1, 2, 3, 5};
        int rs = 0; int *got = sortArray(input, 4, &rs);
        if (rs == 4 && memcmp(got, exp, 4 * sizeof(int)) == 0)
            { passed++; printf("  Test 1 (example 1): PASS\n"); }
        else { printf("  Test 1 (example 1): FAIL\n"); }
        free(got);
    }
    {
        int input[] = {5, 1, 1, 2, 0, 0}, exp[] = {0, 0, 1, 1, 2, 5};
        int rs = 0; int *got = sortArray(input, 6, &rs);
        if (rs == 6 && memcmp(got, exp, 6 * sizeof(int)) == 0)
            { passed++; printf("  Test 2 (duplicates): PASS\n"); }
        else { printf("  Test 2 (duplicates): FAIL\n"); }
        free(got);
    }
    {
        int input[] = {1}, exp[] = {1};
        int rs = 0; int *got = sortArray(input, 1, &rs);
        if (rs == 1 && memcmp(got, exp, 1 * sizeof(int)) == 0)
            { passed++; printf("  Test 3 (single element): PASS\n"); }
        else { printf("  Test 3 (single element): FAIL\n"); }
        free(got);
    }
    {
        int rs = 0; int *got = sortArray(NULL, 0, &rs);
        if (rs == 0)
            { passed++; printf("  Test 4 (empty array): PASS\n"); }
        else { printf("  Test 4 (empty array): FAIL\n"); }
        free(got);
    }
    {
        int input[] = {1, 2, 3, 4, 5}, exp[] = {1, 2, 3, 4, 5};
        int rs = 0; int *got = sortArray(input, 5, &rs);
        if (rs == 5 && memcmp(got, exp, 5 * sizeof(int)) == 0)
            { passed++; printf("  Test 5 (already sorted): PASS\n"); }
        else { printf("  Test 5 (already sorted): FAIL\n"); }
        free(got);
    }
    {
        int input[] = {5, 4, 3, 2, 1}, exp[] = {1, 2, 3, 4, 5};
        int rs = 0; int *got = sortArray(input, 5, &rs);
        if (rs == 5 && memcmp(got, exp, 5 * sizeof(int)) == 0)
            { passed++; printf("  Test 6 (reverse sorted): PASS\n"); }
        else { printf("  Test 6 (reverse sorted): FAIL\n"); }
        free(got);
    }
    {
        int input[] = {7, 7, 7, 7}, exp[] = {7, 7, 7, 7};
        int rs = 0; int *got = sortArray(input, 4, &rs);
        if (rs == 4 && memcmp(got, exp, 4 * sizeof(int)) == 0)
            { passed++; printf("  Test 7 (all same elements): PASS\n"); }
        else { printf("  Test 7 (all same elements): FAIL\n"); }
        free(got);
    }
    {
        int input[] = {-5, -3, -8, -1}, exp[] = {-8, -5, -3, -1};
        int rs = 0; int *got = sortArray(input, 4, &rs);
        if (rs == 4 && memcmp(got, exp, 4 * sizeof(int)) == 0)
            { passed++; printf("  Test 8 (negative numbers): PASS\n"); }
        else { printf("  Test 8 (negative numbers): FAIL\n"); }
        free(got);
    }

    printf("\n  %d/%d passed\n", passed, total);
    printf("============================================================\n\n");
    return passed == total ? 0 : 1;
}
